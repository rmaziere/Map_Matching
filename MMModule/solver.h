#ifndef SOLVER_H
#define SOLVER_H

#include <QObject>

#include "file.h"
#include "grid.h"
#include "pointGPS.h"
#include "pointroad.h"
#include "road.h"
#include "track.h"

#include <unordered_map>
#include <vector>

class Solver : public QObject {
    Q_OBJECT
public:
    explicit Solver(QObject* parent = 0);

    void start();
    void viterbiSetup();

    /**
    * @brief setDistance Calculate distance between GPS point et Road
    * @param p GPS point
    * @param r Road
    */
    void setDistance(PointGPS* p, Road *r);

    void buildRoadPath();


    /**
     * @brief readFiles Read files : track and grid
     * @param file1 track file
     * @param file2 grid file
     */
    void readFiles(File file1, File file2);

    /**
     * @brief filterSpace Use Spatial filter with a value
     * @param val value
     */
    void filterSpace(double val);

    /**
     * @brief filterTemp Use Temporal filter with a value
     * @param val value
     */
    void filterTemp(int val);

    int getIndexFromRoadId(long id);


    QString m_gridFilename; // to move in protected once signals are in use
    QString m_trackFilename;
    //protected:
    Track track;
    Grid grid;
    std::unordered_map<long, Road>* m_roads;
    std::vector<PointRoad>* m_roadPoints;
    std::vector<PointGPS*>* m_trackPoints;

signals:
    void signalMessage(QString);
    void signalDimension(double xMin, double xMax, double yMin, double yMax);
    void signalAllPoints(std::vector<PointGPS*>*);
    void signalAllRoads(std::unordered_map<long, Road>*, std::vector<PointRoad>*);
    void signalCurrentPoint(int id);
    void signalRoadPath(std::vector<long>* rp);
public slots:
    void onSignalSetGrid(QString s);
    void onSignalSetTrack(QString s);
    void onSignalStart();
    void onSignalNextStep();
    void onSignalNeighbours(std::vector<long>* roadsId);
protected:
    unsigned int m_currentStep;
    std::vector<std::vector<float>> T1, T2;
    std::vector<long> m_fromIndexToRoadId;
    std::unordered_map<long,int> m_fromRoadIdToIndex;
    std::vector<long> *prevRoadIds;
    PointGPS *prevPoint;
};

#endif // SOLVER_H
