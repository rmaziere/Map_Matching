#include <QApplication>
#include <QFileDialog>
#include <vector>
#include <math.h>

#include "myexception.h"
#include "track.h"
#include "pointGPS.h"
#include "sauvegarde.h"
#include "file.h"
#include "distance.h"

using namespace std;

int main(/*int argc, char *argv[]*/)
{
    Point A(0,0);
    Point B(0,10);
    Point C(1,11);

    cout << C.distance2ptsegment(A,B);

    //*********PointsGPS**********
    Track Trace = Track();

    for (uint i=0 ; i < Trace.getPoints().size(); ++i){
        cout << Trace.getPoints()[i]->getLatitude() << ",\n"
            << Trace.getPoints()[i]->getLongitude() << ",\n"
            << Trace.getPoints()[i]->getAltitude() << ",\n"
            << Trace.getPoints()[i]->getTimeStamp().toString("yyyy-MM-dd hh:mm:ss")
            << "\n" << endl;
    }

    Trace.~Track();

    for (uint i=0 ; i < Trace.getPoints().size(); ++i){
        cout << Trace.getPoints()[i]->getLatitude() << ",\n"
            << Trace.getPoints()[i]->getLongitude() << ",\n"
            << Trace.getPoints()[i]->getAltitude() << ",\n"
            << Trace.getPoints()[i]->getTimeStamp().toString("yyyy-MM-dd hh:mm:ss")
            << "\n" << endl;
    }

    int j = 0;
    int z = 0;
    for(int i=0; i<10; i++){
        Trace.addPoint(i, j, z, currentDateTime());
        j++;
        z++;
    }
    Trace.delPointGPS(Trace.getPoints()[5]);

    for (uint i=0 ; i < Trace.getPoints().size(); ++i){
        cout << Trace.getPoints()[i]->getLatitude() << ",\n"
            << Trace.getPoints()[i]->getLongitude() << ",\n"
            << Trace.getPoints()[i]->getAltitude() << ",\n"
            << Trace.getPoints()[i]->getTimeStamp().toString("yyyy-MM-dd hh:mm:ss")
            << "\n" << endl;
    }
    //*********PointsGPS**********

    //QApplication app(argc, argv);

    //File Test;
    //QString ext = "shp";

    //Test.selectFilesToOpen(argc, argv, ext);
    //Test.shp2csv();
    /*Test.whereSave();
    for (int i = 0; i < Test.filePath.size(); ++i){
        QString tempFilePath = Test.filePath.at(i);
        QString tempFileName = Test.fileName.at(i);
        QString tempFileExtension = Test.fileExtension.at(i);
        cout << tempFilePath.toStdString() << " - "
             << tempFileName.toStdString() << " - "
             << tempFileExtension.toStdString() << endl;
    }*/
    //return app.exec();

}
