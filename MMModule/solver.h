#ifndef SOLVER_H
#define SOLVER_H

#include <QObject>

#include "grid.h"
#include "pointGPS.h"
#include "pointroad.h"
#include "road.h"
#include "track.h"

#include <unordered_map>
#include <vector>

typedef std::unordered_map<long, Road> AllRoadMap;
typedef std::vector<PointGPS*> AllPointVector;

class Solver : public QObject {
    Q_OBJECT
public:
    explicit Solver() {}
    /*
    explicit Solver(AllRoadMap* gridRoad, std::vector<PointRoad>* roadPoints, AllPointVector* trackPoint)
        : m_roads(gridRoad)
        , m_roadPoints(roadPoints)
        , m_trackPoints(trackPoint)
    {
    }
    */
    void start();
    void setDistance(PointGPS* p, Road& r);

    QString m_gridFilename; // to move in protected once signals are in use
    QString m_trackFilename;

signals:
    void signalMessage(QString);

public slots:
    void onSignalSetGrid(QString s);
    void onSignalSetTrack(QString s);
    void onSignalStart();

protected:
    Grid grid;
    Track track;
    AllRoadMap* m_roads;
    std::vector<PointRoad>* m_roadPoints;
    AllPointVector* m_trackPoints;
};

#endif // SOLVER_H
