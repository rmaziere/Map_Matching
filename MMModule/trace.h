#ifndef TRACE_H
#define TRACE_H

#include "pointTrace.h"
#include <vector>
#include <string>
#include <iostream>     // cout
#include <fstream>      // ifstream
#include <sstream>
#include <QString>
#include <QStringList>

/**
 * @brief The Trace class
 */
class Trace
{
public:
    Trace();
    virtual ~Trace();
    /**
     * @brief readFromCSV Reads a csv file and inserts each point in m_points vector
     * @param filename the filepath/filename for the csv file to read
     */
    void readFromCSV(QString filename);

    /**
     * @brief getPoints Get the m_points vector
     * @return The vector of points pointer
     */
    std::vector<PointTrace*> getPoints();
private:
    /**
     * @brief addPoint Creates a new point and inserts it in m_points
     * @param latitude the latitude of the inserted point
     * @param longitude the longitude of the inserted point
     * @param altitude the altitude of the inserted point
     * @param timeStamp the timeStamp of the inserted point
     */
    void addPoint(float latitude, float longitude, float altitude, QDateTime timeStamp);
    /**
     * @brief m_points Vector where points of the trace are saved
     */
    std::vector<PointTrace*> m_points;
};

#endif // TRACE_H
