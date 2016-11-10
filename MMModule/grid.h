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

    bool inFootPrint(double lat,double lon);

    double latMin;
    double latMax;
    double longMin;
    double longMax;

};

#endif // GRID_H
