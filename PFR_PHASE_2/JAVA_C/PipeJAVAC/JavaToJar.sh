#!/bin/bash
javac -d bin -cp lib/ivy-java-1.2.18.jar -cp lib/wrapperIvyPfr.jar src/RechercheComplexe.java
javac -d bin -cp lib/ivy-java-1.2.18.jar -cp lib/wrapperIvyPfr.jar src/Historique.java
jar cvf rechercheComplexe.jar -C bin . -C lib ivy-java-1.2.18.jar -C lib wrapperIvyPfr.jar
