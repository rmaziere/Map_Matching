#include "sauvegarde.h"

//Utilisation du namespace std pour standard
using namespace std;

int Sauvegarde::sauvegarderCSV(QString cheminAcces, Track maTrack)
{
    // Répertoire de l'utilisateur
    QString home = QDir::homePath();
    // Répertoire où on va enregistrer nos fichiers
    QString path = home + "/.map_matching/";
    // Créer un répertoire si nom existant
    QDir(home).mkdir(path);

    // Récupération du nom du fichier
    QStringList listChemin = cheminAcces.split("/");
    QString nomExt = listChemin.at(listChemin.size() - 1); // Récupération du dernier élément (avec extension)

    // Chemin + fichier d'origine
    QString nom = path + nomExt;

    try {
        // Charge le fichier
        QFile file(nom);
        // Si non ouvert (en mode écriture)
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            throw MyException(1, "Impossible d'écrire le fichier", 2);
        } else {
            cout << "Le fichier a été ouvert avec succès !" << endl;

            // Outil d'écriture
            QTextStream out(&file);

            // Ajout des valeurs
            for (uint i = 0; i < maTrack.getPoints().size(); ++i) {
                /** @todo save what is necessary ! */
                /*                out << maTrack.getPoints()[i]->getLatitude() << ","
                    << maTrack.getPoints()[i]->getLongitude() << ","
                    << maTrack.getPoints()[i]->getAltitude() << ","
                    << maTrack.getPoints()[i]->getTimeStamp().toString("yyyy-MM-dd hh:mm:ss")
                    << "\n";*/
            }

            // Fermeture du fichier
            file.close();
        }
    } catch (std::exception const& e) {
        cerr << "ERREUR : " << e.what() << endl;
    }

    //return app.exec();
    return 0;
}
