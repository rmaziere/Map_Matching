#ifndef MAP_H
#define MAP_H

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
    Map(int width, int height);

    void scaleCalculator(double xMinGrid, double xMaxGrid, double yMinGrid, double yMaxGrid);
    void deltaCalculator(double xMinGrid, double yMinGrid);

    QPointF coordinateTranslator(double x, double y);

    /**
     * @brief drawPolyline
     * @param polyligne
     * @param size the number of polyligne's points
     */
    int drawPolyline(QPointF polyligne, int size);

    /**
     * @brief draw is a test drawing function
     * @return an image on the disk
     */
    int draw();

    /**
     * @brief save the current image
     * @param file is the path used for output
     * @return
     */
    int save(QString file);

protected:
    int width;      /**< image width*/
    int height;     /**< image height*/
    int scale;      /**< scale between the grid and the image*/
    int deltaX;     /**< delta between the SRID's x origin and the grid's x*/
    int deltaY;     /**< delta between the SRID's y origin and the grid's y*/
    QImage img;     /**< The QImage object*/
    QPainter paint; /**< The QPainter object*/
};

#endif // MAP_H
