#include <QApplication>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QString>

#include <QTextStream>

#include <iostream>
#include <string>

#include "../trace.h"

using namespace std;

int main(int argc, char* argv[])
{
    // Open the app
    QApplication app(argc, argv);

    // Set path to home Path
    QString path = QDir::homePath();

    // Select multiple files
    QStringList files;
    while (files.isEmpty()) {
        files = QFileDialog::getOpenFileNames(
            NULL,
            "Select one or more files to open",
            path,
            "Fichier .csv (*.csv)");
    }

    // Parse each file
    QStringList::Iterator it = files.begin();
    std::vector<Trace*> traces(files.size());

    // Initialize a vector of Trace
    for (uint i = 0; i < traces.size(); ++i) {
        traces[i] = new Trace();
    }

    std::vector<Trace*>::iterator itTrace = traces.begin();
    for (std::vector<Trace *>::iterator itTrace = traces.begin(); it != files.end(); ++it, ++itTrace) {
        (*itTrace)->readFromCSV(*it);
    }
    /*
    std::vector<Trace*>::iterator itTrace = traces.begin();
    while(it != files.end()) {

        (*itTrace)->readFromCSV(*it);
        ++itTrace;
        ++it;
    }
    */

    return app.exec();
}
