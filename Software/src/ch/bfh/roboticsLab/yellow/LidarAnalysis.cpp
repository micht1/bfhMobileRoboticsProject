#line 2 "ch/bfh/roboticsLab/yellow/LidarAnalysis.cpp"
/* LidarAnalysis.cpp
 * Copyright (c) BFH roboticsLab
 * All rights reserved.
 */

#include <ch/bfh/roboticsLab/yellow/LidarAnalysis.h>

#include <ch/bfh/roboticsLab/yellow/driver/Lidar.h>
#include <ch/bfh/roboticsLab/util/Util.h>
#include <ch/bfh/roboticsLab/yellow/Peripherals.h>

#include <cmath>
#include <ch/bfh/roboticsLab/yellow/Console.h>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {

LidarAnalysis& LidarAnalysis::getInstance() {
    static LidarAnalysis lidarAnalysis;
    return lidarAnalysis;
}

LidarAnalysis::LidarAnalysis() :
    lidar(driver::LIDAR::getInstance()) {
}

void LidarAnalysis::getScanPoints(const uint16_t &angleSteps) {   
    /** TODO (Ex4.2): Read the scan data and transform from polar to cartesian **/
   // Console& con = ch::bfh::roboticsLab::yellow::Console::getInstance();

    rawScanPoints.clear();
    std::vector<int16_t> toAverage[NUMBER_OF_SCANS_TO_AVERAGE];
    for(unsigned int numberOfScans=0;numberOfScans<NUMBER_OF_SCANS_TO_AVERAGE;++numberOfScans)
    {
        //con.printf("Angle:%d\r\n",angleSteps);
        toAverage[numberOfScans] = lidar.getDistances();
    }
    auto rawPoints = toAverage[0];
    for(unsigned int numberOfScans=1;numberOfScans<NUMBER_OF_SCANS_TO_AVERAGE;++numberOfScans)
    {
        for(unsigned int pointCount=0;pointCount<toAverage[numberOfScans].size();++pointCount)
        {
            rawPoints.at(pointCount) +=toAverage[numberOfScans].at(pointCount);

        }
        toAverage[numberOfScans].clear();
    }
    /** Seperate For-Loop after summation because like that the error of dividing an int is smaller than in other methods      */
    for (unsigned int pointsCount=0; pointsCount<rawPoints.size(); ++pointsCount)
    {
        rawPoints.at(pointsCount) = rawPoints.at(pointsCount)/NUMBER_OF_SCANS_TO_AVERAGE;
    }
    for(unsigned int pointsCount=0;pointsCount<rawPoints.size();pointsCount++)
    {
        Point tmpPoint;
        //con.printf("points:%d %d\r\n",rawPoints[pointsCount],pointsCount);
        if(rawPoints[pointsCount]<peripherals::LIDAR_DISTANCE_THRESHOLD && rawPoints[pointsCount]>0)
        {
            tmpPoint.x = (float)rawPoints.at(pointsCount)*cos(pointsCount*angleSteps*util::RAD);
            tmpPoint.y = (float)rawPoints.at(pointsCount)*sin(pointsCount*angleSteps*util::RAD);

            rawScanPoints.push_back(tmpPoint);
        }
    }
    rawScanPoints.push_back(rawScanPoints.back());
    //con.printf(" number of points:%d",rawPoints.size());

    // TODO: Clear out the member `rawScanPoints` to erase the scan data from the last iteration
    // TODO: Read the scan data from the LIDAR member (at a specified step `angleSteps`)
    // TODO: Transform the scan measurements from the polar (distance & angle) to the cartesian space (x,y) in the robot frame.
    // TODO: Add the scan points (now in cartesian space) to the `rawScanPoints` member.
    // NOTE: Ignore all scan data points which are too far away. Refer to the max range of the lidar (peripherals::LIDAR_DISTANCE_THRESHOLD).


}

LidarAnalysis::LineContainer LidarAnalysis::getLines(const double& minRangeDistance, const double& maxLineImprecision, const double& maxAngleBetweenLines) {
    Console& con = ch::bfh::roboticsLab::yellow::Console::getInstance();

    // Make a fresh scan, full resolution (updates member `rawScanPoints`)
    getScanPoints(1);
    con.printf(" number of points:%d",rawScanPoints.size());
    /** TODO (Ex4.5): Split scan points+ in regions/ranges (e.g. left and right wall inside a corridor) **/
    PointRanges pointRegions;
    PointContainer tmpContainer;
   // con.printf("data dumb ra points\r\n");
    for(unsigned int pointCount=1;pointCount<rawScanPoints.size();pointCount++)
    {
        //con.printf("%f %f;\r",rawScanPoints.at(pointCount).x,rawScanPoints.at(pointCount).y);
        //con.printf("distance %f\r\n",distance(rawScanPoints[pointCount],rawScanPoints[pointCount+1]));
        if(distance(rawScanPoints.at(pointCount-1),rawScanPoints.at(pointCount))>minRangeDistance)
        {
            pointRegions.push_back(tmpContainer);
            con.printf("entered if %d\r\n",pointCount);
            tmpContainer.clear();
        }
        tmpContainer.push_back(rawScanPoints.at(pointCount));
        //con.printf("loop:%d size:%d\r\n",pointCount,tmpContainer.size());
    }
    pointRegions.push_back(tmpContainer);

    // TODO: Compare scan points next to each other:
    // --> If the points are "near" (use the `minRangeDistance` parameter), put them in the same point range.
    // --> If the points are further away, create a new point range.
    // NOTE: Use the `distance` method to get the distance between two scan points.

    // TODO: Eventually you can merge the first and last point range. (Again use `minRangeDistance`)
    // TODO: (optional) You may want to erase point ranges with 4 or less scan points.



    /** Find lines with split&merge algorithm **/

    /** TODO (Ex4.6): 1st part: Split point regions into line segments **/

    // TODO: For each range..
    // TODO: .. search for the farest point away from the line between range start and end point.
    // TODO: .. if the furthest point is not "near" enough (see maxLineImprecision), split the range into two ranges.
    // NOTE: Each range will represent a line segment at the end.
    for(unsigned int rangeCount=0;rangeCount<pointRegions.size();++rangeCount)
    {
        bool doSplit=false;
        do
        {
            unsigned int farestPoint=0;
            for(unsigned int pointCount=0;pointCount<pointRegions.at(rangeCount).size();++pointCount)
            {
                //con.printf("loop2:%d\r\n",pointCount);
                if(distance(pointRegions.at(rangeCount).front(),pointRegions.at(rangeCount).back(),pointRegions.at(rangeCount).at(farestPoint))<distance(pointRegions.at(rangeCount).front(),pointRegions.at(rangeCount).back(),pointRegions.at(rangeCount).at(pointCount)))
                {
                        //con.printf("point distance:%f",distance(pointRegions[rangeCount].front(),pointRegions[rangeCount].back(),pointRegions[rangeCount][pointCount]));
                        farestPoint=pointCount;

                }
            }
            //con.printf("point:%d,%d\r\n",farestPoint,pointRegions[rangeCount].size());
            if(pointRegions.at(rangeCount).size()>0)
            {
                if(distance(pointRegions.at(rangeCount).front(),pointRegions.at(rangeCount).back(),pointRegions.at(rangeCount).at(farestPoint))>maxLineImprecision)
                {
                    //con.printf("split point:X%f y:%f \r\n",pointRegions[rangeCount][farestPoint].x,pointRegions[rangeCount][farestPoint].y);
                    PointContainer tmpContainer;
                    //con.printf("l2\n\r");
                    tmpContainer.insert(tmpContainer.end(),pointRegions.at(rangeCount).begin()+farestPoint,pointRegions.at(rangeCount).end());
                    //con.printf("l3\n\r");
                    pointRegions.at(rangeCount).erase(pointRegions.at(rangeCount).begin()+farestPoint,pointRegions.at(rangeCount).end());
                    //con.printf("l4\n\r");
                    pointRegions.insert(pointRegions.begin()+rangeCount+1,tmpContainer);
                    //con.printf("l5\n\r");
                    tmpContainer.clear();
                    doSplit=true;
                }
                else
                {
                    doSplit=false;
                }
            }
            else
            {
                pointRegions.erase(pointRegions.begin()+rangeCount);
            }
        }while(doSplit==true);

    }
    for(unsigned int lineCount=0;lineCount<pointRegions.size();++lineCount)
    {
        if(lineCount==0)
        {
            if(distance(pointRegions.front().front(),pointRegions.back().back())<maxLineImprecision)
            {
                pointRegions.front().insert(pointRegions.front().begin(),pointRegions.back().back());
            }
        }
        else
        {
            if(distance(pointRegions.at(lineCount).front(),pointRegions.at(lineCount-1).back())<maxLineImprecision)
            {
                pointRegions.at(lineCount).insert(pointRegions.at(lineCount).begin(),pointRegions.at(lineCount-1).back());
            }
        }
    }
    for(unsigned int rangeCount=0;rangeCount<pointRegions.size();rangeCount++)
    {
        if(pointRegions.at(rangeCount).size()<3)
        {
            pointRegions.erase(pointRegions.begin()+rangeCount);
        }
    }

    //con.printf("stage 3 complet");
    for(unsigned int tmCount=0;tmCount<pointRegions.size();tmCount++)
    {
       // con.printf("first point: x%f y%f\r\n",pointRegions[tmCount].front().x,pointRegions[tmCount].front().y);
       // con.printf("second point: x%f y%f\r\n",pointRegions[tmCount].back().x,pointRegions[tmCount].back().y);
    }

    //con.printf(" stage 4 complet\r\n");
    /*for(unsigned int rangeCount=0;rangeCount<pointRegions.size();rangeCount++)
    {
        if(pointRegions[rangeCount].size()<=4)
        {
            pointRegions.erase(pointRegions.begin()+rangeCount);
        }
    }*/
    /** TODO: (optional) 2nd part: You may want to merge consecutive line segments that are "collinear enough"(see maxAngleBetweenLines & maxLineImprecision)
     *
     * Calculate the (smallest) angle between two consecutive line segments
     * If the consecutive lines are almost collinear (see maxAngleBetweenLines)..
     * ..look for the most distant point..
     * ..and if that point is further away than "maxLineImprecision", merge the line segments.
     **/
    for(unsigned int lineSegmentCount=0;lineSegmentCount<pointRegions.size();lineSegmentCount++)
    {
        //con.printf("merging %d\r\n",lineSegmentCount);
        if(lineSegmentCount==0)
        {
            float lineLengthCurrent = distance(pointRegions.front().front(),pointRegions.front().back());
            float lineLengthPrevious = distance(pointRegions.back().front(),pointRegions.back().back());

            Point vectorLineCurrent = {.x = pointRegions.front().front().x-pointRegions.front().back().x,.y=pointRegions.front().front().y-pointRegions.front().back().y};
            Point vectorLinePrevious = {.x = pointRegions.back().front().x-pointRegions.back().back().x,.y=pointRegions.back().front().y-pointRegions.back().back().y};

            float angle = (vectorLineCurrent.x*vectorLinePrevious.x+vectorLineCurrent.y*vectorLinePrevious.y)/(lineLengthCurrent*lineLengthPrevious);


            //con.printf("merging2 %f\r\n",angle/util::RAD);
            if(angle>(180-maxAngleBetweenLines)*util::RAD)
            {
                PointContainer tmpPoints(pointRegions.back());
                tmpPoints.insert(tmpPoints.end(),pointRegions.front().begin(),pointRegions.front().end());
                pointRegions.erase(pointRegions.begin());
                pointRegions.erase(pointRegions.end());
                pointRegions.insert(pointRegions.end(),tmpPoints);

            }
        }
        else
        {

            if(distance(pointRegions[lineSegmentCount].front(),pointRegions[lineSegmentCount-1].back())<maxLineImprecision)
            {
                float lineLengthCurrent = distance(pointRegions[lineSegmentCount].front(),pointRegions[lineSegmentCount].back());
                float lineLengthPrevious = distance(pointRegions[lineSegmentCount-1].front(),pointRegions[lineSegmentCount-1].back());

                Point vectorLineCurrent = {.x = pointRegions[lineSegmentCount].front().x-pointRegions[lineSegmentCount].back().x,.y=pointRegions[lineSegmentCount].front().y-pointRegions[lineSegmentCount].back().y};
                Point vectorLinePrevious = {.x = pointRegions[lineSegmentCount-1].front().x-pointRegions[lineSegmentCount-1].back().x,.y=pointRegions[lineSegmentCount-1].front().y-pointRegions[lineSegmentCount-1].back().y};

                float angle = (vectorLineCurrent.x*vectorLinePrevious.x+vectorLineCurrent.y*vectorLinePrevious.y)/(lineLengthCurrent*lineLengthPrevious);

                con.printf("merging2 %f\r\n",angle/util::RAD);
                if(angle>(180-maxAngleBetweenLines)*util::RAD)
                {
                    PointContainer tmpPoints(pointRegions[lineSegmentCount-1]);
                    tmpPoints.insert(tmpPoints.end(),pointRegions[lineSegmentCount].begin(),pointRegions[lineSegmentCount].end());
                    pointRegions.erase(pointRegions.begin()+lineSegmentCount);
                    pointRegions.erase(pointRegions.begin()+lineSegmentCount-1);
                    pointRegions.insert(pointRegions.begin()+lineSegmentCount-1,tmpPoints);

                }
            }
        }
    }

    //con.printf("stage  5 complet");

    /** TODO (Ex4.7): Fill the line container to be returned **/

    LineContainer lines;
    for(unsigned int regioncount=0;regioncount<pointRegions.size();regioncount++)
    {
        Line tmpLine;
        tmpLine.first = pointRegions.at(regioncount).front();
        tmpLine.second= pointRegions.at(regioncount).back();
        lines.push_back(tmpLine);
        //con.printf("x:%f y:%f\r\n",tmpLine.first.x,tmpLine.first.y);
    }
    //con.printf("stage 6 complet");
    /*for(unsigned int pointCount=0;pointCount<rawScanPoints.size();++pointCount)
    {
        Line tmpLine;
        tmpLine.first = rawScanPoints.at(pointCount);
        tmpLine.second = tmpLine.first;
        lines.push_back(tmpLine);
    }*/
    //con.printf("stage 7 complet");
    // TODO: For each line segment inside the `pointRegions` variable you just filled..
    // TODO: .. extract the start and end points..
    // TODO: .. and create a variable of type `Line`.
    // TODO: Add those lines to the line container `lines` to be returned at the end of this method.


    //con.printf("sizeoflines:%d",lines.size());
    return lines;
}

inline double LidarAnalysis::distance(const Point &p1, const Point &p2) {

    /** TODO (Ex4.3): Calculate the euclidian distance [mm] between the points p1 and p2 **/

    double distance = 0;
    distance = sqrt(pow((p1.x-p2.x),2)+pow((p1.y-p2.y),2));
    return distance;
}

inline double LidarAnalysis::distance(const Point &lineStartPoint, const Point &lineEndPoint, const Point &p) {

    /** TODO (Ex4.4): Calculate the orthogonal distance [mm] between a line and a point **/

    double distance = 0;

    double lineLength = LidarAnalysis::distance(lineStartPoint,lineEndPoint);
    distance = abs((lineEndPoint.y-lineStartPoint.y)*p.x-(lineEndPoint.x-lineStartPoint.x)*p.y+lineEndPoint.x*lineStartPoint.y-lineEndPoint.y*lineStartPoint.x)/lineLength;
    /*Point lineVector={.x=lineEndPoint.x-lineStartPoint.x,.y=lineEndPoint.y-lineStartPoint.y};
    Point lineOrtogonalVector = {.x= lineVector.y,.y=-lineVector.x};
    Point projectionVec= {.x=(p.x-lineStartPoint.x),.y=p.y-lineStartPoint.y};
    distance = (projectionVec.x*lineOrtogonalVector.x+projectionVec.y*lineOrtogonalVector.y)/sqrt(pow(lineOrtogonalVector.x,2)+pow(lineOrtogonalVector.y,2));*/
    return distance;
}

}
}
}
}
