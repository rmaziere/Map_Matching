#include "trace.h"

//Utilisation du namespace std pour standard
using namespace std;

Trace::Trace()
    : m_points(0)
{

}

Trace::~Trace()
{
    for (uint i=0 ; i < m_points.size(); ++i)
    {
        delete[] m_points[i];
    }
    m_points.clear(); //vector::clear() does not free memory allocated by the vector to store objects;
    // it calls destructors for the objects it holds.
}


void Trace::readFromCSV(QString filename)
{
    // NOTE : This function doesn't read the header of csv file
    // WARNING : This function doesn't check the correct extension (trust the user who puts a csv-format file)


    cout << "Le fichier " << filename.toStdString() << " va être lu."<< endl;

    // Declare file stream
    ifstream file(filename.toStdString().c_str()); // c_str() :http://stackoverflow.com/questions/32332/why-dont-the-stdfstream-classes-take-a-stdstring

    string value;
    float latitude, longitude, altitude;
    QDateTime timeStamp;
    while ( file.good() )
    {
        getline(file, value, ',');

        if (value.length() == 0) // Elimine les lignes vides
        {
            cout << "Ligne ignorée" << endl;
            continue;
        }

        cout << "Read new point" << endl;

        // Read latitude from file
        latitude = atof(value.c_str());
        cout << "Latitude : " << latitude << " ";

        // Read longitude from file
        getline(file, value, ',');
        longitude = atof(value.c_str());
        cout << "Longitude : " << longitude << " ";

        // Read altitude from file
        getline(file, value, ',');
        altitude = atof(value.c_str());
        cout << "Altitude : " << altitude << " ";

        // Read timeStamp from file
        getline(file, value);
        // If complete timestamp with date & time
        if(value.length() == 19){
            timeStamp = QDateTime::fromString(value.c_str(),"yyyy-MM-dd hh:mm:ss");
            cout << "Date time : " << timeStamp.toString().toStdString() << endl;
        // If uncomplete timestamp with time & without date
        }else if(value.length() == 8){
            timeStamp = QDateTime::fromString(value.c_str(),"hh:mm:ss");
            cout << "Time : " << timeStamp.toString("hh:mm:ss").toStdString() << endl;
        }

        // Add the read point
        addPoint(latitude, longitude, altitude, timeStamp);
    }

    cout << "Le fichier " << filename.toStdString() << " a été lu."<< endl;
}



vector<PointTrace*> Trace::getPoints()
{
    return m_points;
}


void Trace::addPoint(float latitude, float longitude, float altitude, QDateTime timeStamp)
{
    m_points.push_back(new PointTrace(latitude, longitude, altitude, timeStamp));
}
