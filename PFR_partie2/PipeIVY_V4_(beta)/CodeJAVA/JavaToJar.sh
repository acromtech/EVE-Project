#!/bin/bash
javac -d bin -cp lib/ivy-java-1.2.18.jar src/ScorePath.java
javac -d bin -cp lib/ivy-java-1.2.18.jar src/BDconfig.java
javac -d bin -cp lib/ivy-java-1.2.18.jar:bin src/Motor.java
javac -d bin -cp lib/ivy-java-1.2.18.jar:bin src/wrapperIvyPfr.java
jar cvf wrapperIvyPfr.jar -C bin . -C lib ivy-java-1.2.18.jar
mv wrapperIvyPfr.jar ~/PFR_IVY/exempleWrapper/lib
