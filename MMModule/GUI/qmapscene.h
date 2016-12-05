#ifndef QMAPSCENE_H
#define QMAPSCENE_H

#include "../pointGPS.h"
#include "../pointroad.h"
#include "../road.h"
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <unordered_map>
#include <vector>

#define GPSDEFAULT "red"
#define GPSSELECTED "green"
#define ROADDEFAULT "grey"
#define ROADSELECTED "blue"
#define COLORCLEAR "white"
#define X 0
#define Y 1

class QMapScene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit QMapScene(QObject* parent = 0);
    void initialize(int startx, int starty, int width, int height);
    double transform(double x, int dim);
    void highlightSelectedPoint(int pointId);
    void highlightRoadsDefault(bool basic);
    void setBackToDefault(int pointId);
    void setNeighborRoads();

signals:
    void signalTrackCompleted(QString);
    void signalItemToShow(QGraphicsItem*);
    void signalNeighboursId(std::vector<long>*);
public slots:
    void onSignalAllPoints(std::vector<PointGPS*>*);
    void onSignalAllRoads(std::unordered_map<long, Road>* roads, std::vector<PointRoad>*);
    void onSignalStart();
    void onSignalCurrentPoint(int pointId);
    void onSignalRoadPath(std::vector<long>* rp);
    void onSignalRoadSet(std::set<long>* rs);
protected:
    std::vector<PointGPS*>* m_trackPoints;
    std::unordered_map<long, Road>* m_roads;
    std::vector<PointRoad>* m_roadPoints;
    std::vector<long> m_neighboursId;
    double m_scaleFactor = 1; /**< scale between the grid and the image*/
    int m_width; /**< image width*/
    int m_height; /**< image height*/
    int m_shiftX; /**< delta between the SRID's x origin and the grid's x*/
    int m_shiftY; /**< delta between the SRID's y origin and the grid's y*/

    std::vector<QGraphicsRectItem*> pointItems;
    QGraphicsEllipseItem* m_selectionCircle;
};

#endif // QMAPSCENE_H
