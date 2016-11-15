#include <QApplication>
#include <QFileDialog>
#include <math.h>
#include <vector>
#include <limits.h>
#include <iostream>

#include "file.h"
#include "grid.h"
#include "myexception.h"
#include "pointGPS.h"
#include "track.h"
#include "loading.h"


using namespace std;

void dev_grid()
{
    QString gridFile= "../Data/Unit_tests_data_set/gridTestPointsHaveNoDuplicate.csv";
    Grid grid;
    grid.readFromCSV(gridFile);
    grid.buildMarkovMatrix();
    grid.outputInfos();
}

void dev_all()
{
    // grid.readFromCSV("../Data/Unit_tests_data_set/gridTestPointsHaveNoDuplicate.csv");
    QString trackFile= "../Data/Seattle/mini_start_track.csv";
    QString gridFile= "../Data/Seattle/mini_start_network.csv";
    int test= 1;
    switch(test) {
    case 1:
        trackFile= "../Data/Seattle/useful_all_track.csv";
        gridFile= "../Data/Seattle/useful_all_network.csv";
    }

    Track track;
    Grid grid;
    track.readFromCSV(trackFile);
    track.outputInfos();

    grid.setBoundingBox(track.m_xMin, track.m_xMax, track.m_yMin, track.m_yMax);
    //grid.readFromCSVSeattle(gridFile);
    grid.readFromCSV(gridFile);
    grid.outputInfos();

}

void dev_network()
{
/*
    grid myNetwork;
    myNetwork.readFromCSV("../Data/Unit_tests_data_set/simpleNetworkLoaderExemple.csv");
    cout << myNetwork.m_road.size() << endl;

    for (size_t i = 0; i < myNetwork.m_road.size(); ++i) {
        cout << myNetwork.m_road[i]->getListOfPoints().size() << endl;
        cout << myNetwork.m_road[i]->getListOfPoints()[0]->m_x << endl;
    }*/
}

void dev_openFile()
{
/*

    //QApplication app(argc, argv);

    //File Test;
    //QString ext = "shp";

    //Test.selectFilesToOpen(argc, argv, ext);
    //Test.shp2csv();
    Test.whereSave();
    for (int i = 0; i < Test.filePath.size(); ++i){
        QString tempFilePath = Test.filePath.at(i);
        QString tempFileName = Test.fileName.at(i);
        QString tempFileExtension = Test.fileExtension.at(i);
        cout << tempFilePath.toStdString() << " - "
             << tempFileName.toStdString() << " - "
             << tempFileExtension.toStdString() << endl;
    }
    //return app.exec();*/
}

void dev_file(){
    File f;
    f.selectFilesToOpen("shp");
    cout << "File name : " << f.fileName.at(0).toStdString() << ", file extension : " << f.fileExtension.at(0).toStdString() << endl;

    f.shp2csv("Polyline");
    cout << "File name : " << f.fileName.at(0).toStdString() << ", file extension : " << f.fileExtension.at(0).toStdString() << endl;
}

int main(int argc, char *argv[])
{
    //dev_grid();
    //dev_all();
    QApplication app(argc, argv);

    Loading fenetre;
    // Affichage de la fenêtre
    fenetre.show();

    return app.exec();
}
