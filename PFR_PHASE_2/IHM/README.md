# IHM
* **Vous pouvez utiliser le bash launchApp.bash pour lancer l'application sans echec (vérification / installation des dépendances) ou suivre les prérequis détaillés plus bas**
```
bash launchApp.bash
```
* **Vous pouvez également lancer le bash JavaToJar.bash pour regénérer le .jar du projet avec la commande suivante**
```
bash JavaToJar.bash
```

## Prérequis
**GCC**
```
sudo apt install gcc
```
**Make**
```
sudo apt install make
```
**jdk 19**
```
sudo apt install openjdk-19-jdk
```
**Javafx**
```
sudo apt install openjfx
```

**Maven**
```
sudo apt install maven
```

## Executable
**Pour lancer l'executable placez-vous dans le répertoire IHM et lancez la commande suivante**
```
java --module-path /usr/share/openjfx/lib --add-modules javafx.controls,javafx.fxml -jar target/PFR2-1.0-SNAPSHOT-jar-with-dependencies.jar
```

