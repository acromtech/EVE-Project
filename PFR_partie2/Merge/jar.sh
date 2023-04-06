#!/bin/bash
javac -d bin -cp lib/ivy-java-1.2.18.jar src/*.java

jar cvf wrapperIvyPfr.jar manifest.txt -C bin . -C lib ivy-java-1.2.18.jar
