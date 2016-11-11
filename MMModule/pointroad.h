#ifndef POINTROAD_H
#define POINTROAD_H

#include <vector>
#include "point.h"

class PointRoad : public Point {
public:
    /**
     * @brief Constructor for Road points
     * @param x
     * @param y
     */
    PointRoad(double x, double y, bool isNode)
        : Point(x,y)
        , m_isNode(isNode)
        , m_id(counter++)
    {
    }

protected:
    static long counter;    // counter used to generate unique m_id
    bool m_isNode;  // true if this point is an extremity of a road
    long m_id;      // unique id of the point
    std::vector<long> m_belongToRoadId;  // list of road sharing the point
};


long PointRoad::counter = 0;

#endif // POINTROAD_H
