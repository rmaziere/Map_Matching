#include <QApplication>
#include <QFileDialog>
#include <vector>
#include <math.h>

#include "myexception.h"
#include "track.h"
#include "sauvegarde.h"
#include "file.h"
#include "distance.h"

using namespace std;



/*void distance(int identifiantRoad, std::vector<double> pt)
{
    double distMin = 1000000;
    // For each segment in road
    std::vector<double> A(2);
    std::vector<double> B(2);
    A = road->listOfPoint{0};
    for (int i = 1; i < listOfPoints.size(); i++)
    {
        B = road->listOfPoint{i}
        d = distance2ptsegment(A,B,pt);
        if (d < distMin)
        {
            distMin = d;
        }
        A = B;
    }
    if (d <= 200)
    {
        return true;
    }
}*/



int main(/*int argc, char *argv[]*/)
{
    Distance dist;
    std::vector<double> A(2);
    A[0] = 0;
    A[1] = 0;
    std::vector<double> B(2);
    B[0] = 0;
    B[1] = 10;
    std::vector<double> C(2);
    C[0] = 1;
    C[1] = 12;
    cout << dist.distance2ptsegment(A,B,C);


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






