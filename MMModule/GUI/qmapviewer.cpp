#include "qmapviewer.h"

#define GPSDEFAULT "red"
#define X 0
#define Y 2

QMapViewer::QMapViewer(int width, int height)
{
    this->m_width = width;
    this->m_height = height;

    m_map = QImage(this->m_width, this->m_height, QImage::Format_RGB32);
    m_map.fill(Qt::color0);
}

void QMapViewer::drawAllGPSPoints()
{
    m_paint.begin(&m_map);
    m_paint.setPen(QPen(QColor(GPSDEFAULT), 10, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
    for (auto p : *m_trackPoints) {
        drawPoint(*p);
    }
    m_paint.end();
    emit signalTrackCompleted("Track has been graphically processed");
}

void QMapViewer::drawPoint(Point &p)
{
    QPointF pf(transform(p.x(),X), transform(p.y(),Y));
    m_paint.drawPoint(pf);
}

double QMapViewer::transform(double x, int dim)
{
    if (dim==X) return (x-m_shiftX)/m_scaleFactor;
    else return m_height-((x-m_shiftY)/m_scaleFactor);
}
/*
void QMapViewer::onSignalDimension(double xMinGrid, double xMaxGrid, double yMinGrid, double yMaxGrid)
{
    double scaleX = (xMaxGrid - xMinGrid) / m_width;
    double scaleY = (yMaxGrid - yMinGrid) / m_height;
    m_scaleFactor = (scaleX < scaleY)?scaleY:scaleX;
    m_shiftX = round(xMinGrid);
    m_shiftY = round(yMinGrid);
}
*/

QPointF QMapViewer::TranslateToQPoint(double x, double y)
{
    float newX = (x - m_shiftX); //Changement de référence (décalage du 0,0 du SRID)
    newX /= m_scaleFactor; //Application de l'échelle

    float newY = (y - m_shiftY); //Changement de référence (décalage du 0,0 du SRID)
    newY /= m_scaleFactor; //Application de l'échelle
    newY = m_height - newY; //Changement de l'orientation du y

    std::cout << "NewX : " << std::to_string(newX) << std::endl;
    std::cout << "NewY : " << std::to_string(newY) << std::endl;

    QPointF p(newX, newY);
    return p;
}

void QMapViewer::landmarkMaker(int resolution, QString color)
{
    /*Echelle en x*/
    for (int i = 0; i < m_width; i += resolution) {
        paintTick(QPoint(i, 15), QString::number(i), color);
    }

    /*Echelle en y*/
    for (int i = 0; i < m_height; i += resolution) {
        paintTick(QPoint(5, i), QString::number(i));
    }
}

void QMapViewer::paintTick(QPoint point, QString text, QString color)
{
    m_paint.begin(&m_map);

    m_paint.setPen(QPen(QColor(color)));
    m_paint.drawText(point, text);

    m_paint.end();
}

void QMapViewer::makePointFromTrack(std::vector<std::vector<double> > vXY, QString color)
{
    m_paint.begin(&m_map);
    for (uint i = 0; i < vXY.size(); i++) {
        std::cout << "Point x = " << vXY.at(i).at(0) << ", ";
        std::cout << "Point y = " << vXY.at(i).at(1) << std::endl;

        if (i < vXY.size()) {
            m_paint.setPen(QPen(QColor(color), 10, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
            QPointF point = { TranslateToQPoint(vXY.at(i).at(0), vXY.at(i).at(1)) };
            m_paint.drawPoint(point);
        }
    }
    m_paint.end();
}

void QMapViewer::makePolyline(std::vector<std::vector<double> > vXY, QString color)
{
    m_paint.begin(&m_map);
    for (uint i = 0; i < vXY.size(); i++) {
        std::cout << "x = " << vXY.at(i).at(0) << ", ";
        std::cout << "y = " << vXY.at(i).at(1) << std::endl;

        if (i < vXY.size() - 1) {
            QPointF polyligne[2] = { QPointF(vXY.at(i).at(0), vXY.at(i).at(1)), QPointF(vXY.at(i + 1).at(0), vXY.at(i + 1).at(1)) };
            m_paint.setPen(QPen(QColor(color), 3, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
            m_paint.drawPolyline(polyligne, 2);
        }    emit signalTrackCompleted("Track has been graphically processed");
    }
    m_paint.end();
}

void QMapViewer::makePolylineFromRoad(std::vector<std::vector<double> > vXY, QString color)
{
    m_paint.begin(&m_map);

    for (uint i = 0; i < vXY.size(); i++) {
        std::cout << "x = " << vXY.at(i).at(0) << ", ";
        std::cout << "y = " << vXY.at(i).at(1) << std::endl;

        if (i < vXY.size() - 1) {
            QPointF polyligne[2] = { TranslateToQPoint(vXY.at(i).at(0), vXY.at(i).at(1)), TranslateToQPoint(vXY.at(i + 1).at(0), vXY.at(i + 1).at(1)) };
            m_paint.setPen(QPen(QColor(color), 2, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
            m_paint.drawPolyline(polyligne, 2);
        }
    }
    m_paint.end();
}

void QMapViewer::save(QString file)
{
    m_map.save(file);
}

void QMapViewer::onSignalAllPoints(std::vector<PointGPS *> *p)
{
    m_trackPoints=p;
    drawAllGPSPoints();
}
