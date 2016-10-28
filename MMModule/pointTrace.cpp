#include "pointTrace.h"

PointTrace::PointTrace()
    : m_latitude(0)
    , m_longitude(0)
    , m_altitude(0)
    , m_timeStamp(QDateTime::currentDateTime())
{

}


PointTrace::PointTrace(float latitude, float longitude, float altitude, QDateTime timeStamp)
    : m_latitude(latitude)
    , m_longitude(longitude)
    , m_altitude(altitude)
    , m_timeStamp(timeStamp)
{

}

float PointTrace::getLatitude()
{
    return m_latitude;
}

float PointTrace::getLongitude()
{
    return m_longitude;
}

float PointTrace::getAltitude()
{
    return m_altitude;
}

QDateTime PointTrace::getTimeStamp()
{
    return m_timeStamp;
}
