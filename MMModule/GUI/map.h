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

    /**
     * @brief drawPolyline
     * @param polyligne
     * @param size the number of polyligne's points
     */
    int drawPolyline(QPointF polyligne, int size);

    /**
     * @brief draw is a test draw
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
    int width;  /**< image width*/
    int height; /**< image height*/
    QImage img;
    QPainter paint;
};

#endif // MAP_H
