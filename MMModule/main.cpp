#include <QApplication>
#include <QFileDialog>
#include <math.h>
#include <vector>

#include "distance.h"
#include "file.h"
#include "grid.h"
#include "myexception.h"
#include "pointGPS.h"
#include "sauvegarde.h"
#include "track.h"

using namespace std;

/*void dev_area() {
    Track track;
    track.readFromCSV();
    grid g;
    g.setZone(track.xmin, )
    g.readFromCSV();

}*/


int main(/*int argc, char *argv[]*/)
{
    //dev_area();

    /*
    grid myNetwork;
    myNetwork.readFromCSV("../Data/Unit_tests_data_set/simpleNetworkLoaderExemple.csv");
    cout << myNetwork.m_road.size() << endl;

    for (size_t i = 0; i < myNetwork.m_road.size(); ++i) {
        cout << myNetwork.m_road[i]->getListOfPoints().size() << endl;
        cout << myNetwork.m_road[i]->getListOfPoints()[0]->m_x << endl;
    }
*/
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
