#ifndef NETWORK_H
#define NETWORK_H

#include "road.h"
#include <QString>
#include <vector>
using namespace std;
class Network {
public:
    Network();
    virtual ~Network();
    /**
     * @brief readFromCSV Reads a csv file and inserts info into the corresponding attributs
     * @param filename the filepath/filename for the csv file to read
     */
    void readFromCSV(QString filename);

    /**
     * @brief addRoad Creates a new road and inserts it in m_road
     */
    void addRoad(vector<vector<double> > listOfCoordinates, long edgeId, long fromNodeId, long toNodeId);

    vector<Road*> m_road;

};

#endif // NETWORK_H
