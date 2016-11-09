#include "grid.h"
#include <QString>
#include <QStringList>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>


using namespace std;

grid::grid():
    m_road(0)
{

}

grid::~grid()
{
    for (uint i=0 ; i < m_road.size(); ++i)
    {
        delete m_road[i];
    }
    m_road.clear(); //vector::clear() does not free memory allocated by the vector to store objects;
    // it calls destructors for the objects it holds.
}

void grid::readFromCSV(QString filename)
{
    // Declare file stream
    ifstream file(filename.toStdString().c_str()); // c_str() http://stackoverflow.com/questions/32332/why-dont-the-stdfstream-classes-take-a-stdstring

    // Declaration
    string value; // Save the value of the line
    QString stringConverted;

    vector<int> correspondance(4,-1); // Correpondance between the header and the parser :
    // correspondance :
    //  0 : # WKT
    //  1 : # Edge ID
    //  2 : # From Node
    //  3 : # To Node ID

    // Read header
    if (file.good()) {
        // Read the line
        getline(file, value);

        // Convert string to Qstring
        stringConverted = QString::fromStdString(value);

        // Split the line with separator
        QStringList text = stringConverted.split(",");

        // Parse header
        for (int i = 0; i < text.size(); ++i) {
            if (text[i].contains(QString::fromStdString("WKT"),
                    Qt::CaseInsensitive)) {
                correspondance[0] = i;
                //cout << "WKT DETECTED at colonne : " << i << endl;
            } else if (text[i].contains(QString::fromStdString("Edge ID"),
                           Qt::CaseInsensitive)) {
                correspondance[1] = i;
                //cout << "Edge ID DETECTED at colonne : " << i << endl;
            } else if (text[i].contains(QString::fromStdString("From Node"),
                           Qt::CaseInsensitive)) {
                correspondance[2] = i;
                //cout << "From Node DETECTED at colonne : " << i << endl;
            } else if (text[i].contains(QString::fromStdString("To Node ID"),
                           Qt::CaseInsensitive)) {
                correspondance[3] = i;
                //cout << "To Node ID DETECTED at colonne : " << i << endl;
            } else {
                //cout << "Colonne " << text[i].toStdString() << " non reconnue" << endl;
            }
        }
    }

    // Display the correspondance table
    //cout << "BEGIN CORRESPONDANCE" << endl;
    for (uint i = 0; i < correspondance.size(); ++i) {
        //cout << correspondance[i] << endl;
    }
    //cout << "END CORRESPONDANCE" << endl;


    while (file.good()) {
        long edgeId(0);
        long fromNodeId(0);
        long toNodeId(0);
        vector<vector<double> > listOfCoordinates(0);

        getline(file, value);
        // Convert string to Qstring (easiest
        stringConverted = QString::fromStdString(value);
        if (stringConverted.length() != 0) // Elimine les lignes vides
        {
            // Exemple :
            //   Entrée :
            //     "LINESTRING (1.37 3.36,1.24 3.84)",839,825,883,1,22.222222219999999,10
            //   Sortie :
            //     [ LINESTRING (1.37 3.36,1.24 3.84) , 839 , 825 , 883]
            // A cause de la virgule dans linestring, on est obligé de :
            // Spliter sur les virgules les éventuels éléments avant les guillemets
            // Ajouter ce contenu à la liste
            // Spliter sur les guillemets
            // et récupérer la chaine entre les guillemets LINESTRING (1.37 3.36,1.24 3.84)
            // Ajouter ce contenu à la liste
            // Spliter sur les virgules les éventuels éléments après les guillemets
            // Supprimer le premier élement du split (car le Linestring est déjà récupéré)
            // Ajouter le reste à la liste

            QStringList linestringList = stringConverted.split("\"");

            //QString before = linestringList[0];
            //QString linestring = linestringList[1];
            //QString after = linestringList[2];

            QStringList text;

            if (!linestringList[0].isEmpty()) {
                text = linestringList[0].split(",");
            }
            text.append(linestringList[1]);

            QStringList afterSplit = linestringList[2].split(",");
            afterSplit.removeFirst();

            if (!afterSplit.isEmpty()) {
                text += afterSplit;
            }

            for (int i = 0; i < text.size(); ++i) {
                if (i == correspondance[0]) {
                    // traitement WTK

                    QStringList contenuList = text[i].split("LINESTRING (");
                    contenuList = contenuList[1].split(")");
                    QString contenu = contenuList[0];

                    QStringList listePoints = contenu.split(",");
                    cout << "Coordonnées points : " << endl;
                    for (int j = 0; j < listePoints.size(); ++j) {
                        double lat(0.0);
                        double lon(0.0);
                        QStringList coordonnees = listePoints[j].split(" ");
                        lat = coordonnees[0].toDouble();
                        lon = coordonnees[1].toDouble();
                        cout << setprecision(150) << lat << "," << lon << endl;
                        vector<double> coordinates;
                        coordinates.push_back(lat);
                        coordinates.push_back(lon);
                        listOfCoordinates.push_back(coordinates);
                    }

                } else if (i == correspondance[1]) {
                    // traitement Edge ID
                    cout << "Edge ID : " << text[i].toStdString() << " ";
                    edgeId = text[i].toLong();
                } else if (i == correspondance[2]) {
                    // traitement From Node
                    cout << "From Node : " << text[i].toStdString() << " ";
                    fromNodeId = text[i].toLong();
                } else if (i == correspondance[3]) {
                    // traitement To Node ID
                    cout << "To Node ID : " << text[i].toStdString() << " ";
                    toNodeId = text[i].toLong();
                }
            }
            cout << endl;
            addRoad(listOfCoordinates,edgeId,fromNodeId,toNodeId);

        }
    }
}

std::vector<Road *> grid::road() const
{
    return m_road;
}

void grid::addRoad(vector<vector<double> > listOfCoordinates, long edgeId, long fromNodeId, long toNodeId)
{
    m_road.push_back(new Road(listOfCoordinates, edgeId, fromNodeId, toNodeId));
}
