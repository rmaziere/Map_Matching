#ifndef QMAPVIEWER_H
#define QMAPVIEWER_H

#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QString>
#include <iostream>
#include <string>

#include "pointGPS.h"

class QMapViewer : public QObject {
    Q_OBJECT
public:
    /**
     * @brief The Map class's constructor
     * @param Image's width
     * @param Image's height
     */
    explicit QMapViewer(int width=500, int m_height=400);

    void drawAllGPSPoints();
    void drawPoint(Point &);
    double transform(double x, int dim);


    /**
     * @brief TranslateToQPoint
     * @param x
     * @param y
     * @return
     */
    QPointF TranslateToQPoint(double x, double y);


    void landmarkMaker(int resolution, QString color = "black");

    void paintTick(QPoint point, QString text, QString color = "black");

    void makePointFromTrack(std::vector<std::vector<double> > vXY, QString color = "black");

    /**
     * @brief makePolyline
     * @param vXY
     * @return
     */
    void makePolyline(std::vector<std::vector<double> > vXY, QString color = "black");

    void makePolylineFromRoad(std::vector<std::vector<double> > vXY, QString color = "black");

    /**
     * @brief drawPolyline
     * @param polyligne
     * @param size the number of polyligne's points
     */
    void drawPolyline(QPointF polyligne, int size);

    /**
     * @brief save the current image
     * @param file is the path used for output
     * @return
     */
    void save(QString file);

    QImage m_map; /**< map */



signals:
    void signalTrackCompleted(QString);

public slots:
    void onSignalAllPoints(std::vector<PointGPS*> *);




protected:
    std::vector<PointGPS*> *m_trackPoints;
    double m_scaleFactor = 1; /**< scale between the grid and the image*/
    int m_width; /**< image width*/
    int m_height; /**< image height*/
    int m_shiftX; /**< delta between the SRID's x origin and the grid's x*/
    int m_shiftY; /**< delta between the SRID's y origin and the grid's y*/

    QPainter m_paint; /**< The QPainter object*/
};

#endif // QMAPVIEWER_H
