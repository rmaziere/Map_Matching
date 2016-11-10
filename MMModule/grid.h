#ifndef GRID_H
#define GRID_H

#include "road.h"
#include "track.h"

#include <QString>
#include <vector>
using namespace std;
class grid {
public:
    grid();
    virtual ~grid();

    /**
     * @brief setZone Save data about our area of roads
     * @param xMin Coordinate xMin of a track
     * @param xMax Coordinate xMax of a track
     * @param yMin Coordinate yMin of a track
     * @param yMax Coordinate yMax of a track
     */
    void setZone(double xMin,double xMax,double yMin,double yMax);

    /**
     * @brief readFromCSV Reads a csv file and inserts info into the corresponding attributs
     * @param filename the filepath/filename for the csv file to read
     */
    void readFromCSV(QString filename);

    /**
     * @brief addRoad Creates a new road and inserts it in m_road
     */
    void addRoad(vector<vector<double> > listOfCoordinates, long edgeId, long fromNodeId, long toNodeId);

    std::vector<Road*> getListOfRoad() const;

    std::vector<Road*> m_road;

    /**
     * @brief inFootPrint Test if a point is in the defined area of a track
     * @param x Coordinate x of a point
     * @param y Coordinate x of a point
     * @return true or false
     */
    bool inFootPrint(double x,double y);

    /**
     * @brief Parametres of the square
     */
    double m_xMin;
    double m_xMax;
    double m_yMin;
    double m_yMax;

};

#endif // GRID_H
