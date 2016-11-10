#include "file.h"

File::File(){}

int File::splitPath(QString fileGlobalPath){
    if(fileGlobalPath.isEmpty()){
        return 1;
    }else{
        QStringList splitter = fileGlobalPath.split(".");

        QString pathWithoutExtension = splitter.at(0); //Path +  fileName

        QStringList splitter2 = pathWithoutExtension.split("/");

        QString QSfileName = splitter2.at(splitter2.length()-1); //fileName
        fileName << splitter2.at(splitter2.length()-1); //fileName

        filePath << pathWithoutExtension.left(pathWithoutExtension.length() - QSfileName.length()); //path

        fileExtension << splitter.at(1).toLower(); //fileExtension

        return 0;
    }
}

int File::selectFilesToOpen(QString extensionFilter){
    // Set path to home Path
    QString path = QDir::homePath();

    // Select multiple files
    QStringList files;
    while (files.isEmpty())
    {
        files = QFileDialog::getOpenFileNames(
                        NULL,
                        "Select one or more files to open",
                        path,
                        "Fichier ." + extensionFilter + " (*." + extensionFilter + ")");
    }
    for (int i = 0; i < files.size(); ++i){
        QString temp = files.at(i);
        splitPath(temp);
    }

    return 0;
}

int File::whereSave(){
    QString filters("ShapeFile (*.shp);;Text files (*.csv *.txt);;All files (*.*)");
    QString defaultFilter("Text files (*.csv)");

    // UI Save File
    QString fileGlobalPath = QFileDialog::getSaveFileName(0, "Save file", QDir::currentPath(),
                                                        filters, &defaultFilter);
    if (!fileGlobalPath.isEmpty()) {
    splitPath(fileGlobalPath);
    }

    return 0;
}

int File::shp2csv(){
    QString originPath ;
    QString destinationPath;

    for (int i = 0; i < filePath.size(); ++i){
        QString tempFilePath = filePath.at(i);
        QString tempFileName = fileName.at(i);
        QString tempFileExtension = fileExtension.at(i);

        originPath = tempFilePath + tempFileName + "." + tempFileExtension;
        destinationPath = tempFilePath + tempFileName + "_L93.csv";

        string shpToCsv_command = "ogr2ogr -f CSV " + destinationPath.toStdString() + " " + originPath.toStdString() + " -s_srs EPSG:4326 -t_srs EPSG:2154 -lco GEOMETRY=AS_YX";

        system(shpToCsv_command.c_str());//shp wgs84 => csv Lambert 93
    }
    return 0;
}
