# Installation de TexMaker sous debian

``` bash
wget http://www.xm1math.net/texmaker/texmaker_debian_jessie_4.5_amd64.deb
sudo apt-get install libpoppler-qt4-4  
sudo dpkg -i texmaker_debian_jessie_4.5_amd64.deb 
sudo apt-get install texlive
sudo apt-get install texlive-science
sudo apt-get install texlive-latex-extra
sudo apt-get install texlive-lang-french
```

## Configuration

Options / configuration Texmaker :
+  Commandes : 
 +    Cocher : Utiliser un sous-répertoire "build" pour les fichiers de sortie
 +    Afficheur Pdf : 
   +      Cocher : intégré à la fenêtre
