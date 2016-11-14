#ifndef TRACK_H
#define TRACK_H

#include "pointGPS.h"

#include <QString>
#include <QStringList>
#include <QDateTime>
#include <fstream> // ifstream
#include <iostream> // cout
#include <sstream>
#include <string>
#include <vector>


#define DISTANCE_THRESHOLD 200  // from paper

/**
 * @brief The Track class
 */
class Track {
public:
    Track()
        : //m_points(0),
          m_xMin(std::numeric_limits<double>::max()),
          m_xMax(0.0),
          m_yMin(std::numeric_limits<double>::max()),
          m_yMax(0.0)
    {
    }
    virtual ~Track();

    /**
     * @brief readFromCSV Reads a csv file and inserts each point in m_points vector
     * @param filename the filepath/filename for the csv file to read
     */
    void readFromCSV(QString filename);


    /**
     * @brief delPointGPS deletes a occurence
     * @param pointer the pointer of the occurrence to delete
     */
    void delPointGPS(int occurrence);


    /**
     * @brief addPoint Creates a new point and inserts it in m_points
     * @param altitude the altitude of the inserted point
     * @param timeStamp the timeStamp of the inserted point
     */
    void addPoint(double x, double y, float altitude, unsigned int timeStamp);


    /**
     * @brief spaceFilter delete points in function of the interval input
     * @param interval minimal wished between two points
     */
    void spaceFilter(double interval);

    /**
     * @brief temporalFiltering
     */
    void temporalFilter(uint interval);

    /**
     * @brief updateBox update the enclosing box of the track
     * @param x Coordinate x of a point
     * @param y Coordinate x of a point
     */
    void updateBox(double x, double y);

    /**
     * @brief applyThresholdToBox apply a threshold to bounding box once
     * the data file has been read
     */
    void applyThresholdToBox();

    void outputInfos();



    /**
     * @brief getPoints Get the m_points vector
     * @return The vector of points pointer
     */
    std::vector<PointGPS*> getPoints();


    /** TODO protected
     * @brief Parametres of the bounding box
     */
    double m_xMin;
    double m_xMax;
    double m_yMin;
    double m_yMax;

protected:
    /**
     * @brief m_points Vector where points of the Track are saved
     */
    std::vector<PointGPS*> m_points;
    //Point m_southWest, m_northEst;  // describe englobing box  (could replace the 4 coordinates ?)
    std::string m_trackFullName;

};

#endif // TRACK_H
