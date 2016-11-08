#ifndef POINT_H
#define POINT_H


class Point {
public:
    Point(double x, double y):m_id(-1), m_x(x), m_y(y) {}
    Point(long id, double x, double y):m_id(id), m_x(x), m_y(y){}

    long m_id;  // id when this point is an extremity of a road (-1 otherwise)
    double m_x, m_y; // coordinates in metric system
};

#endif // POINT_H
