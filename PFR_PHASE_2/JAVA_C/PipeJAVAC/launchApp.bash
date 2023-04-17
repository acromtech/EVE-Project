#!/bin/bash
# Auteur : Alexis GIBERT

sudo apt install gcc
sudo apt install make
sudo apt install openjdk-19-jdk

# Compilation du code source
javac -cp "lib/*" -d bin src/Main.java

# Création du fichier manifeste
echo -e "Main-Class: Main\nClass-Path: lib/Bus.jar lib/ivy-java-1.2.18.jar" > manifest.txt

# Création du fichier JAR
jar cvfm Main.jar manifest.txt -C bin/ .

# Suppression du fichier manifeste
rm manifest.txt

# Déplacement du fichier JAR dans le répertoire courant
mv Main.jar .

# Donner les droits d'exécution au fichier JAR
chmod +x Main.jar

sudo java -jar Main.jar

