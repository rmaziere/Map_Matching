#include <QFileDialog>
#include <QtGui/QApplication>
#include <iostream>
#include <limits.h>
#include <math.h>
#include <vector>

#include "file.h"
#include "grid.h"
#include "loading.h"
#include "myexception.h"
#include "pointGPS.h"
#include "track.h"
#include "loading.h"
#include "GUI/map.h"
#include "MainWindow.h"
#include "journalprocess.h"
#include "qdebugstream.h"
#include "solver.h"
#include <QTextEdit>

using namespace std;

void dev_grid()
{
    QString gridFile = "../Data/Unit_tests_data_set/gridTestPointsHaveNoDuplicate.csv";
    Grid grid;
    grid.readFromCSV(gridFile);
    grid.buildMarkovMatrix();
    grid.outputInfos();
}

void dev_all()
{
    // grid.readFromCSV("../Data/Unit_tests_data_set/gridTestPointsHaveNoDuplicate.csv");
    QString trackFile = "../Data/Seattle/mini_start_track.csv";
    QString gridFile = "../Data/Seattle/mini_start_network.csv";
    int test = 0;
    switch (test) {
    case 1:
        trackFile = "../Data/Seattle/useful_all_track.csv";
        gridFile = "../Data/Seattle/useful_all_network.csv";
    }

    Track track;
    Grid grid;
    track.readFromCSV(trackFile);
    track.outputInfos();

    grid.setBoundingBox(track.m_xMin, track.m_xMax, track.m_yMin, track.m_yMax);
    //grid.readFromCSVSeattle(gridFile);
    grid.readFromCSV(gridFile);
    grid.outputInfos();
    grid.buildMarkovMatrix();
    Solver solver(grid.getRoads(), grid.getPoints(), track.getPointsAsPointer());
    solver.initialize();

    std::cout << "The end." << std::endl;
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

void ui(){
    Loading fenetre;
    // Affichage de la fenêtre
    fenetre.show();
}

void dev_file(){
    File f;
    f.selectFilesToOpen("shp");
    cout << "File name : " << f.fileName.at(0).toStdString() << ", file extension : " << f.fileExtension.at(0).toStdString() << endl;

    f.shp2csv("Polyline");
    cout << "File name : " << f.fileName.at(0).toStdString() << ", file extension : " << f.fileExtension.at(0).toStdString() << endl;
}

void dev_img(){
    Map m(100, 100);
    m.draw();
    m.save("/home/rmaziere/DEV/QImage_TP/img_2.png");
}

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    JournalProcess* process = new JournalProcess();

    QTextEdit* logProcess = new QTextEdit(process);
    process->setWidgetResizable(true);
    logProcess->resize(process->size().width(),
        process->size().height());
    logProcess->setReadOnly(true);
    QDebugStream log(std::cout, logProcess);
    process->show();

    //dev_grid();
    //dev_all();

    MainWindow w;
    w.setWindowTitle("Map Matching");

#ifdef Q_OS_SYMBIAN
    w.showMaximized();
#else
    w.resize(360, 504);
    w.show();
#endif
    std::cout << "Tous les cout sont rediriges ici" << endl;
    return app.exec();
}
