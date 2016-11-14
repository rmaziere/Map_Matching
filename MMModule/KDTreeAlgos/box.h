#ifndef BOX_H
#define BOX_H

#include "../point.h"

class Box
{
public:
    Box() {}
    Box(const Point &low, const Point &high)
        : m_low(low), m_high(high) {}

    double distanceToPoint(const Point &point);

    // accessors
    const Point *low() const { return &m_low;}
    const Point *high() const { return &m_high;}

protected:
    Point m_low;
    Point m_high;
};

#endif // BOX_H
