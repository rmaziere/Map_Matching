#include "grid.h"
#include <QString>
#include <QStringList>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <regex>
#include <vector>

#define DEBUG_READCSV false
#define DEBUG_ADDROAD false

long Grid::counter = 0;

Grid::Grid()
    : m_xMin(0.0)
    , m_xMax(std::numeric_limits<double>::max())
    , m_yMin(0.0)
    , m_yMax(std::numeric_limits<double>::max())
    , m_xMinGrid(std::numeric_limits<double>::max())
    , m_xMaxGrid(0.0)
    , m_yMinGrid(std::numeric_limits<double>::max())
    , m_yMaxGrid(0.0)
{
}

Grid::~Grid()
{
    m_mapOfAllRoads.clear();
    m_mapOfExtPoints.clear(); // should be already done at the end of reading CSV
    m_vectorOfPoints.clear();
}

void Grid::setTrackBoundingBox(double xMin, double xMax, double yMin, double yMax) // from GPS track
{
    m_xMin = xMin;
    m_xMax = xMax;
    m_yMin = yMin;
    m_yMax = yMax;
}

void Grid::readFromCSV(QString filename)
{

    emit signalMessage("Loading grid ...");
    std::string line;
    QString stringConverted;
    m_gridFullName = filename.toStdString();
    // Declare file stream
    std::ifstream file(filename.toStdString().c_str()); // c_str() http://stackoverflow.com/questions/32332/why-dont-the-stdfstream-classes-take-a-stdstring

    std::vector<int> correspondance(4, -1); // Correpondance between the header and the parser :
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
        std::vector<std::vector<double> > listOfCoordinates(0);

        getline(file, line);
        // Convert string to Qstring (easiest
        stringConverted = QString::fromStdString(line);
        if (stringConverted.length() != 0) // Elimine les lignes vides
        {
            // Exemple :QMetaObject
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
                    if (DEBUG_READCSV)
                        std::cout << "Coordonnées points : " << std::endl;
                    for (int j = 0; j < listePoints.size(); ++j) {
                        double x(0.0);
                        double y(0.0);
                        QStringList coordonnees = listePoints[j].split(" ");
                        x = coordonnees[0].toDouble();
                        y = coordonnees[1].toDouble();
                        inBox = inFootPrint(x, y);
                        updateGrid(x, y);
                        if (DEBUG_READCSV)
                            std::cout << std::setprecision(150) << x << "," << y << std::endl;
                        std::vector<double> coordinates;
                        coordinates.push_back(x);
                        coordinates.push_back(y);
                        listOfCoordinates.push_back(coordinates);
                    }

                } else if (i == correspondance[1]) {
                    // traitement Edge ID
                    if (DEBUG_READCSV)
                        std::cout << "Edge ID : " << text[i].toStdString() << " ";
                    edgeId = text[i].toLong();
                } else if (i == correspondance[2]) {
                    // traitement From Node
                    if (DEBUG_READCSV)
                        std::cout << "From Node : " << text[i].toStdString() << " ";
                    //fromNodeId = text[i].toLong();
                } else if (i == correspondance[3]) {
                    // traitement To Node ID
                    if (DEBUG_READCSV)
                        std::cout << "To Node ID : " << text[i].toStdString() << " ";
                    //toNodeId = text[i].toLong();
                }
            }
            if (DEBUG_READCSV)
                std::cout << std::endl;
            if (inBox)
                addRoad(listOfCoordinates, edgeId);
        }
    }
    // m_mapOfExtPoints.clear(); // TODO remove comment, and DO clear map (kept for test)
}

void Grid::addRoad(const std::vector<std::vector<double> >& listOfCoordinates, long edgeId)
{
    int n = listOfCoordinates.size();
    int curPoint = 0; // used to apply a special treatment to first and last point of a road
    bool newPoint = true;
    int existingPointId = -1; // id of the point if its already exists
    if (edgeId == 0) {
        edgeId = counter;
        counter++;
    }
    Road road(edgeId);
    for (const auto& coord : listOfCoordinates) {
        newPoint = true;
        PointRoad p(coord[0], coord[1], (curPoint == 0 || curPoint == n - 1));
        PointRoad* pp = &p;
        if (curPoint == 0 || curPoint == n - 1) { // for extremities, check if road already exists, if so use it
            if (m_mapOfExtPoints.count(p)) {
                ExtremityPointMap::const_iterator got = m_mapOfExtPoints.find(p);
                existingPointId = got->second;
                if (DEBUG_ADDROAD)
                    p.outputInfos();
                newPoint = false;
                pp = &m_vectorOfPoints[existingPointId]; // TODO error check if not a new point
            } else {
                pp = &p;
            }
        }
        pp->updateBelongToRoad(edgeId);
        if (newPoint) {
            p.setid(m_vectorOfPoints.size());
            m_vectorOfPoints.push_back(std::move(p));
            if (p.isNode())
                m_mapOfExtPoints[p] = p.id();
        }
        road.addPoint(pp->id());
        ++curPoint;
    }
    m_mapOfAllRoads[road.edgeId()] = road;
    //m_mapOfAllRoads.insert({road.edgeId(), std::move(road)});
}

void Grid::outputInfos()
{
    std::cout << "Network " << m_gridFullName << " contains: \n\t" << m_mapOfAllRoads.size() << " roads" << std::endl;
    std::cout << "\twith a grand total of " << m_vectorOfPoints.size() << " points" << std::endl;
    std::cout << "\tof which " << m_mapOfExtPoints.size() << " are extremities." << std::endl;
}

std::string Grid::infos()
{
    std::stringstream ss;
    ss << "Network " << m_gridFullName << " contains: \n\t" << m_mapOfAllRoads.size() << " roads\n";
    ss << "\twith a grand total of " << m_vectorOfPoints.size() << " points\n";
    ss << "\tof which " << m_mapOfExtPoints.size() << " are extremities.\n";
    return ss.str();
}

AllRoadMap::iterator Grid::getRoadEntry(long id)
{
    AllRoadMap::iterator got = m_mapOfAllRoads.find(id);
    return got;
}

bool Grid::inFootPrint(double x, double y)
{
    return (m_xMin <= x) && (x <= m_xMax) && (m_yMin <= y) && (y <= m_yMax);
}

void Grid::buildMarkovMatrix()
{
    bool DEBUG = false;
    // check all points and for those who are a node (extremity of a road) update all the roads
    for (const auto& p : m_vectorOfPoints) {
        if (p.isNode()) {
            const std::vector<long>& listOfRoadId = p.vectorOfRoadId();
            for (const auto roadId : listOfRoadId) {
                AllRoadMap::iterator got = getRoadEntry(roadId);
                for (const auto neighborId : listOfRoadId) {
                    got->second.addNeighbor(neighborId);
                    if (DEBUG) {
                        std::cout << "update neighbour " << std::endl;
                        got->second.outputInfos();
                    }
                }
            }
        }
    }
    // verification

    if (DEBUG) {
        std::cout << "Resutat: " << std::endl;
        for (auto& it : m_mapOfAllRoads) {
            it.second.outputInfos();
        }
    }
}

double Grid::computeDistanceFraction(PointGPS* prevPoint, PointGPS* curPoint, long prevRoadId, long curRoadId)
{
    double dbird, droad; // distance
    double r = 0.0; // fraction
    AllRoadMap::iterator got = getRoadEntry(prevRoadId);
    Road* r1 = &got->second;
    Road* r2 = &getRoadEntry(prevRoadId)->second;
    // find projection of each point on road
    std::vector<double> k1 = getProjectedPointAndDistance(prevPoint, r1);
    std::vector<double> k2 = getProjectedPointAndDistance(curPoint, r2);
    Point projR1(k1.at(0), k1.at(1)), projR2(k2.at(0), k2.at(1));
    int node = r1->getIntersectionIDWith(r2);
    Point *pnode= &m_vectorOfPoints.at(node);
    // bird distance
    dbird = prevPoint->distanceToPoint(*curPoint);
    if (prevRoadId == curRoadId) {
        //droad = getDistanceBetweenProjections(&projR1, &projR2, r1);
        droad= projR1.distanceToPoint(projR2);
    } else {
        //droad = getDistanceToExtremity(&projR1, node, r1) + getDistanceToExtremity(&projR2, node, r2);
        droad= projR1.distanceToPoint(*pnode)+ projR2.distanceToPoint(*pnode);
    }

    if (droad<0.00001 || dbird<0.00001)
        return 0.4;
    double res= 0.5;
    if (dbird>droad) res= droad/dbird; else res= dbird/droad;
    if (prevRoadId != curRoadId) res*=0.8; // malus for changing road (quick fix)
    return (res*res);
}

std::vector<double> Grid::getProjectedPointAndDistance(PointGPS* p, Road* r)
{
    std::vector<double> res, bestRes;
    double d, bestDistance = std::numeric_limits<double>::max();
    const std::vector<int>& listOfPointId = r->vectorOfPointsId();
    for (uint i = 1; i < listOfPointId.size(); i++) {
        res = p->projectionOnSegment(m_vectorOfPoints.at(listOfPointId[i - 1]), m_vectorOfPoints.at(listOfPointId[i]));
        d = res.at(2);
        if (d < bestDistance) {
            bestDistance = d;
            bestRes = res;
        }
    }
    return res;
}

int Grid::getSegmentCounter(Point* p, Road* r)
{
    double d;
    const std::vector<int>& listOfPointId = r->vectorOfPointsId();
    for (uint i = 1; i < listOfPointId.size(); i++) {
        d = p->distanceToSegment(m_vectorOfPoints.at(listOfPointId[i - 1]), m_vectorOfPoints.at(listOfPointId[i]));
        if (d <= 0.0001)
            return i;
    }
}

void Grid::updateGrid(double x, double y)
{
    m_xMinGrid = std::min(m_xMinGrid, x);
    m_xMaxGrid = std::max(m_xMaxGrid, x);
    m_yMinGrid = std::min(m_yMinGrid, y);
    m_yMaxGrid = std::max(m_yMaxGrid, y);
}

bool Grid::trackInGrid()
{
    return (xMin() >= xMinGrid()) && (xMax() <= xMaxGrid()) && (yMin() >= yMinGrid()) && (yMax() <= yMaxGrid());
}
