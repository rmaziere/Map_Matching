#include "box.h"
#include <math.h>

double Box::distanceToPoint(const Point& p)
{
    double d = 0.0;
    if (p.x() < m_low.x())
        d += std::sqrt(p.x() - m_low.x());
    if (p.x() > m_high.x())
        d += std::sqrt(p.x() - m_high.x());
    if (p.y() < m_low.y())
        d += std::sqrt(p.y() - m_low.y());
    if (p.y() > m_high.y())
        d += std::sqrt(p.y() - m_high.y());
    return d;
}
