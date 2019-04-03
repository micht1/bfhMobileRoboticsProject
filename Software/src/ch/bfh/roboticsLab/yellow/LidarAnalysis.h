#line 2 "ch/bfh/roboticsLab/yellow/LidarAnalysis.h"
/* LidarAnalysis.h
 * Copyright (c) BFH roboticsLab
 * All rights reserved.
 */

#pragma once

#include <ch/bfh/roboticsLab/yellow/driver/LIDAR.h>
#include <vector>

namespace ch {
namespace bfh {
namespace roboticsLab {
namespace yellow {

/**
 * This class implements the LIDAR data analysis.
 * @author irislisa.naef@bfh.ch
 */
class LidarAnalysis {

public:

    /** This class defines a Cartesian point. */
    struct Point {
        /** X coordinate. */
        double x;
        /** Y coordinate. */
        double y;
    };

    /** Line type: a pair of Points */
    using Line = std::pair<Point, Point>;
    /** Line container type: a vector of lines. */
    using LineContainer = std::vector<Line>;

    /** Default minimum distance between two line regions (e.g. two opposite walls viewed from inside the corridor) [mm]. */
    static constexpr float MIN_RANGE_DISTANCE_DEFAULT = 100;

    /** Default maximum distance from a point to a line, in order for that point to belong to that line [mm]. */
    static constexpr float MAX_LINE_IMPRECISION_DEFAULT = 50;

    /** Default maximum angle between lines [deg]. */
    static constexpr float MAX_ANGLE_BETWEEN_LINES_DEFAULT = 150;

    /** Retrieve the singleton of the LidarAnalysis object. */
    static LidarAnalysis& getInstance();

    /** Destroy the singleton object. */
    virtual ~LidarAnalysis() {
    }

    /**
     * @brief Get raw scan points for a specific angle step.
     * @param angleSteps Angle steps to read data [°]
     */
    void getScanPoints(const uint16_t& angleSteps = 1);

    /**
     * @brief Feauture Extraction: Find lines (split & merge algorithm)
     * @param minRangeDistance Minimum distance between two line regions (e.g. two opposite walls viewed from inside the corridor) [mm]. Defaults to MIN_RANGE_DISTANCE_DEFAULT.
     * @param maxLineImprecision Maximum distance from a point to a line, in order for that point to belong to that line [mm]. Defaults to MAX_LINE_IMPRECISION_DEFAULT.
     * @param maxAngleBetweenLines maximum angle between lines [deg]. Defaults to MAX_ANGLE_BETWEEN_LINES_DEFAULT.
     * @return container with found lines.
     */
    LineContainer getLines(const double& minRangeDistance = MIN_RANGE_DISTANCE_DEFAULT,
                           const double& maxLineImprecision = MAX_LINE_IMPRECISION_DEFAULT,
                           const double& maxAngleBetweenLines = MAX_ANGLE_BETWEEN_LINES_DEFAULT);

private:

    /** Point container type: vector of points. */
    using PointContainer = std::vector<Point>;
    /** Collection of point ranges (of point containers) */
    using PointRanges = std::vector<PointContainer>;

    /**
     * Creates a new LidarAnalysis object that will read LIDAR data from the given reference.
     */
    LidarAnalysis();
    /** Private empty constructor to force usage of #getInstance. */
    LidarAnalysis(LidarAnalysis const&);
    /** Private equals operator to force usage of #getInstance. */
    void operator=(LidarAnalysis const&);

    /** LIDAR instance to read scan from */
    driver::LIDAR& lidar;

    /** Raw scan points in robot frame (cartesian space). */
    std::vector<Point> rawScanPoints;

    /**
     * @brief Calculate distance between two points.
     * @param p1 Point 1 [mm]
     * @param p2 Point 2 [mm]
     * @return distance between points [mm]
     */
    inline double distance(const Point& p1, const Point& p2);

    /**
     * @brief Calculate (perpendicular) distance between a line and a point.
     * @param lineStartPoint Start point of line [mm]
     * @param lineEndPoint End point of line [mm]
     * @param p Point to get the distance to [mm]
     * @return distance between line and point [mm]
     */
    inline double distance(const Point& lineStartPoint, const Point& lineEndPoint, const Point& p);
};

}
}
}
}
