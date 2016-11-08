#ifndef FILE_H
#define FILE_H

#include <iostream>
#include <string>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>

#include "myexception.h"

/**
 * @brief The File class
 */
class File
{
public:
    /**
     * @brief The File constructor
     * @param none
     */
    File();

    /**
     * @brief The split function to split the path file to filePath, fileName, fileExtension
     * @param The Global file's path
     */
    int splitPath(QString fileGlobalPath);

    int selectFilesToOpen(int argc, char *argv[], QString extensionFilter);

    /**
     * @brief The UI to select the file's path to save
     * @param none
     */
    int whereSave();

    /**
     * @brief The function to convert WGS84 ShapeFile(s) to Lambert 93 CSV(s)
     * @param none
     */
    int shp2csv();

    /**
     * @brief The File destructor
     * @param none
     */
    virtual ~File(){}

protected:
    QStringList filePath;
    QStringList fileName;
    QStringList fileExtension;
};

#endif // FILE_H
