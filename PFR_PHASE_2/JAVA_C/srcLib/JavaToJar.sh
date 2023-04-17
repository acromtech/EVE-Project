#!/bin/bash
# Auteur : Alexis GIBERT
javac -d bin -cp lib/ivy-java-1.2.18.jar src/*.java
jar cvf Bus.jar -C bin . -C lib ivy-java-1.2.18.jar

