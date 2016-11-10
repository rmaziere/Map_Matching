#ifndef FILE_H
#define FILE_H

#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <iostream>
#include <string>

#include "myexception.h"

/**
 * @brief The File class
 */
class File {
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

    /**
     * @brief The UI to select the file's path to open
     * @param the file extension to filter
     */
    int selectFilesToOpen(QString extensionFilter);

    /**
     * @brief The UI to select the file's path to save
     * @param none
     */
    int whereSave();

    /**
     * @brief The function to convert WGS84 ShapeFile(s) to Lambert 93 CSV(s)
     * @param The geometry type (Point, Polyline)
     */
    int shp2csv(QString geometryType);

    /**
     * @brief The File destructor
     * @param none
     */
    virtual ~File() {}

    QStringList filePath;
    QStringList fileName;
    QStringList fileExtension;
};

#endif // FILE_H
