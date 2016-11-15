#ifndef FILE_H
#define FILE_H

/**
  * @file file.h
  */

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
     */
    File();

    /**
     * @brief The split function to split the path file to filePath, fileName, fileExtension attributes
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

    /**
     * @name All the informations of the files list
     */
    //@{
    QStringList filePath; /**< The path of files*/
    QStringList fileName; /**< The name of files*/
    QStringList fileExtension; /**< The extension of files*/
    //@}
};

#endif // FILE_H
