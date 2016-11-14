#include "track.h"
#include <limits>
#include <QLocale>

using namespace std;

#define DEBUG_READCSV false

Track::~Track()
{
    for (uint i = 0; i < m_points.size(); ++i) {
        delete m_points[i];
    }
    m_points.clear();
}

// WARNING : This function doesn't check the correct extension (trust the user who puts a csv-format file)
void Track::readFromCSV(QString filename)
{
    string value; // Save the value of the line
    QString stringConverted;

    m_trackFullName= filename.toStdString();

    if (DEBUG_READCSV) cout << "Le fichier " << filename.toStdString() << " va être lu." << endl;
    ifstream file(filename.toStdString().c_str()); // c_str() :http://stackoverflow.com/questions/32332/why-dont-the-stdfstream-classes-take-a-stdstring
    vector<int> correspondance(7); // Correpondance between the header and the parser :
    // correspondance :
    //  0 : # x
    //  1 : # y
    //  2 : # latitude column
    //  3 : # longitude column
    //  4 : # altitude column
    //  5 : # date column
    //  6 : # time column
    for (uint i = 0; i < correspondance.size(); ++i) {
        correspondance[i] = -1;
    }

    // Read header
    if (file.good()) {
        // Read the line
        getline(file, value);

        // Convert string to Qstring (easiest
        stringConverted = QString::fromStdString(value);

        // Split the line with separator
        QStringList text = stringConverted.split(",");
        //vector<string> text = split(value,',');

        // Parse header

            for (int i = 0; i < text.size(); ++i) {
                if (DEBUG_READCSV) cout << "Colonne " << text[i].toStdString() << endl;
                if (text[i].contains(QString::fromStdString("X"), Qt::CaseInsensitive)&&(!(text[i].contains(QString::fromStdString("max"), Qt::CaseInsensitive)))) {
                    correspondance[0] = i;
                    if (DEBUG_READCSV) cout << "X DETECTED at colonne : " << i << endl;
                } else if ((text[i].contains(QString::fromStdString("Y"), Qt::CaseInsensitive))&&(!(text[i].contains(QString::fromStdString("Type"), Qt::CaseInsensitive)))) {
                    correspondance[1] = i;
                    if (DEBUG_READCSV) cout << "Y DETECTED at colonne : " << i << endl;
                } else if (text[i].contains(QString::fromStdString("Lati"), Qt::CaseInsensitive)) {
                    correspondance[2] = i;
                    if (DEBUG_READCSV) cout << "LATITUDE DETECTED at colonne : " << i << endl;
                } else if (text[i].contains(QString::fromStdString("Longi"), Qt::CaseInsensitive)) {
                    correspondance[3] = i;
                    if (DEBUG_READCSV) cout << "LONGITUDE DETECTED at colonne : " << i << endl;
                } else if (text[i].contains(QString::fromStdString("Alti"), Qt::CaseInsensitive)) {
                    correspondance[4] = i;
                    if (DEBUG_READCSV) cout << "ALTITUDE DETECTED at colonne : " << i << endl;
                } else if (text[i].contains(QString::fromStdString("Date"), Qt::CaseInsensitive)) {
                    correspondance[5] = i;
                    if (DEBUG_READCSV) cout << "DATE DETECTED at colonne : " << i << endl;
                } else if ((text[i].contains(QString::fromStdString("Time"), Qt::CaseInsensitive))||(text[i].contains(QString::fromStdString("Heure"), Qt::CaseInsensitive))) {
                    correspondance[6] = i;
                    if (DEBUG_READCSV) cout << "Time DETECTED at colonne : " << i << endl;
                } else {
                    if (DEBUG_READCSV) cout << "Colonne " << text[i].toStdString() << " non reconnue" << endl;
                }
            }

        }

    // Display the correspondance table
    if (DEBUG_READCSV) cout << "BEGIN CORRESPONDANCE" << endl;
    for (uint i = 0; i < correspondance.size(); ++i) {
        if (DEBUG_READCSV) cout << correspondance[i] << endl;
    }
    if (DEBUG_READCSV) cout << "END CORRESPONDANCE" << endl;

    // Parse the file
    double x(0), y(0);
    float latitude(0), longitude(0), altitude(0);
    QDateTime ts(QDateTime::currentDateTime());
    while (file.good()) {
        // Reinitialize variables (default values)
        x = 0;
        y = 0;
        latitude = 0;
        longitude = 0;
        altitude = 0;
        ts = QDateTime::currentDateTime();
        vector<QString> specificDate(2);

        getline(file, value);
        stringConverted = QString::fromStdString(value);

        if (stringConverted.length() != 0) // Elimine les lignes vides
        {
            if (DEBUG_READCSV) cout << "Read new point" << endl;
            QStringList text = stringConverted.split(",");
            for (int i = 0; i < text.size(); ++i) {
                if (i == correspondance[0]) {
                    // Traitement X
                    // Read x from file
                    x = text[i].toDouble();

                    if (DEBUG_READCSV) cout << " X : " << x << " ";
                } else if (i == correspondance[1]) {
                    // Traitement Y
                    // Read y from file
                    y = text[i].toDouble();

                    if (DEBUG_READCSV) cout << " Y : " << y << " ";
                } else if (i == correspondance[2]) {
                    // Traitement Latitude
                    // Read latitude from file
                    latitude = text[i].toFloat();

                    if (DEBUG_READCSV) cout << " Latitude : " << latitude << " ";
                } else if (i == correspondance[3]) {
                    // Traitement Longitude
                    // Read longitude from file
                    longitude = text[i].toFloat();

                    if (DEBUG_READCSV) cout << " Longitude : " << longitude << " ";
                } else if (i == correspondance[4]) {
                    // Traitement Altitude
                    // Read altitude from file
                    altitude = text[i].toFloat();

                    if (DEBUG_READCSV) cout << " Altitude : " << altitude << " ";
                } else if (i == correspondance[5]) {
                    // Traitement Date
                    // Read date from file
                    specificDate[0] = text[i];
                    if (DEBUG_READCSV) cout << " Date : " << specificDate[0].toStdString();

                } else if (i == correspondance[6]) {
                    // Traitement Time
                    // Read time from file
                    specificDate[1] = text[i];
                    if (DEBUG_READCSV) cout << " Time : " << specificDate[1].toStdString();
                }
            }
            if ((specificDate[0].size() == 19) && (specificDate[1].size() == 0))
                ts = QDateTime::fromString(specificDate[0], "yyyy-MM-dd hh:mm:ss");
            else if ((specificDate[0].size() == 11) && (specificDate[1].size() == 0))
                ts = QDateTime::fromString(specificDate[0], "yyyy-MM-dd");
            else if ((specificDate[0].size() == 0) && (specificDate[1].size() == 8))
                ts = QDateTime::fromString(specificDate[1], "hh:mm:ss");
            else if ((specificDate[0].size() == 11) && (specificDate[1].size() == 8)) {
                // Attention : si les mois sont enregistres avec "Jan",
                // il faut passer en langue anglaise/americaine
                // Sinon timeStamp est vide... et c'est embetant
                QLocale locale(QLocale::English, QLocale::UnitedStates);
                ts = locale.toDateTime((specificDate[0] + specificDate[1]), "dd'-'MMM'-'yyyyhh':'mm':'ss");
            }
            if (DEBUG_READCSV) cout << "timestamp : " << ts.toString("yyyy-MM-dd hh:mm:ss").toStdString();
            if (DEBUG_READCSV) cout << endl;
            addPoint(x, y, altitude, ts.toTime_t());
        } else {
            if (DEBUG_READCSV) cout << "Ligne ignorée" << endl;
            continue;
        }
    }
    applyThresholdToBox();
    if (DEBUG_READCSV) cout << "Le fichier " << filename.toStdString() << " a été lu." << endl;
}

vector<PointGPS*> Track::getPoints()
{
    return m_points;
}

void Track::temporalFilter(uint interval)
{
    PointGPS* pointPrecedent;

    bool firstElement(true);
    for (vector<PointGPS*>::iterator b = m_points.begin(); b != m_points.end();) {
        if (firstElement) {
            pointPrecedent = *b;
            firstElement = false;
            ++b;
        } else {
            if ((*b)->timeStamp() - pointPrecedent->timeStamp() <= interval) {
                b = m_points.erase(b); // reseat iterator to a valid value post-erase
                cout << "point supprimé" << endl;
            } else {
                pointPrecedent = *b;
                ++b;
            }
        }
    }
}

void Track::spaceFilter(double interval)
{
    for (uint i = 0; i < m_points.size(); i++) { // on parcours la liste des points
        // tant qu on ne se trouve pas sur le dernier point
        //&& (security segmentation)
        // tant que l interval est inferieure a la distance au point suivant
        while (i != (m_points.size() - 1) && (interval > m_points[i]->distanceToPoint(*m_points[i + 1]))) {
            this->delPointGPS(i + 1); // on supprime le point suivant
        }
    }
}

void Track::delPointGPS(int occurrence)
{
    m_points.erase(m_points.begin() + occurrence);
}

void Track::addPoint(double x, double y, float altitude, unsigned int timeStamp)
{
    updateBox(x, y);
    m_points.push_back(new PointGPS(x,y,altitude,timeStamp));
}

void Track::updateBox(double x, double y)
{
    m_xMin = std::min(m_xMin,x);
    m_xMax = std::max(m_xMax,x);
    m_yMin = std::min(m_yMin,y);
    m_yMax = std::max(m_yMax,y);
}

void Track::applyThresholdToBox()
{
    m_xMin-= DISTANCE_THRESHOLD;
    m_yMin-= DISTANCE_THRESHOLD;
    m_xMax+= DISTANCE_THRESHOLD;
    m_yMax+= DISTANCE_THRESHOLD;
}

void Track::outputInfos()
{
    cout << "Track " << m_trackFullName << " contains: \n\t" << m_points.size() << " points" << "\n\tin box:";
    cout << "\n\t\t min (x,y) (" << m_xMin << ", " << m_yMin << ")";
    cout << "\n\t\t max (x,y) (" << m_xMax << ", " << m_yMax << ")" << endl;
}
