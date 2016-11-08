# Notes pour l'implémentation de la correction de traces

## Sources
- Construction du modèle : <https://en.wikipedia.org/wiki/Hidden_Markov_model>
- Choix du chemin le plus probable : <https://en.wikipedia.org/wiki/Viterbi_algorithm>

## Outils/Méthodologies/etc
---

Le code n'utilise que **C++11** (pas de QT) pour des raisons de performances. Il peut être lancé pas à pas et sort à chaque étape, les segments sélectionnés (donc 1 par entrée GPS). Si l'on arrive à installer **pybind11** (https://github.com/pybind/pybind11) Python récupère les informations et les met en forme :
- affichage graphique des traces (avec mémoire des x étapes précédentes)
- affichage formaté des évaluations   

## Étapes de l'algorithme

1. Lecture du réseau, transformation
2. Lecture de la trace
  * Paramétrage (filtrage, ...)
  * Transformation et filtrage
3. Initialisation
  * Éliminer du réseau les segments > 200 mètres d'un point GPS
  * Initialiser tous les segments


 > **Note** Le processus de lecture des fichiers, filtrage et construction/peuplement des structures de données  sera probablement long (>60s), il faudra penser à créer des jeux de tests plus petits ou à sauvegarder cette étape en format binaire (idéalement)

## Étapes préalables à l'application de l'algorithme

L'algorithme utilise un réseau routier et une trace GPS potentiellement bruités. Les calculs pour l'affectation des points GPS au segment de route se font en mètres.

#### Entrées de l'algorithme

1. Trace GPS en mètres
2. Réseau routier en mètres

La transformation en mètres se fait sous **QGIS** à partir de données exprimées en latitude et longitude et le référentiel le plus adapté à la localisation générale des données traitées (en attendant une méthode automatisée).

## Explication du fonctionnement d'un HMM

La page wikipedia est très bien faite (<https://en.wikipedia.org/wiki/Hidden_Markov_model>)

```Python
states = ('Rainy', 'Sunny')

observations = ('walk', 'shop', 'clean')

start_probability = {'Rainy': 0.6, 'Sunny': 0.4}

transition_probability = {
   'Rainy' : {'Rainy': 0.7, 'Sunny': 0.3},
   'Sunny' : {'Rainy': 0.4, 'Sunny': 0.6},
   }

emission_probability = {
   'Rainy' : {'walk': 0.1, 'shop': 0.4, 'clean': 0.5},
   'Sunny' : {'walk': 0.6, 'shop': 0.3, 'clean': 0.1},
   }
```
Dans cet exemple, on cherche à deviner le temps qu'il fait (`states`) durant chacune des `observations`, sachant qu’initialement il y a légèrement plus de chance que le temps soit à la pluie qu'au soleil (`start_probability`).

On connaît aussi les probabilités sur l'évolution du temps (par exemple, le temps à plus de chance de ne pas changer que de changer).

On sait aussi les probabilités d'observer telle action (`walk`, ...) selon le temps qu'il fait.

L’algorithme prend donc en entrées toutes ces informations et va produire pour le jeu d'observations  `('walk', 'shop', 'clean')`, la séquence de temps la plus probable.

Le processus présenté : <http://techeffigytutorials.blogspot.com/2015/01/markov-chains-explained.html>


Pour faciliter la lecture, les informations sont présentées selon le formalisme suivant :
- vocabulaire anglais en *italique*
- proposition d'implémentation en *quoted text*
- en `code` les noms proposés pour l'implémentation (*CamelCase* pour les classes, *camelCase* pour les variables de type int, long, etc...)

#### États (*Hidden States*)

Un état représente une situation, ici une route.

> Un réseau (`Network`) est composé d'un certain nombre de routes (`Road`).
>
>Chaque route est décrite par un nombre de points (`Point`) (au moins 2) qui sont ordonnés. Chaque couple de point est un segment (`Segment`) qui représente une portion de route.

> Les coordonnées sont en mètres.

#### Observations (*Observation*)

> Une trace GPS (`Track`) contient une liste de points (`Point`) comprenant un marquage horaire (`timeStamp`) et une altitude (`altitude`). L'altitude n'est à priori pas exploitée dans l'algorithme.  

#### Probabilité initiale (*Start probability*)

Probabilité initiale affectée à chaque état. La somme des probabilités = 1.0

> Dans notre cas, on prendra les segments dans un rayon de x m (donnés par la publi) autour du premier point GPS et on affecte les probabilités selon les distances. La route la plus proche aura la plus forte probabilité.

#### Probabilité de transition (*Transition probability*)

Pour chaque état, on affecte une probabilité de passer à un état suivant. S'il y a N états, on a alors N transitions pour chaque état (la somme est 1.0). Cela donne une matrice NxN (*Markov matrix*).

>Il faut pouvoir calculer les probabilités de transition entre routes. Une transition est possible quand deux segments partagent un point en commun (à priori, par forcément le premier ou le dernier - cas du branchement).  

>Il faut décider si l'on gère le sens de parcours (donnée présentent dans le jeu de test, mais pas forcément sur nos tests).

``` python
STAY_ON_ROAD= 0.5  # à décider, probabilité de rester sur la même route
foreach road r1:
  noOfTargets= 0 # nombre d'embranchements possibles à partir de r1
  targets= []
  foreach road r2:
    if r1.sharePoint(r2):
      ++no_of_targets # on compte r1
      targets.append(r2.id) if r2.id!=r1.id
  statRef= (1.0-STAY_ON_ROAD)/noOfTargets
  r1.set(statNextRoad= statRef, listOfNextRoads= targets)   
```
 > **Note**: Complexité NxNxlength(road). Optimisation possible ?

#### Probabilité d'émission (*Emission probability*)

Pour chaque couple(état,observation), on donne une probabilité, sachant que la somme des couples (état A, observation i) (i variant de 1 à M) vaut 1.0

> On utilisera dans un premier temps les probabilités initiales (uniquement calculées sur la distance). On pourra exploiter dans un second temps la vitesse de circulation et le type de route si ces données sont présentes.

```
DISTANCE_THRESHOLD= 300 # à vérifier avec la publi
foreach point p:
  foreach road r:
    distance= shortestDistance(p,r)
    if distance < DISTANCE_THRESHOLD
    ...  
```

## Estimation de la mémoire nécessaire

Calcul avec des données réalistes mais non réelles :
- Point : 2 long
- Route : 5 Point en moyenne
- Réseau : 2000 Route
- Trace GPS : 1000 Point + timestamp (long), + altitude (long) pour chaque
- Matrice de Markov : |Réseau x Réseau| # float
- Matrice des émissions : |Trace GPS|x|Réseau| # float

Résultat (sans surchage: classe, fonctions, variable (id), etc) :

```
double: 8 octets (64 bits)
float: 4 octets
```

- Réseau : `2000x5x2x8= 1600ko`
- Trace : `1000x4x8=32ko`
- Matrice de Markov : `2000x2000x4= 16Mo`
- Matrice des émissions : `1000x1000x4= 4Mo`
- Réseau de Markov : `5!x5x1000=600Mo`

## Description des classes

Proposition idéale qui optimise la mémoire (le diagramme de classe présente des structures de données optimisée en temps de calcul et plus simple à manipuler).

#### Point
- double x, y
- int id

#### Road
- int id
- vector`<int>` pointId
- float statRef
- vector`<int>`roadId # représente la Matrice de Markov

#### Network
- vector`<Road>` road
- Point rectLowerLeftBound, rectUpperRightBound # boite englobante

#### PointGPS
- double x,y,z
- long timeStamp
- int id
- vector`<Emission>` emissionProbability

#### Emission
- float probability
- int roadId

#### Track
- vector`<PointGPS>` point

### Structures utile pour l'algorithme

- vector`<vector<float>>` markovMatrix
- vector`<vector<float>>` emissionMatrix
