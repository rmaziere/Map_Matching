#include<dupli_timer.h>

void dupli_timer(QgsVectorLayer *layer_init, int duree){

    // CREATION de la nouvelle couche  QgsVectorLayer(data_source,                          layer_name, provider_name
    QgsVectorLayer *layer_dupli = new QgsVectorLayer("point?crs=epsg:4326&field=id:integer", "Point dupliqués",  "memory");
    // Gets the map canvas
    QgsMapCanvas *canvas = m_GISInterface->mapCanvas();

    // si les 2 couches sont valides
    if(layer_dupli->isValid() && layer_init->isValid()){

        QgsMessageLog::instance()->logMessage("Validation des couches !\n");
        // Registers the layer
        QgsMapLayerRegistry::instance()->addMapLayer(layer_dupli);
        // Creation de la nouvelle liste
        QgsFeatureList FeatureList2;
        QgsMessageLog::instance()->logMessage("Création de la nouvelle liste !\n");
        // Creation du nouveau DataProvider
        QgsVectorDataProvider *pr2 = layer_dupli->dataProvider();

        // selectionne toutes les feature la couche d entree
        layer_init->selectAll();
        // conteur des points de la couche (peut servir pour le TIMER)
        long int cont=1;

        // pour chaque FEATURE de la couche d entree
        for(QgsFeature feature : layer_init->selectedFeatures()){

            sleep(duree); // en seconde !!!

            // ajout de la feature a la liste 2
            FeatureList2.append(feature);
            QString QS_cont = QString::number(cont);
            QgsMessageLog::instance()->logMessage("Création du point "+QS_cont);
            cont++;

            // AJOUT de la feature list 2 dans la couche
            pr2->addFeatures(FeatureList2);
            QgsMessageLog::instance()->logMessage("Ajout de la FeatureList2 à la couche dupliquée !\n");

            // rafraichit l affichage de la couche dupliquee dans QGIS
            layer_dupli->reload();
            layer_dupli->updateExtents();
            canvas->refresh();
            canvas->updateMap();
            canvas->refreshAllLayers();
            canvas->updateFullExtent();
            canvas->updateOverview();

        }

        // deselectionne la couche d entree
        layer_init->removeSelection();

    }else{

        QgsMessageLog::instance()->logMessage("Erreur lors de la validation des couches !\n");

    }

}
