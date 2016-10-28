#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include <QString>
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <string>
#include "trace.h"


class Sauvegarde
{
public:

    //Constructeur
    Sauvegarde();

    //Fonction de sauvegarde en CSV
    /**
     * @brief sauvegarderCSV save data in a CSV file
     * @param cheminAcces
     * @param maTrace
     */
    int sauvegarderCSV(QString cheminAcces, Trace maTrace);

    //Destructeur
    virtual ~Sauvegarde();
};

#endif // SAUVEGARDE_H
