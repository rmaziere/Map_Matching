#ifndef POINT_H
#define POINT_H

#define POINT_GPS -2
#define POINT_INSIDE -1

class Point {
public:
    //Point(): m_id(-1), m_x(0.0), m_y(0.0) {}
    Point(double x, double y):m_id(POINT_GPS), m_x(x), m_y(y) {}    // used for a GPS point
    Point(long id, double x, double y):m_id(id), m_x(x), m_y(y){}   // used for a point in a road

    double distance2pt(Point pt);
    double distance2ptsegment(Point A,Point B);


    long m_id;  // id when this point is an extremity of a road (-1 otherwise)
    double m_x, m_y; // coordinates in metric system

};

#endif // POINT_H
