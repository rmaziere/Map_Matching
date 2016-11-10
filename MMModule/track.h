#ifndef TRACK_H
#define TRACK_H

#include "pointGPS.h"
#include <QString>
#include <QStringList>
#include <fstream> // ifstream
#include <iostream> // cout
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief The Track class
 */
class Track {
public:
    Track();
    virtual ~Track();
    /**
     * @brief readFromCSV Reads a csv file and inserts each point in m_points vector
     * @param filename the filepath/filename for the csv file to read
     */
    void readFromCSV(QString filename);

    /**
     * @brief getPoints Get the m_points vector
     * @return The vector of points pointer
     */
    std::vector<PointGPS*> getPoints();

    /**
     * @brief delPointGPS deletes a occurence
     * @param pointer the pointer of the occurrence to delete
     * @return nothing
     */
    void delPointGPS(int occurrence);

    //private:
    /**
     * @brief addPoint Creates a new point and inserts it in m_points
     * @param latitude the latitude of the inserted point
     * @param longitude the longitude of the inserted point
     * @param altitude the altitude of the inserted point
     * @param timeStamp the timeStamp of the inserted point
     */
    void addPoint(double x, double y, float latitude, float longitude, float altitude, QDateTime timeStamp);

    /**
     * @brief addPoint Creates a new point and inserts it in m_points
     * @param latitude the latitude of the inserted point
     * @param longitude the longitude of the inserted point
     * @param altitude the altitude of the inserted point
     * @param timeStamp the timeStamp of the inserted point
     */
    void addPoint(float latitude, float longitude, float altitude, QDateTime timeStamp);
    /**
     * @brief m_points Vector where points of the Track are saved
     */
    std::vector<PointGPS*> m_points;
};

#endif // TRACK_H
