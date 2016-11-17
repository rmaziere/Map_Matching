#include "map.h"

Map::Map(){}

Map::Map(int width = 1280, int height = 1024)
{
    this->width = width;
    this->height = height;

    img = QImage(this->width, this->height, QImage::Format_RGB32);
    img.fill(Qt::color0);
}

void Map::scaleCalculator(double xMinGrid, double xMaxGrid, double yMinGrid, double yMaxGrid)
{
    double scaleX = (xMaxGrid - xMinGrid) / width;
    double scaleY = (yMaxGrid - yMinGrid) / height;

    std::cout << "scaleCalculator.scaleX = " << std::to_string(scaleX) << std::endl;
    std::cout << "scaleCalculator.scaleY = " << std::to_string(scaleY) << std::endl;

    if (scaleX < scaleY) {
        scale = scaleY;
    } else {
        scale = scaleX;
    }
}

void Map::deltaCalculator(double xMinGrid, double yMinGrid)
{
    deltaX = round(xMinGrid);
    deltaY = round(yMinGrid);
}

QPointF Map::coordinateTranslator(double x, double y)
{
    float newX = (x - deltaX); //Changement de référence (décalage du 0,0 du SRID)
    newX /= scale; //Application de l'échelle

    float newY = (y - deltaY); //Changement de référence (décalage du 0,0 du SRID)
    newY /= scale; //Application de l'échelle
    newY = height - newY; //Changement de l'orientation du y

    std::cout << "NewX : " << std::to_string(newX) << std::endl;
    std::cout << "NewY : " << std::to_string(newY) << std::endl;

    QPointF p(newX, newY);
    return p;
}

void Map::landmarkMaker(int resolution, QString color)
{
    /*Echelle en x*/
    for (int i = 0; i < width; i += resolution) {
        write(QPoint(i, 15), QString::number(i), color);
    }

    /*Echelle en y*/
    for (int i = 0; i < height; i += resolution) {
        write(QPoint(5, i), QString::number(i));
    }
}

void Map::write(QPoint point, QString text, QString color)
{
    paint.begin(&img);

    paint.setPen(QPen(QColor(color)));
    paint.drawText(point, text);

    paint.end();
}

void Map::makePointFromTrack(std::vector<std::vector<double> > vXY, QString color)
{
    paint.begin(&img);
    for (uint i = 0; i < vXY.size(); i++) {
        std::cout << "Point x = " << vXY.at(i).at(0) << ", ";
        std::cout << "Point y = " << vXY.at(i).at(1) << std::endl;

        if (i < vXY.size()) {
            paint.setPen(QPen(QColor(color), 10, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
            QPointF point = { coordinateTranslator(vXY.at(i).at(0), vXY.at(i).at(1)) };
            paint.drawPoint(point);
        }
    }
    paint.end();
}

void Map::makePolyline(std::vector<std::vector<double> > vXY, QString color)
{
    paint.begin(&img);
    for (uint i = 0; i < vXY.size(); i++) {
        std::cout << "x = " << vXY.at(i).at(0) << ", ";
        std::cout << "y = " << vXY.at(i).at(1) << std::endl;

        if (i < vXY.size() - 1) {
            QPointF polyligne[2] = { QPointF(vXY.at(i).at(0), vXY.at(i).at(1)), QPointF(vXY.at(i + 1).at(0), vXY.at(i + 1).at(1)) };
            paint.setPen(QPen(QColor(color), 3, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
            paint.drawPolyline(polyligne, 2);
        }
    }
    paint.end();
}

void Map::makePolylineFromRoad(std::vector<std::vector<double> > vXY, QString color)
{
    paint.begin(&img);

    for (uint i = 0; i < vXY.size(); i++) {
        std::cout << "x = " << vXY.at(i).at(0) << ", ";
        std::cout << "y = " << vXY.at(i).at(1) << std::endl;

        if (i < vXY.size() - 1) {
            QPointF polyligne[2] = { coordinateTranslator(vXY.at(i).at(0), vXY.at(i).at(1)), coordinateTranslator(vXY.at(i + 1).at(0), vXY.at(i + 1).at(1)) };
            paint.setPen(QPen(QColor(color), 2, Qt::SolidLine, Qt::RoundCap, Qt::BevelJoin));
            paint.drawPolyline(polyligne, 2);
        }
    }
    paint.end();
}

void Map::save(QString file)
{
    img.save(file);
}
