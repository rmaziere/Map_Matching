#ifndef POINT_H
#define POINT_H

#define EPS 1e-12 // for double comparisons

class Point {
public:
    /**
     * @brief Constructor for GPS points
     * @param x
     * @param y
     */
    Point(double x, double y)
        : m_x(x)
        , m_y(y)
    {
    }

    /**
     * @brief samePointAs Check if two points share the same coordinates
     * @param p Point to compare
     * @return true or false
     */
    bool samePointAs(const Point& p) const;

    /**
     * @brief distanceToPoint Calculate distance between two points
     * @param p Point
     * @return euclidian distance
     */
    double distanceToPoint(const Point& p) const;

    /**
     * @brief distanceToSegment Compute the distance between a point and a segment
     * @param p1 A point corresponding to one extremity of the segment
     * @param p2 The other extremity
     * @return Value of distance
     */
    double distanceToSegment(const Point& p1, const Point& p2) const;

    // accessors
    double x() const;
    void setX(double x);
    double y() const;
    void setY(double y);

protected:
    double m_x, m_y; // coordinates in metric system
};

#endif // POINT_H
