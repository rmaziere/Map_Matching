# Tutoriel pour utiliser le framework Google Test

## Plugin Google Test C++ pour Qt Creator 
### Installer le plugin Google Test C++ pour Qt Creator : 

Ouvrir un terminal
Télécharger l'archive correspondant à la version de QtCreator, lien disponible sur https://sourceforge.net/projects/qtc-gtest/files/bin/
(pour QtCreator 4.0.* => télécharger QtcGtest-4.0.0 ):

```bash
	wget 'https://sourceforge.net/projects/qtc-gtest/files/bin/4.0.0/QtcGtest-4.0.0-linux-x64.tar.gz'
```


Se déplacer dans le dossier d'installation de QtCreator : 
```bash
	cd /opt/Qt5.7.0/Tools/QtCreator
```

Décompresser l'archive téléchargée dans ce dossier :
```bash
	sudo tar zxvf /home/roselia/Téléchargements/QtcGtest-4.0.0-linux-x64.tar.gz 
```


### Activer le plugin Google Test C++ dans QtCreator
	Ouvrir QtCreator
	Aller dans Aide --> À propos des plug-ins...
	Sélectionner le plugin C++ --> QtcGtest
	Fermer la fenêtre
	Fermer QtCreator
	Relancer QtCreator

## Librairie Google Test C++
### Installer la librairie : 
	cloner le dépôt Github
```bash
		git clone https://github.com/google/googletest.git
```

	aller dans le dossier du repository ainsi créé
```bash
		cd googletest
```

	puis aller dans le dossier googletest
```bash
		cd googletest
```

	creer un répertoire pour compiler : 
```bash
		mkdir build
```

	se rendre dans le répertoire
```bash
		cd build
```

	parametrer la compilation : 
```bash
		cmake ..
```

	compiler : 
```bash
		make
```

	installer la librairie : 
```bash
		sudo make install
```

### Utiliser la librairie dans QtCreator
	Avoir un projet déjà existant (contenant des .h)
	Créer un nouveau projet QtCreator (QtConsole application va très bien)
	Dans le .pro :
```cpp
		QT       += core gui

		CONFIG += c++11

		TEMPLATE = app

		LIBS += -lgtest

		INCLUDEPATH += <Chemin Relatif vers les sources du projet existant>

		SOURCES += main.cpp \
			<Chemin Relatif vers la classe à tester du projet existant>.cpp

		HEADERS += \
			<Chemin Relatif vers la classe à tester du projet existant>.h
```


	Dans le fichier main.cpp
```cpp
		#include "gtest/gtest.h"
		#include "<classe a tester>.h"

		TEST(<arborescence du test>) {
		    EXPECT_EQ (<sortie>, <Fonction de la classe à tester>(<argument>));
		}

		int main(int argc, char **argv) {
		  ::testing::InitGoogleTest(&argc, argv);
		  return RUN_ALL_TESTS();
		}
```


### Exemple : 
		Projet existant :
			square.cpp
```cpp
				#include "square.h"

				double square(double){
				    return 0.0;
				}
```

			square.h
```cpp
				#ifndef SQUARE_H
				#define SQUARE_H

				double square(double);

				#endif // SQUARE_H
```

		Nouveau projet :
			fichier .pro 
```cpp
				QT       += core gui

				CONFIG += c++11

				TEMPLATE = app

				LIBS += -lgtest

				INCLUDEPATH += ../fonctionSquare

				SOURCES += main.cpp \
				    ../fonctionSquare/square.cpp

				HEADERS += \
				    ../fonctionSquare/square.h
```

			main.cpp
```cpp
				#include "gtest/gtest.h"
				#include "square.h"


				TEST(SquareRootTest, PositiveNos) {
				    EXPECT_EQ (18.0, square(324.0));
				    EXPECT_EQ (25.4, square(645.16));
				    EXPECT_EQ (50.3321, square(2533.310224));
				}

				TEST (SquareRootTest, ZeroAndNegativeNos) {
				    ASSERT_EQ (0.0, square(0.0));
				    ASSERT_EQ (-1, square(-22.0));
				}

				int main(int argc, char **argv) {
				  ::testing::InitGoogleTest(&argc, argv);
				  return RUN_ALL_TESTS();
				}
```


## Utilisation 
ASSERT: Fails fast, aborting the current function.
EXPECT: Continues after the failure

### Les tests
#### Les chaines de caractères
```cpp
EXPECT_STREQ("jump", functionSingulier("jumps"));
```
#### Les booléens
```cpp
ASSERT_TRUE(fp = fopen(path, "r"));
```
#### Les floatants
```cpp
ASSERT_FLOAT_EQ (expected, actual)
ASSERT_DOUBLE_EQ (expected, actual) 
ASSERT_NEAR (expected, actual, absolute_range)
 
EXPECT_FLOAT_EQ (expected, actual)
EXPECT_DOUBLE_EQ (expected, actual) 
EXPECT_NEAR (expected, actual, absolute_range)
```

