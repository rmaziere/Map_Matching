#ifndef POINT_H
#define POINT_H

#define POINT_GPS -2
#define POINT_INSIDE -1
#define EPS 1e-12

class Point {
public:
    Point(double x, double y):m_id(POINT_GPS), m_x(x), m_y(y) {}    // used for a GPS point
    Point(long id, double x, double y):m_id(id), m_x(x), m_y(y){}   // used for a point in a road

    bool samePointAs(Point p);

    /**
     * @brief distance2pt Calculate distance between two points
     * @param pt Point (x,y)
     * @return Value of distance
     */
    double distance2pt(Point pt);

    /**
     * @brief distance2ptsegment Calculate distance between a point and a segment
     * @param A First point of the segment (x,y)
     * @param B Last Point of the segment (x,y)
     * @return Value of distance
     */
    double distance2ptsegment(Point A, Point B);

    double x() const;
    void setX(double x);
    double y() const;
    void setY(double y);
    long id() const;
    void setId(long id);

    long m_id;  // id when this point is an extremity of a road (-1 otherwise)
    double m_x, m_y; // coordinates in metric system

};

#endif // POINT_H
