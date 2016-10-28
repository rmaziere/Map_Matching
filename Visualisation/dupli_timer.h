#ifndef DUPLI_TIMER_H
#define DUPLI_TIMER_H

#include <unistd.h> // SLEEP
#include <qgsvectorlayer.h> // VECTOR LAYER
#include <qgsgeometry.h>
#include <qgsvectordataprovider.h>
#include <qgsfeaturerequest.h>

/**
 * @brief dupli_timer est une fonction qui duplique une couche vector QGIS avec un certain laps de temps entre chaque feature dupliquée
 * @param layer_init est la couche vecteur QGIS à dupliquer
 * @param duree est le temps de latence entre deux duplications de feature
 */
void dupli_timer(QgsVectorLayer *layer_init, int duree);

#endif // DUPLI_TIMER_H
