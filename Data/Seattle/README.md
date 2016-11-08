# Description des fichiers data

Les données proviennent de la publication qui sert pour l'implémentation de l'algorithme.

## Données brutes fournies 

### Publication et présentation

1- `Hidden Markov Map Matching Through Noise and Sparseness<..>.pptx`
2- `map matching ACM GIS camera ready.pdf`

### Données brutes 

Les données brutes sont au format csv avec une ligne d'entête décrivant chaque champs. Les coordonnées sont exprimées en latitudes / longitudes

1- Réseau routier de la ville de Seattle : `road_network.txt`
2- Traces GPS : `gps_data.txt`
3- Traces GPS corrigées : `ground_truth_route.txt`

### Projet QGIS

`jeudetest.qgs`et les fichiers QGIS associés montrent l'emprise du réseau et la trace GPS.

### Données exploitables par l'algorithme

Les données brutes sont transformées pour être exprimée en mètres dans la projection adéquate (EPSG 32048 pour Seattle).

Les fichiers suivants sont correspondent à la trace entière :
1- Réseau routier de la ville de Seattle : `road_network_meters.csv`
2- Réseau routier de la ville de Seattle réduit à un rectangle englobant la trace GPS : `road_road_network_meters_utile.csv`
2- Traces GPS : `track_meters.csv`
3- Traces GPS corrigées : `ground_truth_route.txt`


> **NOTE** Il faudrait créer des jeux de tests plus petits pour tester l'algorithme sans perdre de temps durant les phases lecture de fichiers  + initialisation des structures de données