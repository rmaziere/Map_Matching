#include "point.h"
#include <math.h>
#include <algorithm>


Point::Point(double x, double y):
    m_id(POINT_GPS), m_x(x), m_y(y)
    {}    // used for a GPS point

Point::Point(long id, double x, double y):
    m_id(id), m_x(x), m_y(y)
    {}   // used for a point in a road

double Point::distance2pt(Point pt)
{
    return sqrt(pow(pt.m_x-this->m_x,2)+pow(pt.m_y-this->m_y,2));
}

double Point::distance2ptsegment(Point A,Point B)
{
    if ((B.m_x == A.m_x) && (B.m_y == A.m_y))
    {
        return this->distance2pt(A);
    }
    else
    {
        double num = (this->m_x - A.m_x) * (B.m_x - A.m_x) + (this->m_y - A.m_y) * (B.m_y - A.m_y);
        double tSol = num / pow(A.distance2pt(B),2);
        double t = std::max(0.0, std::min(1.0, tSol));
        Point proj(A.m_x + t * (B.m_x - A.m_x), A.m_y + t * (B.m_y - A.m_y));

        return this->distance2pt(proj);
    }
}


