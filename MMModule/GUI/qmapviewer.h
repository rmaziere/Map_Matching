#ifndef QMAPVIEWER_H
#define QMAPVIEWER_H

#include <QApplication>
#include <QImage>
#include <QPainter>
#include <QString>
#include <iostream>
#include <string>

class QMapViewer {
public:
    /**
     * @brief The Map class's constructor
     * @param Image's width
     * @param Image's height
     */
    QMapViewer();

    QMapViewer(int width, int height);

    /**
     * @brief scaleCalculator
     * @param xMinGrid
     * @param xMaxGrid
     * @param yMinGrid
     * @param yMaxGrid
     */
    void scaleCalculator(double xMinGrid, double xMaxGrid, double yMinGrid, double yMaxGrid);

    /**
     * @brief deltaCalculator
     * @param xMinGrid
     * @param yMinGrid
     */
    void deltaCalculator(double xMinGrid, double yMinGrid);

    /**
     * @brief coordinateTranslator
     * @param x
     * @param y
     * @return
     */
    QPointF coordinateTranslator(double x, double y);

    void landmarkMaker(int resolution, QString color = "black");

    void write(QPoint point, QString text, QString color = "black");

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

    //protected:
    int width; /**< image width*/
    int height; /**< image height*/
    double scale = 1; /**< scale between the grid and the image*/
    int deltaX; /**< delta between the SRID's x origin and the grid's x*/
    int deltaY; /**< delta between the SRID's y origin and the grid's y*/
    QImage img; /**< The QImage object*/
    QPainter paint; /**< The QPainter object*/
};

#endif // QMAPVIEWER_H
