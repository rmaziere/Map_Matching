#ifndef TRACK_H
#define TRACK_H

/**
  * @file track.h
  * @brief The class Track
  */

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
    /**
     * @brief Track's Constructor
     */
    Track() :
        //m_points(0),
          m_xMin(std::numeric_limits<double>::max()),
          m_xMax(0.0),
          m_yMin(std::numeric_limits<double>::max()),
          m_yMax(0.0)
    {}
    virtual ~Track();

    /**
     * @brief Reads a csv file and inserts each point in m_points vector
     * @param filename the filepath/filename.fileExtension for the csv file to read
     */
    void readFromCSV(QString filename);

    /**
     * @brief Deletes a occurence
     * @param The pointer of the occurrence to delete
     */
    void delPointGPS(int occurrence);

    /**
     * @brief Creates a new point and inserts it in m_points
     * @param the x coordinate
     * @param the y coordinate
     * @param the altitude of the inserted point
     * @param the timeStamp of the inserted point
     */
    void addPoint(double x, double y, float altitude, unsigned int timeStamp);

    /**
     * @brief This is a space filter, which deletes points depending on a distance interval
     * @param interval : minimal wished between two points in meters
     */
    void spaceFilter(double interval);

    /**
     * @brief This is a temporal filter, which deletes points depending on a time value
     * @param interval : Time value in seconds
     */
    void temporalFilter(uint interval);

    /**
     * @brief Update the enclosing box of the track
     * @param x Coordinate x of a point
     * @param y Coordinate x of a point
     */
    void updateBox(double x, double y);

    /**
     * @brief Apply a threshold to bounding box once the data file has been read
     */
    void applyThresholdToBox();

    /**
     * @brief Print some informations to user in console
     */
    void outputInfos();

    /**
     * @brief getPoints Get the m_points vector
     * @return The vector of points pointer
     */
    std::vector<PointGPS*> getPoints();

    //TODO protected
    /**
     * @name The coordinates of the bounding box.
     */
    //@{
    double m_xMin;  /**< The x min value*/
    double m_xMax;  /**< The x max value*/
    double m_yMin;  /**< The y min value*/
    double m_yMax;  /**< The y max value*/
    //@}

protected:
    /**
     * @brief m_points Vector where points of the Track are saved
     */
    std::vector<PointGPS*> m_points;    /**< Vector of points*/
    //Point m_southWest, m_northEst;    /**< englobing box*/
    std::string m_trackFullName;        /**< Name of the track */

};

#endif // TRACK_H
