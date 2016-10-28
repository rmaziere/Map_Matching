#include <QApplication>


#include "../exception.h"
#include "trace.h"
#include "sauvegarde.h"


int main(int argc, char *argv[])
{
    //Instantiation de QApplication
    QApplication app(argc, argv);

    //Instantiation de la fonction de lecture d'un fichier CSV
    Trace maTrace = Trace();
    QString chemin = "/home/julie/Map_Matching/MMModule/csv/20090427085649.csv";
    maTrace.readFromCSV(chemin);
    for (uint i=0 ; i < maTrace.getPoints().size(); ++i)
    {
        std::cout << i << " "
                  << maTrace.getPoints()[i]->getLatitude() << " "
                  << maTrace.getPoints()[i]->getLongitude() << " "
                  << maTrace.getPoints()[i]->getAltitude() << " "
                  << maTrace.getPoints()[i]->getTimeStamp().toString().toStdString()
                  << std::endl;
    }

    //Instantiation de la fonction de sauvegarde d'un fichier en CSV
    Sauvegarde Test;
    Test.sauvegarderCSV(chemin, maTrace);

    return 0;
}
