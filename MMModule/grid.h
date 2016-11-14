#ifndef GRID_H
#define GRID_H

#include "road.h"
#include "track.h"

#include <QString>
#include <vector>
#include <unordered_map>

struct hashFunc {
    size_t operator()(const PointRoad &p) const{
    size_t h1 = std::hash<double>()(p.x());
    size_t h2 = std::hash<double>()(p.y());
    return h1 ^ (h2 << 1);
    }
};

struct equalsFunc{
  bool operator()( const PointRoad& p1, const PointRoad& p2) const{
    return p1.samePointAs(p2);
  }
};

typedef unordered_map<PointRoad, int, hashFunc, equalsFunc> ExtremityPointMap; // for all edges points
typedef unordered_map<long, Road> AllRoadMap;   // for all roads

class Grid {
public:
    Grid();
    virtual ~Grid();

    /**
     * @brief setZone Save data about our area of roads
     * @param xMin Coordinate xMin of a track
     * @param xMax Coordinate xMax of a track
     * @param yMin Coordinate yMin of a track
     * @param yMax Coordinate yMax of a track
     */
    void setBoundingBox(double xMin,double xMax,double yMin,double yMax);

    /**
     * @brief readFromCSV Reads a csv file and inserts info into the corresponding attributs
     * @param filename the filepath/filename for the csv file to read
     */
    void readFromCSV(QString filename);

    /**
     * @brief addRoad Creates a new road and inserts it in m_road
     */
    void addRoad(const vector<vector<double> > & listOfCoordinates, long edgeId);

    /**
     * @brief inFootPrint Test if a point is in the defined area of a track
     * @param x Coordinate x of a point
     * @param y Coordinate x of a point
     * @return true or false
     */
    bool inFootPrint(double x,double y);

    void setDistance(PointGPS &p, Road &r);

    void buildKDTree();

    void outputInfos();

    // accessors
    int getNoOfRoads() const { return m_mapOfAllRoads.size();}
    int getNoOfPoints() const { return m_vectorOfPoints.size();}
    double xMin() const { return m_xMin;}
    double xMax() const { return m_xMax;}
    double yMin() const { return m_yMin;}
    double yMax() const { return m_yMax;}
protected:
    std::string m_gridFullName;
    ExtremityPointMap m_mapOfExtPoints; // temporary container during csv loading
    AllRoadMap m_mapOfAllRoads;
    std::vector<PointRoad> m_vectorOfPoints;

    double m_xMin;
    double m_xMax;
    double m_yMin;
    double m_yMax;
};

#endif // GRID_H
