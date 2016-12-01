#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <vector>
/**
  * @file point.h
  * @brief Class Point
  */

/**
  * @brief Used to compare doubles
  */
#define EPS 1e-12

/**
 * @brief The Point class
 */

class Point {
public:
    Point() {} // should never be used !!

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
     * @brief Point Class's Destructor
     */
    virtual ~Point() {}

    /**
     * @brief Check if two points share the same coordinates
     * @param p Point to compare
     * @return true or false
     */
    bool samePointAs(const Point& p) const;

    /**
     * @brief Calculate distance between two points
     * @param p Point to compare
     * @return Euclidian distance
     */
    double distanceToPoint(const Point& p) const;

    std::vector<double> projectionOnSegment(const Point& a, const Point& b) const;

    /**
     * @brief Compute the distance between a point and a segment
     * @param p1 A point corresponding to one extremity of the segment
     * @param p2 The other extremity
     * @return Value of distance
     */
    double distanceToSegment(const Point& p1, const Point& p2) const;

    virtual std::string infos() const;

    /**
     * @name Setters and getters of x & y
     */
    //@{
    double x() const; /**< x getter */
    void setx(double x); /**< x setter */
    double y() const; /**< y getter */
    void sety(double y); /**< y setter */
    //@}

    /**
     * @brief x the accessor for the KDtree
     * @param dim this value must be 0 for x and 1 for y
     * @return m_x or m_y depending on the dim value
     */
    double x(int dim) const;
    void setx(int dim, double value); /**< set m_x or m_y according to dim value */

protected:
    /**
     * @name The point's coordinates
     */
    //@{
    double m_x; /**< x coordinate*/
    double m_y; /**< y coordinate*/
    //@}

    static const double POINT_RADIUS; /**< max radius around a point used to look for roads */
};

#endif // POINT_H
