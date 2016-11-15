#include "map.h"

Map::Map(int width, int height){
    this->width  = width;
    this->height = height;

    img = QImage(this->width, this->height, QImage::Format_RGB32);
    img.fill(Qt::color0);
}

int Map::draw(){
    paint.begin(&img);
    paint.drawRect(0,0,99,99);

    paint.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));

    static const QPointF points[3] = {
        QPointF(10.0, 80.0),
        QPointF(20.0, 10.0),
        QPointF(80.0, 30.0)
    };

    paint.drawPolyline(points, 3);

    paint.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
    paint.drawPoint(75,75);

    paint.end();
    return 0;
}
/*
int Map::drawPolyline(QPointF polyligne, int size){
    paint.drawPolyline(polyligne, size);
    return 0;
}*/

int Map::save(QString file){
    img.save(file);
    return 0;
}
