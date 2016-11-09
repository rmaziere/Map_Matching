#include "pointGPS.h"


PointGPS::PointGPS()
    : Point(0.0,0.0)
    , m_latitude(0)
    , m_longitude(0)
    , m_altitude(0)
    , m_timeStamp(QDateTime::currentDateTime())
{

}


PointGPS::PointGPS(float latitude, float longitude, float altitude, QDateTime timeStamp)
    : Point(0.0,0.0)
    , m_latitude(latitude)
    , m_longitude(longitude)
    , m_altitude(altitude)
    , m_timeStamp(timeStamp)
{

}


PointGPS::PointGPS(double x, double y, float latitude, float longitude, float altitude, QDateTime timeStamp)
    : Point(x, y)
    , m_latitude(latitude)
    , m_longitude(longitude)
    , m_altitude(altitude)
    , m_timeStamp(timeStamp)
{

}

float PointGPS::getLatitude()
{
    return m_latitude;
}

float PointGPS::getLongitude()
{
    return m_longitude;
}

float PointGPS::getAltitude()
{
    return m_altitude;
}

QDateTime PointGPS::getTimeStamp()
{
    return m_timeStamp;
}
