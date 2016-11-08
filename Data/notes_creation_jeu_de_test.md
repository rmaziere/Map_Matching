# Création d'un jeu de test

## Cas de Seattle

A partir du projet QGIS, il faut sélectionner une portion de trace GPS et une portion du réseau routier qui doit englober chaque point GPS sélectionner avec une marge de 200m (600m pour plus de sécurité).

Nommage proposé `xxx_yyy_zzz.csv`. Par exemple, pour une trace courte qui est au début de la trace complète, on nomme les fichiers  `mini_start_network.csv` et `mini_start_road.csv`:
- `mini`: trace et zone du réseau réduites
- `start`: caractéristique de la trace (ici début du parcours)
- `network` ou `road` pour le type de données.


### Sauvegarde de la trace GPS

1 - prendre SCR sélectionné (Seattle : EPSG 32048)
2 - save AS_xy

### Sauvegarde dy réseau
 
1 - prendre SCR sélectionné (Seattle : EPSG 32048)
2 - save AS_WKT