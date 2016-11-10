#include "track.h"
#include <QLocale>
//Utilisation du namespace std pour standard
using namespace std;

Track::Track()
    : m_points(0)
{
}

Track::~Track()
{
    for (uint i = 0; i < m_points.size(); ++i) {
        delete m_points[i];
    }
    m_points.clear(); //vector::clear() does not free memory allocated by the vector to store objects;
    // it calls destructors for the objects it holds.
}

void Track::readFromCSV(QString filename)
{
    // WARNING : This function doesn't check the correct extension (trust the user who puts a csv-format file)

    cout << "Le fichier " << filename.toStdString() << " va être lu." << endl;

    // Declare file stream
    ifstream file(filename.toStdString().c_str()); // c_str() :http://stackoverflow.com/questions/32332/why-dont-the-stdfstream-classes-take-a-stdstring

    // Declaration
    string value; // Save the value of the line
    QString stringConverted;

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
            cout << "Colonne " << text[i].toStdString() << endl;
            if (text[i].contains(QString::fromStdString("X"), Qt::CaseInsensitive)) {
                correspondance[0] = i;
                cout << "X DETECTED at colonne : " << i << endl;
            } else if (text[i].contains(QString::fromStdString("Y"), Qt::CaseInsensitive)) {
                correspondance[1] = i;
                cout << "Y DETECTED at colonne : " << i << endl;
            } else if (text[i].contains(QString::fromStdString("Lati"), Qt::CaseInsensitive)) {
                correspondance[2] = i;
                cout << "LATITUDE DETECTED at colonne : " << i << endl;
            } else if (text[i].contains(QString::fromStdString("Longi"), Qt::CaseInsensitive)) {
                correspondance[3] = i;
                cout << "LONGITUDE DETECTED at colonne : " << i << endl;
            } else if (text[i].contains(QString::fromStdString("Alti"), Qt::CaseInsensitive)) {
                correspondance[4] = i;
                cout << "ALTITUDE DETECTED at colonne : " << i << endl;
            } else if (text[i].contains(QString::fromStdString("Date"), Qt::CaseInsensitive)) {
                correspondance[5] = i;
                cout << "DATE DETECTED at colonne : " << i << endl;
            } else if (text[i].contains(QString::fromStdString("Time"), Qt::CaseInsensitive)) {
                correspondance[6] = i;
                cout << "Time DETECTED at colonne : " << i << endl;
            } else {
                cout << "Colonne " << text[i].toStdString() << " non reconnue" << endl;
            }
        }
    }

    // Display the correspondance table
    cout << "BEGIN CORRESPONDANCE" << endl;
    for (uint i = 0; i < correspondance.size(); ++i) {
        cout << correspondance[i] << endl;
    }
    cout << "END CORRESPONDANCE" << endl;

    // Parse the file
    double x(0), y(0);
    float latitude(0), longitude(0), altitude(0);
    QDateTime timeStamp(QDateTime::currentDateTime());
    while (file.good()) {
        // Reinitialize variables (default values)
        x = 0;
        y = 0;
        latitude = 0;
        longitude = 0;
        altitude = 0;
        timeStamp = QDateTime::currentDateTime();
        vector<QString> specificDate(2);

        getline(file, value);
        // Convert string to Qstring (easiest
        stringConverted = QString::fromStdString(value);

        if (stringConverted.length() != 0) // Elimine les lignes vides
        {
            cout << "Read new point" << endl;
            QStringList text = stringConverted.split(",");
            for (int i = 0; i < text.size(); ++i) {
                if (i == correspondance[0]) {
                    // Traitement X
                    // Read x from file
                    x = text[i].toDouble();

                    cout << " X : " << x << " ";
                } else if (i == correspondance[1]) {
                    // Traitement Y
                    // Read y from file
                    y = text[i].toDouble();

                    cout << " Y : " << y << " ";
                } else if (i == correspondance[2]) {
                    // Traitement Latitude
                    // Read latitude from file
                    latitude = text[i].toFloat();

                    cout << " Latitude : " << latitude << " ";
                } else if (i == correspondance[3]) {
                    // Traitement Longitude
                    // Read longitude from file
                    longitude = text[i].toFloat();

                    cout << " Longitude : " << longitude << " ";
                } else if (i == correspondance[4]) {
                    // Traitement Altitude
                    // Read altitude from file
                    altitude = text[i].toFloat();

                    cout << " Altitude : " << altitude << " ";
                } else if (i == correspondance[5]) {
                    // Traitement Date
                    // Read date from file
                    specificDate[0] = text[i];
                    cout << " Date : " << specificDate[0].toStdString();

                } else if (i == correspondance[6]) {
                    // Traitement Time
                    // Read time from file
                    specificDate[1] = text[i];
                    cout << " Time : " << specificDate[1].toStdString();
                }
            }
            if ((specificDate[0].size() == 19) && (specificDate[1].size() == 0))
                timeStamp = QDateTime::fromString(specificDate[0], "yyyy-MM-dd hh:mm:ss");
            else if ((specificDate[0].size() == 11) && (specificDate[1].size() == 0))
                timeStamp = QDateTime::fromString(specificDate[0], "yyyy-MM-dd");
            else if ((specificDate[0].size() == 0) && (specificDate[1].size() == 8))
                timeStamp = QDateTime::fromString(specificDate[1], "hh:mm:ss");
            else if ((specificDate[0].size() == 11) && (specificDate[1].size() == 8)) {
                // Attention : si les mois sont enregistres avec "Jan",
                // il faut passer en langue anglaise/americaine
                // Sinon timeStamp est vide... et c'est embetant
                QLocale locale(QLocale::English, QLocale::UnitedStates);
                timeStamp = locale.toDateTime((specificDate[0] + specificDate[1]), "dd'-'MMM'-'yyyyhh':'mm':'ss");
            }
            cout << "timestamp : " << timeStamp.toString("yyyy-MM-dd hh:mm:ss").toStdString();
            cout << endl;
            // Add the read point
            addPoint(x, y, latitude, longitude, altitude, timeStamp);
        } else {
            cout << "Ligne ignorée" << endl;
            continue;
        }
    }

    cout << "Le fichier " << filename.toStdString() << " a été lu." << endl;
}

vector<PointGPS*> Track::getPoints()
{
    return m_points;
}

void Track::addPoint(double x, double y, float latitude, float longitude, float altitude, QDateTime timeStamp)
{
    m_points.push_back(new PointGPS(x, y, latitude, longitude, altitude, timeStamp));
}

void Track::addPoint(float latitude, float longitude, float altitude, QDateTime timeStamp)
{
    m_points.push_back(new PointGPS(latitude, longitude, altitude, timeStamp));
}

void Track::temporalFilter(int interval)
{
    PointGPS* pointPrecedent;

    bool firstElement(true);
    for (vector<PointGPS*>::iterator b = m_points.begin(); b != m_points.end();) {
        if (firstElement) {
            pointPrecedent = *b;
            firstElement = false;
            ++b;
        } else {
            if ((*b)->getTimeStamp().toTime_t() - pointPrecedent->getTimeStamp().toTime_t() <= interval) {
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
    for (uint i = 0; i < m_points.size(); i++) { // on parcourt la liste des points
        // tant qu on ne se trouve pas sur le dernier point
        //&& (security segmentation)
        // tant que l interval est inferieure a la distance au point suivant
        while (i != m_points.size() - 1 && interval > m_points[i]->distance2pt(*m_points[i + 1])) {
            this->delPointGPS(i + 1); // on supprime le point suivant
        }
    }
}

void Track::delPointGPS(int occurrence)
{
    m_points.erase(m_points.begin() + occurrence);
}

void Track::includingRectangle(double x, double y)
{
    xmin = std::min(xmin, x);
    xmax = std::max(xmax, x);
    ymin = std::min(ymin, y);
    ymax = std::max(ymax, y);
}
