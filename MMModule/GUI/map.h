#ifndef MAP_H
#define MAP_H

#include <iostream>
#include <string>
#include <QApplication>
#include <QString>
#include <QImage>
#include <QPainter>

class Map
{
public:
    /**
     * @brief The Map class's constructor
     * @param Image's width
     * @param Image's height
     */
    Map();

    Map(int width, int height);

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

    int landmarkMaker(int resolution, QString color="black");

    int write(QPoint point, QString text,  QString color="black");


    int makePointFromTrack(std::vector<std::vector<double>> vXY, QString color="black");

    /**
     * @brief makePolyline
     * @param vXY
     * @return
     */
    int makePolyline(std::vector<std::vector<double>> vXY, QString color="black");

    int makePolylineFromRoad(std::vector<std::vector<double>> vXY, QString color="black");

    /**
     * @brief drawPolyline
     * @param polyligne
     * @param size the number of polyligne's points
     */
    int drawPolyline(QPointF polyligne, int size);

    /**
     * @brief save the current image
     * @param file is the path used for output
     * @return
     */
    int save(QString file);

//protected:
    int width;      /**< image width*/
    int height;     /**< image height*/
    double scale = 1;      /**< scale between the grid and the image*/
    int deltaX;     /**< delta between the SRID's x origin and the grid's x*/
    int deltaY;     /**< delta between the SRID's y origin and the grid's y*/
    QImage img;     /**< The QImage object*/
    QPainter paint; /**< The QPainter object*/
};

#endif // MAP_H
