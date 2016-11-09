#ifndef GRID_H
#define GRID_H

#include "road.h"
#include <QString>
#include <vector>
using namespace std;
class grid {
public:
    grid();
    virtual ~grid();
    /**
     * @brief readFromCSV Reads a csv file and inserts info into the corresponding attributs
     * @param filename the filepath/filename for the csv file to read
     */
    void readFromCSV(QString filename);
    /**
    * @brief m_points Vector where roads are saved
    */
    std::vector<Road*> m_road;
    /**
     * @brief addRoad Creates a new road and inserts it in m_road
     */
    void addRoad(vector<vector<double> > listOfCoordinates, long edgeId, long fromNodeId, long toNodeId);
};

#endif // GRID_H
