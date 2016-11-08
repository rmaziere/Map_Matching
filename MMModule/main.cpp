#include <QApplication>
#include <QFileDialog>
#include <vector>
#include <math.h>

#include "myexception.h"
#include "track.h"
#include "sauvegarde.h"
#include "file.h"

using namespace std;

double distance2pt(std::vector<double> pt1,std::vector<double> pt2)
{
    return sqrt(pow(pt2[0]-pt1[0],2)+pow(pt2[1]-pt1[1],2));
}

double distance2ptsegment(std::vector<double> A,std::vector<double> B, std::vector<double> pt)
{
    if ((B[0] == A[0]) && (B[1] == A[1]))
    {
        return distance2pt(A,pt);
    }
    else
    {
        double num = (pt[0] - A[0]) * (B[0] - A[0]) + (pt[1] - A[1]) * (B[1] - A[1]);
        double tSol = num / pow(distance2pt(A,B),2);
        double t = std::max(0.0, std::min(1.0, tSol));
        std::vector<double> proj(2);
        proj[0] = A[0] + t * (B[0] - A[0]);
        proj[1] = A[1] + t * (B[1] - A[1]);
        return distance2pt(pt, proj);
    }
}

/*void distance(int identifiantRoad, std::vector<double> pt)
{
    double distMin = 1000000;
    // For each segment in road
    // distance2ptsegment();
    //Remplissage.......
    distMin = double(identifiantRoad) + pt[0];
}*/


void shp2csv(QString path)
{
    // Récupération du nom du fichier
        QStringList spliter2 = path.split(".");
        QStringList spliter = path.split("/");
        string filePath= spliter2.at(0).toStdString(); // Récupération du chemin du fichier
        string fileName= spliter.at(spliter.size()-1).toStdString(); // Récupération du non du fichier avec extension

        string dest = filePath + ".csv";
        string orig = path.toStdString();

        cout << "Origine : " + orig << endl;
        cout << "Destination : " + dest << endl;
}


int main(/*int argc, char *argv[]*/)
{
    std::vector<double> A(2);
    A[0] = 0;
    A[1] = 0;
    std::vector<double> B(2);
    B[0] = 0;
    B[1] = 10;
    std::vector<double> C(2);
    C[0] = 1;
    C[1] = 12;
    cout << distance2ptsegment(A,B,C);
    /*// Open the app
    QApplication app(argc, argv);

    // Set path to home Path
    QString path = QDir::homePath();

    // Select file
    QString file;
    while (file.isEmpty())
    {
        file = QFileDialog::getOpenFileName(
                        NULL,
                        "Select one or more files to open",
                        path,
                        "Fichier .csv (*.csv);; Fichier .shp (*.shp)");
    }

    Track maTrack = Track();
    maTrack.readFromCSV(file);

    // Debut Conversion

    shp2csv(file);

    // Fin Conversion
    
    //Instantiation de la fonction de sauvegarde d'un fichier en CSV
    Sauvegarde Test;
    Test.sauvegarderCSV(file, maTrack);

    return app.exec();*/
    /*
    QApplication app(argc, argv);

    File Test;
    QString ext = "shp";

    Test.selectFilesToOpen(argc, argv, ext);
    Test.shp2csv();
    Test.whereSave();

    for (int i = 0; i < Test.filePath.size(); ++i){
        QString tempFilePath = Test.filePath.at(i);
        QString tempFileName = Test.fileName.at(i);
        QString tempFileExtension = Test.fileExtension.at(i);
        cout << tempFilePath.toStdString() << " - "
             << tempFileName.toStdString() << " - "
             << tempFileExtension.toStdString() << endl;
    }
    return app.exec();*/
}






