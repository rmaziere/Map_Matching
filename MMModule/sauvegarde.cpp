#include "sauvegarde.h"
#include "../exception.h"

//Utilisation du namespace std pour standard
using namespace std;

//Fonction de sauvegarde en CSV
Sauvegarde::Sauvegarde()
{

}

int Sauvegarde::sauvegarderCSV(int argc, char *argv[]){

    // Répertoire de l'utilisateur
    QString path = QDir::homePath();

    // Nom du fichier initialisé
    QString fichier;

    // Sélection du chemin et du nom du fichier
    while (fichier.isEmpty())
    {
        fichier = QFileDialog::getSaveFileName(NULL, "Enregistrer un fichier", path, "Fichier .csv (*.csv)");
    }

    // Chemin + fichier
    QString nom = fichier + ".csv";

    try{
        // Charge le fichier
        QFile file(nom);
        // Si non ouvert (en mode écriture)
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
            throw Erreur(1, "Impossible d'écrire le fichier", 2);
        }
        else{
            cout << "Le fichier a été ouvert avec succès !" << endl;

            // Outil d'écriture
            QTextStream out(&file);

            // Ajout des valeurs
            out << "Bonjour!\n";
            out << "J'écris dans un fichier txt!\n";

            // Fermeture du fichier
            file.close();
        }
    }
    catch(std::exception const& e){
        cerr << "ERREUR : " << e.what() << endl;
    }

    //return app.exec();
    return 0;
}

Sauvegarde::~Sauvegarde()
{

}
