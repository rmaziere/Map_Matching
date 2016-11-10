#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include <QDir>
#include <QFile>
#include <QString>
#include <QTextStream>

#include "myexception.h"
#include "track.h"

class Sauvegarde {
public:
    //Constructeur
    Sauvegarde();

    //Fonction de sauvegarde en CSV
    /**
     * @brief sauvegarderCSV save data in a CSV file
     * @param cheminAcces
     * @param maTrace
     */
    int sauvegarderCSV(QString cheminAcces, Track maTrace);

    //Destructeur
    virtual ~Sauvegarde();
};

#endif // SAUVEGARDE_H
