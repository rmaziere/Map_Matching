#include "qmapscene.h"

#include <QPen>
#define POINT_SIZE 3

QMapScene::QMapScene(QObject* parent)
    : QGraphicsScene(parent)
{
    setItemIndexMethod(QGraphicsScene::NoIndex);
}

void QMapScene::initialize(int startx, int starty, int width, int height)
{
    m_width = width;
    m_height = height;
    //std::cout << startx << " " << starty << " " <<
    this->setSceneRect(QRectF(startx, starty, m_width - startx, m_height - starty));
}

double QMapScene::transform(double x, int dim)
{
    if (dim == X)
        return (x - m_shiftX) / m_scaleFactor;
    else
        return m_height - ((x - m_shiftY) / m_scaleFactor);
}

void QMapScene::onSignalAllPoints(std::vector<PointGPS*>* p)
{
    m_trackPoints = p;
    points = new QGraphicsRectItem[m_trackPoints->size()];
    int count = 0;

    for (auto p : *m_trackPoints) {
        QGraphicsRectItem* r = new QGraphicsRectItem(p->x(), p->y(), POINT_SIZE, POINT_SIZE);
        r->setPen(QPen(QColor("red"), 10));
        addItem(r);
        //points[count]= r;
        //qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = Q_NULLPTR
        ++count;
    }
    emit signalTrackCompleted("Track has been graphically processed");
}

void QMapScene::signalAllRoads(std::unordered_map<long, Road>* roads, std::vector<PointRoad>* points)
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
        addPath(*path);
    }
}
