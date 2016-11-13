#include "grid.h"
#include <QString>
#include <QStringList>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <regex>

using namespace std;

#define DEBUG_READCSV false
#define DEBUG_ADDROAD false

Grid::Grid()
    : m_xMin(0.0)
    , m_xMax(std::numeric_limits<double>::max())
    , m_yMin(0.0)
    , m_yMax(std::numeric_limits<double>::max())
{

}

Grid::~Grid()
{
    m_mapOfAllRoads.clear();
    m_mapOfExtPoints.clear(); // should be already done at the end of reading CSV
    m_vectorOfPoints.clear();
}


void Grid::setBoundingBox(double xMin,double xMax,double yMin,double yMax)
{
    m_xMin = xMin;
    m_xMax = xMax;
    m_yMin = yMin;
    m_yMax = yMax;
}

void Grid::readFromCSV(QString filename)
{
    string line;
    QString stringConverted;
    m_gridFullName= filename.toStdString();
    // Declare file stream
    ifstream file(filename.toStdString().c_str()); // c_str() http://stackoverflow.com/questions/32332/why-dont-the-stdfstream-classes-take-a-stdstring

    vector<int> correspondance(4, -1); // Correpondance between the header and the parser :
    // correspondance :
    //  0 : # WKT
    //  1 : # Edge ID
    //  2 : # From Node
    //  3 : # To Node ID

    // Read header
    if (file.good()) {
        getline(file, line);
        stringConverted = QString::fromStdString(line);
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
    /*cout << "BEGIN CORRESPONDANCE" << endl;
    for (uint i = 0; i < correspondance.size(); ++i) {
        cout << correspondance[i] << endl;
    }
    cout << "END CORRESPONDANCE" << endl;*/

    while (file.good()) {
        long edgeId(0);
        //long fromNodeId(0);
        //long toNodeId(0);
        vector<vector<double>> listOfCoordinates(0);

        getline(file, line);
        // Convert string to Qstring (easiest
        stringConverted = QString::fromStdString(line);
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

            //Initialisation du test
            bool inBox = false;
            for (int i = 0; i < text.size(); ++i) {
                if (i == correspondance[0]) {
                    // traitement WTK
                    QStringList contenuList = text[i].split("LINESTRING (");
                    contenuList = contenuList[1].split(")");
                    QString contenu = contenuList[0];

                    QStringList listePoints = contenu.split(",");
                    if (DEBUG_READCSV) cout << "Coordonnées points : " << endl;
                    for (int j = 0; j < listePoints.size(); ++j) {
                        double x(0.0);
                        double y(0.0);
                        QStringList coordonnees = listePoints[j].split(" ");
                        x = coordonnees[0].toDouble();
                        y = coordonnees[1].toDouble();
                        inBox = inFootPrint(x,y);
                        if (DEBUG_READCSV) cout << setprecision(150) << x << "," << y << endl;
                        vector<double> coordinates;
                        coordinates.push_back(x);
                        coordinates.push_back(y);
                        listOfCoordinates.push_back(coordinates);
                    }

                } else if (i == correspondance[1]) {
                    // traitement Edge ID
                    if (DEBUG_READCSV) cout << "Edge ID : " << text[i].toStdString() << " ";
                    edgeId = text[i].toLong();
                } else if (i == correspondance[2]) {
                    // traitement From Node
                    if (DEBUG_READCSV) cout << "From Node : " << text[i].toStdString() << " ";
                    //fromNodeId = text[i].toLong();
                } else if (i == correspondance[3]) {
                    // traitement To Node ID
                    if (DEBUG_READCSV) cout << "To Node ID : " << text[i].toStdString() << " ";
                    //toNodeId = text[i].toLong();
                }
            }
            if (DEBUG_READCSV) cout << endl;
            if (inBox)
                addRoad(listOfCoordinates, edgeId);
        }
    }
    // m_mapOfExtPoints.clear(); // TODO remove comment, and DO clear map
}

void Grid::addRoad(const vector<vector<double> > &listOfCoordinates, long edgeId)
{
    int n= listOfCoordinates.size();
    int curPoint= 0;    // used to apply a special treatment to first and last point of a road
    bool newPoint= true;
    int existingPointId= -1;    // id of the point if its already exists
    Road road(edgeId);
    for (const auto& coord: listOfCoordinates) {
        newPoint= true;
        PointRoad p(coord[0], coord[1], (curPoint==0 || curPoint==n-1));
        if (curPoint==0 || curPoint==n-1) { // for extremities, check if road already exists, if so use it
            if (m_mapOfExtPoints.count(p)) {
                ExtremityPointMap::const_iterator got= m_mapOfExtPoints.find(p);
                existingPointId= got->second;
                if (DEBUG_ADDROAD) p.outputInfos();
                newPoint= false;
                p= m_vectorOfPoints[existingPointId];       // check if not a new point
            }
        }
        p.updateBelongToRoad(edgeId);
        if (newPoint) {
            p.setid(m_vectorOfPoints.size());
            m_vectorOfPoints.push_back(std::move(p));
            if (p.isNode()) m_mapOfExtPoints[p]= p.id();
        }
        road.addPoint(p.id());
        ++curPoint;
    }
    m_mapOfAllRoads[road.edgeId()]= road;
}

void Grid::outputInfos()
{
    cout << "Network " << m_gridFullName << " contains: \n\t" << m_mapOfAllRoads.size() << " roads" << endl;
    cout << "\twith a grand total of " << m_vectorOfPoints.size() << " points" << endl;
    cout << "\tof which " << m_mapOfExtPoints.size() << " are extremities." << endl;
}

bool Grid::inFootPrint(double x, double y)
{
    return (m_xMin <= x) && (x <= m_xMax) && (m_yMin <= y) && (y <= m_yMax);
}

void Grid::setDistance(PointGPS &p, Road &r)
{
    const vector<int> &listOfPointId= r.vectorOfPointsId();
    double d, bestDistance= std::numeric_limits<double>::max();
    for (uint i=1; i<listOfPointId.size(); i++) {
        d= p.distanceToSegment(m_vectorOfPoints[listOfPointId[i-1]], m_vectorOfPoints[listOfPointId[i]]);
        if (d<bestDistance) bestDistance= d;
    }
    p.addEmissionProbability(r.edgeId(), bestDistance);
}

void Grid::buildKDTree()
{

}

