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

    // TODO: Clear out the member `rawScanPoints` to erase the scan data from the last iteration
    // TODO: Read the scan data from the LIDAR member (at a specified step `angleSteps`)
    // TODO: Transform the scan measurements from the polar (distance & angle) to the cartesian space (x,y) in the robot frame.
    // TODO: Add the scan points (now in cartesian space) to the `rawScanPoints` member.
    // NOTE: Ignore all scan data points which are too far away. Refer to the max range of the lidar (peripherals::LIDAR_DISTANCE_THRESHOLD).


}

LidarAnalysis::LineContainer LidarAnalysis::getLines(const double& minRangeDistance, const double& maxLineImprecision, const double& maxAngleBetweenLines) {

    // Make a fresh scan, full resolution (updates member `rawScanPoints`)
    getScanPoints(1);

    /** TODO (Ex4.5): Split scan points in regions/ranges (e.g. left and right wall inside a corridor) **/

    PointRanges pointRegions;

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



    /** TODO: (optional) 2nd part: You may want to merge consecutive line segments that are "collinear enough"(see maxAngleBetweenLines & maxLineImprecision)
     *
     * Calculate the (smallest) angle between two consecutive line segments
     * If the consecutive lines are almost collinear (see maxAngleBetweenLines)..
     * ..look for the most distant point..
     * ..and if that point is further away than "maxLineImprecision", merge the line segments.
     **/



    /** TODO (Ex4.7): Fill the line container to be returned **/

    LineContainer lines;

    // TODO: For each line segment inside the `pointRegions` variable you just filled..
    // TODO: .. extract the start and end points..
    // TODO: .. and create a variable of type `Line`.
    // TODO: Add those lines to the line container `lines` to be returned at the end of this method.



    return lines;
}

inline double LidarAnalysis::distance(const Point &p1, const Point &p2) {

    /** TODO (Ex4.3): Calculate the euclidian distance [mm] between the points p1 and p2 **/

    double distance = 0;
    return distance;
}

inline double LidarAnalysis::distance(const Point &lineStartPoint, const Point &lineEndPoint, const Point &p) {

    /** TODO (Ex4.4): Calculate the orthogonal distance [mm] between a line and a point **/

    double distance = 0;
    return distance;
}

}
}
}
}
