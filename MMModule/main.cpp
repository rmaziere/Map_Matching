#include <QApplication>
#include <QFileDialog>


#include "../exception.h"
#include "Track.h"
#include "sauvegarde.h"
using namespace std;
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

        string shp2csv_comd = "ogr2ogr -f CSV " + dest + " " +  orig;

        cout << "shp2csv_comd : " + shp2csv_comd << endl;

        system(shp2csv_comd.c_str());
        cout << "!!! Fin de fonction !!!" << endl;
}

int main(int argc, char *argv[])
{
    // Open the app
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

    Trace maTrace = Trace();
    maTrace.readFromCSV(file);

    // Debut Conversion

    shp2csv(file);

    // Fin Conversion
    
    //Instantiation de la fonction de sauvegarde d'un fichier en CSV
    Sauvegarde Test;
    Test.sauvegarderCSV(file, maTrace);

    return app.exec();
}
