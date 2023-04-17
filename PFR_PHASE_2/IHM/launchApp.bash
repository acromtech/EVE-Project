#!/bin/bash
# Auteur : Alexis GIBERT
sudo apt install gcc
sudo apt install make
sudo apt install openjdk-19-jdk
sudo apt install openjfx
sudo apt install maven
mvn clean package
java --module-path /usr/share/openjfx/lib --add-modules javafx.controls,javafx.fxml -jar target/PFR2-1.0-SNAPSHOT-jar-with-dependencies.jar
