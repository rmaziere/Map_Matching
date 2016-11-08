#ifndef DISTANCE_H
#define DISTANCE_H

#include <point.h>

#include <vector>
#include <math.h>

class Distance
{
public:
    /**
     * @brief Distance
     */
    Distance();
    /**
     * @brief distance2pt Calculate distance between two points
     * @param pt1 First point (x,y)
     * @param pt2 Last point (x,y)
     * @return value of sqrt((pt1.x - pt2.x)² + (pt1.y - pt2.y)²)
     */
    double distance2pt(Point pt1,Point pt2);
    /**
     * @brief distance2ptsegment Calculate distance between a point and a segment
     * @param A First point of the segment (x,y)
     * @param B Last Point of the segment (x,y)
     * @param pt Point (x,y)
     * @return value of distance
     */
    double distance2ptsegment(Point A,Point B, Point pt);

};

#endif // DISTANCE_H
