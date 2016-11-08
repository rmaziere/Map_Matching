#ifndef POINTGPS_H
#define POINTGPS_H

#include <QObject>
#include <QDateTime>

class PointGPS
{
    public:
        /**
         * @brief PointGPS constructor
         * Create a new Point Trace with default parameters :
         * latitude = 0
         * longitude = 0
         * altitude = 0
         * timeStamp = currentDate
         */
        PointGPS();

        /**
         * @brief PointGPS constructor
         * Create a new Point GPS
         */
        PointGPS(float latitude, float longitude, float altitude, QDateTime timeStamp);

        /**
         * @brief getLatitude Getter for m_latitude parameter
         * @return float the latitude
         */
        float getLatitude();

        /**
         * @brief getLongitude Getter for m_longitude parameter
         * @return float the longitude
         */
        float getLongitude();

        /**
         * @brief getAltitude Getter for m_altitude parameter
         * @return float the altitude
         */
        float getAltitude();

        /**
         * @brief getTimeStamp Getter for m_timeStamp parameter
         * @return QDateTime the timeStamp
         */
        QDateTime getTimeStamp();

    private:
        float m_latitude;
        float m_longitude;
        float m_altitude;
        QDateTime m_timeStamp;
};
#endif // POINTGPS_H
