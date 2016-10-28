#include <QApplication>
#include <QFileDialog>


#include "../exception.h"
#include "trace.h"
#include "sauvegarde.h"


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
                        "Fichier .csv (*.csv)");
    }

    Trace maTrace = Trace();
    maTrace.readFromCSV(file);
    
    //Instantiation de la fonction de sauvegarde d'un fichier en CSV
    Sauvegarde Test;
    Test.sauvegarderCSV(file, maTrace);

    return app.exec();
}
