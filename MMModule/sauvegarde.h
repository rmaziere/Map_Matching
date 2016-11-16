#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include <QDir>
#include <QFile>
#include <QString>
#include <QTextStream>

#include "myexception.h"
#include "track.h"

/**
 * @brief Container for manipulation of files with graphic interface
 * @todo rendre la classe statique
 */
class Sauvegarde {
public:
    /**
     * @brief Constructor
     */
    Sauvegarde();

    /**
     * @brief save data in a CSV file
     * @todo Documenter les paramètres de la fonction... A quoi sert cheminAccess ?
     * @todo Refactorer les noms des paramètres
     * @param cheminAcces
     * @param maTrace
     */
    int sauvegarderCSV(QString cheminAcces, Track maTrace);

    /**
     * @brief Destructor
     */
    virtual ~Sauvegarde();
};

#endif // SAUVEGARDE_H
