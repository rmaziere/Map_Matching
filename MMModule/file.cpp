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
    try{
        // Set path to home Path
        QString path = QDir::homePath();

        // Select multiple files
        QStringList files;

        //Return null is cancel buttom is pressed
        files = QFileDialog::getOpenFileNames(
                        NULL,
                        "Select one or more files to open",
                        path,
                        "Fichier ." + extensionFilter + " (*." + extensionFilter + ")");

        if(files.isEmpty()){
             throw MyException(1, "No file selected !", 2);
        }
        for (int i = 0; i < files.size(); ++i){
            QString temp = files.at(i);
            splitPath(temp);
        }
    return 1;
    }
    catch(std::exception const& e){
        cerr << "ERROR : " << e.what() << endl;
        return 0;
    }


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

int File::shp2csv(QString geometryType){
    try{
        if(geometryType.isEmpty() || (geometryType != "Point" && geometryType != "Polyline")){
            throw MyException(1, "Le type de géométrie n'est pas défini ou n'est pas compatible", 2);
        }else{
            QString originPath ;
            QString destinationPath;
            string gdalGeometryParam;

            if(geometryType == "Point"){
                gdalGeometryParam = "AS_YX";
            }else if(geometryType == "Polyline"){
                gdalGeometryParam = "AS_WKT";
            }

            for (int i = 0; i < filePath.size(); ++i){
                QString tempFilePath = filePath.at(i);
                QString tempFileName = fileName.at(i);
                QString tempFileExtension = fileExtension.at(i);

                originPath = tempFilePath + tempFileName + "." + tempFileExtension;
                destinationPath = tempFilePath + tempFileName + "_L93.csv";

                string shpToCsv_command = "ogr2ogr -f CSV " + destinationPath.toStdString() + " " + originPath.toStdString() + " -t_srs EPSG:2154 -lco GEOMETRY=" + gdalGeometryParam;

                system(shpToCsv_command.c_str());//shp wgs84 => csv Lambert 93

                fileName.replace(i, tempFileName + "_L93");
                fileExtension.replace(i, "csv");
            }
            return 1;
        }
    }
    catch(std::exception const& e){
        cerr << "ERREUR : " << e.what() << endl;
    }
    return 0;
}
