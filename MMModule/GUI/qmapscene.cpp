#include "qmapscene.h"
#include <QPen>
#define POINT_SIZE 15
#define ROAD_SIZE 5

/**
http://doc.qt.io/qt-5/graphicsview.html#the-graphics-view-coordinate-system
Finally, if you use want to find what items are inside a view ellipse, you can pass a QPainterPath to mapToScene(), and then pass the mapped path to QGraphicsScene::items().
 */


QMapScene::QMapScene(QObject* parent)
    : QGraphicsScene(parent)
{
    setItemIndexMethod(QGraphicsScene::NoIndex);
}

void QMapScene::initialize(int startx, int starty, int width, int height)
{
    m_width = width;
    m_height = height;
    this->setSceneRect(QRectF(startx, starty, m_width - startx, m_height - starty));
}

void QMapScene::onSignalAllPoints(std::vector<PointGPS*>* p)
{
    m_trackPoints = p;
    int count = 0;

    for (auto p : *m_trackPoints) {
        QGraphicsRectItem* rect = new QGraphicsRectItem(p->x(), p->y(), POINT_SIZE, POINT_SIZE);
        rect->setPen(QPen(QColor(GPSDEFAULT), POINT_SIZE));
        addItem(rect);

        pointItems.push_back(rect);
        //qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = Q_NULLPTR
        ++count;
        std::cout << rect->x() << " " << rect->y() << std::endl;
    }
    emit signalTrackCompleted("Track has been graphically processed");
}

void QMapScene::onSignalAllRoads(std::unordered_map<long, Road>* roads, std::vector<PointRoad>* points)
{
    m_roads = roads;
    m_roadPoints = points;
    for (auto it : *roads) {
        Road r = it.second;
        const std::vector<int>& listOfPointId = it.second.vectorOfPointsId();
        QPainterPath* path = new QPainterPath(QPointF(m_roadPoints->at(listOfPointId[0]).x(), m_roadPoints->at(listOfPointId[0]).y()));
        for (uint i = 1; i < listOfPointId.size(); i++) {
            path->lineTo(m_roadPoints->at(listOfPointId[i]).x(), m_roadPoints->at(listOfPointId[i]).y());
        }
        addPath(*path, QPen(QColor(ROADDEFAULT)));
    }
}

void QMapScene::onSignalStart()
{

}

void QMapScene::onSignalCurrentPoint(int pointId)
{
    // show point
    std::cout << pointItems.size() << std::endl;
    QGraphicsRectItem *it= pointItems[pointId];
    //it->mapToScene()
    it->setPen(QPen(QColor(GPSDEFAULT), POINT_SIZE*10));
    it->setBrush(QBrush(QColor(0, 0, 0, 150)));
    QPointF pos= it->scenePos();
    // show circle 200m radius
    //QGraphicsEllipseItem *test= new QGraphicsEllipseItem(pos.x(), pos.y(), 200, 200);
    addEllipse(it->x(), it->y(), 200, 200, QPen(QColor("green"),20));
    // select roads

    // send roads

    std::cout << "point at " << pos.x() << " " << pos.y() << std::endl;
}
