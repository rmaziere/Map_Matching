#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

#include <QString>
#include <QFileDialog>
#include <QApplication>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <string>


class Sauvegarde
{
public:

    //Constructeur
    Sauvegarde();

    //Fonction de sauvegarde en CSV
    int sauvegarderCSV(int argc, char *argv[]);

    //Destructeur
    virtual ~Sauvegarde();
};

#endif // SAUVEGARDE_H
