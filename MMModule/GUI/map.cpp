#include "map.h"

Map::Map(){
    Map(1280, 1024);
}

Map::Map(int width=1280, int height=1024){
    this->width  = width;
    this->height = height;

    img = QImage(this->width, this->height, QImage::Format_RGB32);
    img.fill(Qt::color0);
}

void Map::scaleCalculator(double xMinGrid, double xMaxGrid, double yMinGrid, double yMaxGrid){
    int scaleX = width / (xMaxGrid - xMinGrid);
    int scaleY = height / (yMaxGrid - yMinGrid);

    if(scaleX < scaleY){
        scale = scaleY;
    }else{
        scale = scaleX;
    }
}

void Map::deltaCalculator(double xMinGrid, double yMinGrid){
    deltaX = round(xMinGrid);
    deltaY = round(yMinGrid);
}

QPointF Map::coordinateTranslator(double x, double y){
    float newX = (x - deltaX);//Changement de référence (décalage du 0,0 du SRID)
    newX *= scale;          //Application de l'échelle

    float newY = (y - deltaY);//Changement de référence (décalage du 0,0 du SRID)
    newY *= scale;          //Application de l'échelle
    newY = height - y;      //Changement de l'orientation du y

    QPointF p(newX, newY);
    return p;
}

int Map::draw(){
    paint.begin(&img);

    paint.setPen(QPen(Qt::black, 3, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));

    paint.drawRect(0,0,99,99);

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

int Map::makePolyline(std::vector<std::vector<double>> vXY){
    paint.begin(&img);

    std::cout << "Taille du vecteur : " << vXY.size()<< std::endl;

    for(int i = 0; i < vXY.size(); i++){
        std::cout << "x = " << vXY.at(i).at(0) << ", ";
        std::cout << "y = " << vXY.at(i).at(1) << std::endl;

        if (i < vXY.size() - 1) {
            QPointF polyligne[2] = {QPointF(vXY.at(i).at(0), vXY.at(i).at(1)), QPointF(vXY.at(i+1).at(0), vXY.at(i+1).at(1))};
            paint.setPen(QPen(Qt::red, 3, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
            paint.drawPolyline(polyligne, 2);

        }
        paint.setPen(QPen(Qt::blue, 15, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
        paint.drawPoint(QPointF(vXY.at(i).at(0), vXY.at(i).at(1)));
    }

    std::cout << "drawPolyline" << std::endl;
    paint.end();
    return 0;
}

int Map::save(QString file){
    img.save(file);
    return 0;
}
