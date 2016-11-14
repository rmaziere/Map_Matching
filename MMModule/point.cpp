#include "point.h"
#include <algorithm>
#include <math.h>
#include <iomanip>
#include <sstream>

bool Point::samePointAs(const Point &p) const
{
    return (fabs(m_x - p.m_x) < EPS) && (fabs(m_y - p.m_y) < EPS);
}

double Point::distanceToPoint(const Point& p) const
{
    return sqrt(pow(p.m_x - this->m_x, 2) + pow(p.m_y - this->m_y, 2));
}

double Point::distanceToSegment(const Point& a, const Point& b) const
{
    if (a.samePointAs(b)) {
        return this->distanceToPoint(a);
    } else {
        double num = (this->m_x - a.m_x) * (b.m_x - a.m_x) + (this->m_y - a.m_y) * (b.m_y - a.m_y);
        double tSol = num / pow(a.distanceToPoint(b), 2);
        double t = std::max(0.0, std::min(1.0, tSol));
        Point proj(a.m_x + t * (b.m_x - a.m_x), a.m_y + t * (b.m_y - a.m_y));
        return this->distanceToPoint(proj);
    }
}


std::string Point::infos() const
{
    std::stringstream ss;
    ss << "(" << std::fixed << std::setprecision(2) << m_x << ", " << m_y << ")";
    return ss.str();
}

double Point::y() const
{
    return m_y;
}

void Point::sety(double y)
{
    m_y = y;
}

double Point::x(int dim) const
{
    return (dim==0)?m_x:m_y;
}

void Point::setx(int dim, double value)
{
    if (dim==0) m_x= value; else m_y= value;
}

double Point::x() const
{
    return m_x;
}

void Point::setx(double x)
{
    m_x = x;
}
