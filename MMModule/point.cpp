#include "point.h"
#include <math.h>
#include <algorithm>


bool Point::samePointAs(Point p) {
    return (fabs(m_x - p.m_x) < EPS) && (fabs(m_y - p.m_y) < EPS);
}

double Point::distance2pt(Point pt) {
    return sqrt(pow(pt.m_x-this->m_x,2)+pow(pt.m_y-this->m_y,2));
}

double Point::distance2ptsegment(Point A,Point B) {
    if (A.samePointAs(B))     {
        return this->distance2pt(A);
    }
    else {
        double num = (this->m_x - A.m_x) * (B.m_x - A.m_x) + (this->m_y - A.m_y) * (B.m_y - A.m_y);
        double tSol = num / pow(A.distance2pt(B),2);
        double t = std::max(0.0, std::min(1.0, tSol));
        Point proj(A.m_x + t * (B.m_x - A.m_x), A.m_y + t * (B.m_y - A.m_y));

        return this->distance2pt(proj);
    }
}

double Point::y() const
{
    return m_y;
}

void Point::setY(double y)
{
    m_y = y;
}

long Point::id() const
{
    return m_id;
}

void Point::setId(long id)
{
    m_id = id;
}

double Point::x() const
{
    return m_x;
}

void Point::setX(double x)
{
    m_x = x;
}


