#include <QtGui/QApplication>

#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <vector>

#include "myexception.h"

#include "GUI/controller.h"
#include "solver.h"

#include "MainWindow.h"

#include "grid.h"
#include "track.h"
#include "pointGPS.h"


using namespace std;
/*! \mainpage This is the official documentation for the Map Matching project
 *
 * \section install_sec Dependances
 *
 * QT4 : sudo apt-get install libqt4-dev
 *
 *
 * <a href="https://rmaziere.github.io/Map_Matching/">Website</a>
 *
 */
void dev_thread()
{
    QThread* thread = new QThread();
    Solver* solver = new Solver();
    solver->m_trackFilename = "../Data/Seattle/useful_all_track.csv";
    solver->m_gridFilename = "../Data/Seattle/useful_all_network.csv";
    //solver->m_trackFilename = "../Data/Seattle/mini_start_track.csv";
    //solver->m_gridFilename = "../Data/Seattle/mini_start_network.csv";

    //solver->m_trackFilename = "../Data/France/Zones/Trace_Z5_L93.csv";
    //solver->m_gridFilename = "../Data/France/Zones/Route_Ready_Z5_L93.csv";

    solver->moveToThread(thread);
    thread->start();
    Controller* controller = new Controller();
    //QMetaObject::invokeMethod(solver, "onSignalStart");
    controller->addSolver(solver);
    controller->connectSignals();
    controller->m_qProcessViewer->resize(500, 500);
    controller->m_qProcessViewer->show();
}

void dev_grid()
{
    QString gridFile = "../Data/Unit_tests_data_set/gridTestPointsHaveNoDuplicate.csv";
    Grid grid;
    grid.readFromCSV(gridFile);
    grid.buildMarkovMatrix();
    grid.outputInfos();
}

void dev_gridAndTrack()
{
    // grid.readFromCSV("../Data/Unit_tests_data_set/gridTestPointsHaveNoDuplicate.csv");
    QString trackFile = "../Data/Seattle/mini_start_track.csv";
    QString gridFile = "../Data/Seattle/mini_start_network.csv";
    int test = 1;
    switch (test) {
    case 1:
        trackFile = "../Data/Seattle/useful_all_track.csv";
        gridFile = "../Data/Seattle/useful_all_network.csv";
    }

    Track track;
    Grid grid;
    track.readFromCSV(trackFile);
    track.outputInfos();

    grid.setTrackBoundingBox(track.m_xMin, track.m_xMax, track.m_yMin, track.m_yMax);
    grid.readFromCSV(gridFile);
    grid.outputInfos();
    grid.buildMarkovMatrix();
    //Solver solver();
    //grid.getRoads(), grid.getPoints(), track.getPointsAsPointer());
    //solver.initialize();

    std::cout << "The end." << std::endl;
}

void dev_file()
{
    File f;
    f.selectFilesToOpen("shp");
    cout << "File name : " << f.fileName.at(0).toStdString() << ", file extension : " << f.fileExtension.at(0).toStdString() << endl;

    cout << f.shp2csv("Point") << endl;
    cout << "File path : " << f.filePath.at(0).toStdString() << "File name : " << f.fileName.at(0).toStdString() << ", file extension : " << f.fileExtension.at(0).toStdString() << endl;
}

/*void dev_img()
{
    vector<vector<double> > poly;

    for (int i = 0; i <= 1000; i += 150) {
        double x = i + 25;
        double y = i * 0.75;
        vector<double> coordinates;
        coordinates.push_back(x);
        coordinates.push_back(y);
        poly.push_back(coordinates);
    }

    vector<vector<double> > polyRoad;

    vector<double> coordinates;
    coordinates.push_back(1000.25);
    coordinates.push_back(3352.28);
    polyRoad.push_back(coordinates);

    coordinates.clear();

    coordinates.push_back(2000.0);
    coordinates.push_back(6000.0);
    polyRoad.push_back(coordinates);

    Map m(1280, 1024);

    m.scaleCalculator(1000.25, 2000.75, 3352.28, 6000.67);

    m.deltaCalculator(1000.25, 3352.28);

    m.makePolyline(poly, "green");

    m.makePolylineFromRoad(polyRoad, "grey");

    vector<vector<double> > point;

    vector<double> pcoordinates;
    pcoordinates.push_back(1800.0);
    pcoordinates.push_back(4800.0);
    point.push_back(pcoordinates);

    m.makePointFromTrack(point, "orange");

    m.landmarkMaker(200);

    QLabel* myLabel = new QLabel();
    myLabel->setPixmap(QPixmap::fromImage(m.img));

    myLabel->show();

    m.save("/tmp/test.png");

    cout << "width : " << m.width << endl;
    cout << "height : " << m.height << endl;
    cout << "Facteur d'échelle : " << m.scale << endl;
}*/

void dev_ui()
{
    //Fenetre non enlevable
    MainWindow* w = new MainWindow();
    w->setWindowTitle("Map Matching");

    w->resize(500, 700);
    w->show();
}

/****************************************************************************/
/*** Pas de code dans le main, seulement l'appel d'une fonction ci-dessus ***/
/****************************************************************************/

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    //dev_img();

    dev_thread();
    //dev_ui();

    return app.exec();
    //return app.closingDown();
}
