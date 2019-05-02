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

    //get lidar points 5 times and save them. after that average that
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

    /** Seperate For-Loop after summation because like that the error of dividing an int is smaller than in if its done in other loop      */
    for (unsigned int pointsCount=0; pointsCount<rawPoints.size(); ++pointsCount)
    {
        rawPoints.at(pointsCount) = rawPoints.at(pointsCount)/NUMBER_OF_SCANS_TO_AVERAGE;
    }
    // check if the mesured point is in the valid range
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
}

LidarAnalysis::LineContainer LidarAnalysis::getLines(const double& minRangeDistance, const double& maxLineImprecision, const double& maxAngleBetweenLines) {
    Console& con = ch::bfh::roboticsLab::yellow::Console::getInstance();

    // Make a fresh scan, full resolution (updates member `rawScanPoints`)
    getScanPoints(1);
    // seperate raw data into regions which belong together
    PointRanges pointRegions;
    PointContainer tmpContainer;
    for(unsigned int pointCount=1;pointCount<rawScanPoints.size();pointCount++)
    {
        // check distance, if distance is grater than specified, seperate
        if(distance(rawScanPoints.at(pointCount-1),rawScanPoints.at(pointCount))>minRangeDistance)
        {
            pointRegions.push_back(tmpContainer);
            //con.printf("entered if %d\r\n",pointCount);
            tmpContainer.clear();
        }
        tmpContainer.push_back(rawScanPoints.at(pointCount));
        //con.printf("loop:%d size:%d\r\n",pointCount,tmpContainer.size());
    }
    pointRegions.push_back(tmpContainer);

    /** Find lines with split&merge algorithm **/
    //split
    for(unsigned int rangeCount=0;rangeCount<pointRegions.size();++rangeCount)
    {
        bool doSplit=false;
        do
        {
            unsigned int farestPoint=0;
            for(unsigned int pointCount=0;pointCount<pointRegions.at(rangeCount).size();++pointCount)
            {

                if(distance(pointRegions.at(rangeCount).front(),pointRegions.at(rangeCount).back(),pointRegions.at(rangeCount).at(farestPoint))<distance(pointRegions.at(rangeCount).front(),pointRegions.at(rangeCount).back(),pointRegions.at(rangeCount).at(pointCount)))
                {

                        farestPoint=pointCount;

                }
            }

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
    // erase region with 3 points or less
    for(unsigned int rangeCount=0;rangeCount<pointRegions.size();rangeCount++)
    {
        if(pointRegions.at(rangeCount).size()<3)
        {
            pointRegions.erase(pointRegions.begin()+rangeCount);
        }
    }

    // calculates the angle between consecutive lines. merges them into one when the angle is less than the angle specieifed in: MAX_ANGLE_BETWEEN_LINES_DEFAULT
    for(unsigned int lineSegmentCount=0;lineSegmentCount<pointRegions.size();lineSegmentCount++)
    {
        //con.printf("merging %d\r\n",lineSegmentCount);
        // first and last line
        if(lineSegmentCount==0)
        {
            if(distance(pointRegions.front().front(),pointRegions.back().back())<maxLineImprecision)
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
        }
        else
        {
            //other lines
            if(distance(pointRegions[lineSegmentCount].front(),pointRegions[lineSegmentCount-1].back())<maxLineImprecision)
            {
                float lineLengthCurrent = distance(pointRegions[lineSegmentCount].front(),pointRegions[lineSegmentCount].back());
                float lineLengthPrevious = distance(pointRegions[lineSegmentCount-1].front(),pointRegions[lineSegmentCount-1].back());

                Point vectorLineCurrent = {.x = pointRegions[lineSegmentCount].front().x-pointRegions[lineSegmentCount].back().x,.y=pointRegions[lineSegmentCount].front().y-pointRegions[lineSegmentCount].back().y};
                Point vectorLinePrevious = {.x = pointRegions[lineSegmentCount-1].front().x-pointRegions[lineSegmentCount-1].back().x,.y=pointRegions[lineSegmentCount-1].front().y-pointRegions[lineSegmentCount-1].back().y};

                float angle = (vectorLineCurrent.x*vectorLinePrevious.x+vectorLineCurrent.y*vectorLinePrevious.y)/(lineLengthCurrent*lineLengthPrevious);

                //con.printf("merging2 %f\r\n",angle/util::RAD);
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


    /** Fill the line container to be returned **/

    LineContainer lines;
    for(unsigned int regioncount=0;regioncount<pointRegions.size();regioncount++)
    {
        Line tmpLine;
        tmpLine.first = pointRegions.at(regioncount).front();
        tmpLine.second= pointRegions.at(regioncount).back();
        lines.push_back(tmpLine);
        //con.printf("x:%f y:%f\r\n",tmpLine.first.x,tmpLine.first.y);
    }
    con.printf("stage 7 complet");
    //con.printf("sizeoflines:%d",lines.size());
    return lines;
}

inline double LidarAnalysis::distance(const Point &p1, const Point &p2) {

    /** Calculate the euclidian distance [mm] between the points p1 and p2 **/

    double distance = 0;
    distance = sqrt(pow((p1.x-p2.x),2)+pow((p1.y-p2.y),2));
    return distance;
}

inline double LidarAnalysis::distance(const Point &lineStartPoint, const Point &lineEndPoint, const Point &p) {

    /** Calculate the orthogonal distance [mm] between a line and a point **/

    double distance = 0;

    double lineLength = LidarAnalysis::distance(lineStartPoint,lineEndPoint);
    distance = abs((lineEndPoint.y-lineStartPoint.y)*p.x-(lineEndPoint.x-lineStartPoint.x)*p.y+lineEndPoint.x*lineStartPoint.y-lineEndPoint.y*lineStartPoint.x)/lineLength;
    return distance;
}

}
}
}
}
