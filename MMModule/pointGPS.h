#ifndef POINTGPS_H
#define POINTGPS_H

#include "emissionprobability.h"
#include "point.h"
#include <vector>

#define ALT_DEFAULT 0.0
class PointGPS : public Point {
public:
    /**
     * @brief PointGPS constructor
     * Create a new Point GPS with default altitude
     */
    PointGPS(double x, double y, unsigned int timestamp)
        : Point(x, y)
        , m_altitude(ALT_DEFAULT)
        , m_timeStamp(timestamp)
    {
    }

    /**
     * @brief PointGPS constructor
     * Create a new Point GPS
     */
    PointGPS(double x, double y, float altitude, unsigned int timestamp)
        : Point(x, y)
        , m_altitude(altitude)
        , m_timeStamp(timestamp)
    {
    }

    void addEmissionProbability(long roadId, double distance);

    std::string infos() const;

    // accessors
    unsigned int timeStamp() const { return m_timeStamp; }
    float altitude() const { return m_altitude; }
protected:
    float m_altitude; // TODO keep ?
    unsigned int m_timeStamp; // WARNING in second
    std::vector<EmissionProbability> m_emissionProbability;
};
#endif // POINTGPS_H
