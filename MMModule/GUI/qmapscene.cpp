#include "qmapscene.h"
#include <QPen>

#define POINT_SIZE 15
#define ROAD_SIZE 5
#define RADIUS 200

#define KEY_ISROAD 0
#define KEY_ROADID 1

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

void QMapScene::highlightSelectedPoint(int pointId)
{
    QGraphicsRectItem* it = pointItems[pointId];
    it->setPen(QPen(QColor(GPSSELECTED), POINT_SIZE * 2));
    //it->setBrush(QBrush(QColor(GPSSELECTED)));
    // show circle 200m radius
    m_selectionCircle->setPen(QPen(QColor(COLORCLEAR), POINT_SIZE));
    m_selectionCircle->setPos(it->x() - RADIUS, it->y() - RADIUS);
    m_selectionCircle->setPen(QPen(QColor(GPSSELECTED), POINT_SIZE));
    //update();
}

void QMapScene::highlightRoadsDefault(bool basic)
{
    QList<QGraphicsItem*> list = m_selectionCircle->collidingItems();
    for (auto* item : list) {
        if (item->data(KEY_ISROAD).toBool()) {
            if (basic)
                ((QGraphicsPathItem*)item)->setPen(QPen(QColor(ROADDEFAULT)));
            else
                ((QGraphicsPathItem*)item)->setPen(QPen(QColor(ROADSELECTED)));
        }
    }
}

void QMapScene::setBackToDefault(int pointId)
{
    QGraphicsRectItem* it = pointItems[pointId];
    it->setPen(QPen(QColor(GPSDEFAULT), POINT_SIZE));
}

void QMapScene::setNeighborRoads()
{
    QList<QGraphicsItem*> list = m_selectionCircle->collidingItems();
    m_neighboursId.clear();
    for (auto* item : list) {
        if (item->data(KEY_ISROAD).toBool()) {
            m_neighboursId.push_back(item->data(KEY_ROADID).toLongLong());
        }
    }
}

void QMapScene::onSignalAllPoints(std::vector<PointGPS*>* p)
{
    m_trackPoints = p;
    int count = 0;

    for (auto p : *m_trackPoints) {
        /*
        QGraphicsRectItem* rect = new QGraphicsRectItem(p->x(), p->y(), POINT_SIZE, POINT_SIZE);*/
        QGraphicsRectItem* rect = new QGraphicsRectItem(0, 0, POINT_SIZE, POINT_SIZE);
        rect->setPos(p->x(), p->y());
        rect->setPen(QPen(QColor(GPSDEFAULT), POINT_SIZE));
        rect->setData(KEY_ISROAD, false);
        addItem(rect);

        pointItems.push_back(rect);
        //qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = Q_NULLPTR
        ++count;
    }
    PointGPS* p0 = m_trackPoints->at(0);
    m_selectionCircle = new QGraphicsEllipseItem(0, 0, 2 * RADIUS, 2 * RADIUS);
    m_selectionCircle->setPos(p0->x() - RADIUS, p0->y() - RADIUS);
    m_selectionCircle->setPen(QPen(QColor(GPSSELECTED), POINT_SIZE));
    addItem(m_selectionCircle);
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
        QGraphicsPathItem* pathItem = new QGraphicsPathItem();
        pathItem->setPath(*path);
        pathItem->setData(KEY_ISROAD, true);
        qlonglong v = r.edgeId();
        pathItem->setData(KEY_ROADID, v);
        pathItem->setPen(QPen(QColor(ROADDEFAULT)));
        addItem(pathItem);
    }
}

void QMapScene::onSignalStart()
{
    QGraphicsRectItem* it = pointItems[0];
    highlightSelectedPoint(0);
    emit signalItemToShow(it);
}

void QMapScene::onSignalCurrentPoint(int pointId)
{
    if (pointId > 0) {
        setBackToDefault(pointId - 1);
        highlightRoadsDefault(true);
    }
    highlightSelectedPoint(pointId);

    QList<QGraphicsItem*> list = m_selectionCircle->collidingItems();
    highlightRoadsDefault(false);
    setNeighborRoads();

    std::cout << "Point " << pointId << std::endl;

    emit signalNeighboursId(&m_neighboursId);
    emit signalItemToShow(pointItems[pointId]);
}

void QMapScene::onSignalRoadPath(std::vector<long>* rp)
{
    bool found;
    QPen pen(QColor(GPSSELECTED), POINT_SIZE);
    QPen defaultPen(QColor(ROADDEFAULT));
    foreach (QGraphicsItem* item, items()) {
        QGraphicsPathItem* path = qgraphicsitem_cast<QGraphicsPathItem*>(item);
        if (!path)
            continue;
        // check if in road path
        found = false;
        for (auto r : *rp) {
            if (path->data(KEY_ROADID).toLongLong() == r) {
                path->setPen(pen);
                found = true;
            }
        }
        if (!found)
            path->setPen(defaultPen);
    }
    delete rp;
}
