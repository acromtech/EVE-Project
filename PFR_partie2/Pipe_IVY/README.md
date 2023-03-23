# Wrapper IVY V1
Ce wrapper permet de renvoyer les résultats obtenu par le programme C au controlleur JAVA.

**Pour lancer le programme de test ouvrez le répertoire CodeJAVA/src/testWrapperIvyPfr.java**
```
//PROGRAMME DE TEST

import java.util.List;

public class testWrapperIvyPfr{
    public static void main(String[] args) {
        
        //Déclaration du wrapper (Démarre directement la liaison JAVA-C)
        wrapperIvyPfr wrapper = new wrapperIvyPfr();

        //Déclaration d'une liste ScorePath et envoi de la requete pour un traitement via le moteur de recherche textuel "T"
        List<ScorePath> scoreRequete1=wrapper.sendRequete("T","mot");
        
        //Affiche le résultat de la requete
        for (ScorePath scorePath : scoreRequete1)
          System.out.println("JAVA\tScore : " + scorePath.getScore() + " - Path : " + scorePath.getPath());

        //Deconnection du bus
        wrapper.stopBus();
    }
}
```

## Fonctions utilisable
### En C
```
void startBus();
void sendAllResBus(IvyFrameBuffer descScore);
void stopBus();
```
### En JAVA
```
List<ScorePath> sendRequete(String type_traitement,String requete); //type de traitement = "T" : Texte / "I" : Image / "S" : Son
void stopBus();
```
> Notez que la connection au bus se fait directement dans le constructeur
> ```
> wrapperIvyPfr wrapper = new wrapperIvyPfr();
> ```

## Paramètres modifiables
Actuellement le fichier `wrapperPFR.h`dispose d'un paramètre réglable afin de renvoyer un nombre maximal de résulats (bien entendu si le nombre de résultats est inférieur ce paramètre ne sera pas pris en compte).
```
#define NBLISTE 10
```
## Version futures
Dans la prochaine version :
1. Le paramètre `NBLISTE` sera directement envoyé par le JAVA (puisque c'est le controlleur) afin de limiter les déclarations
2. Les trames seront structurés de manière à pouvoir aussi lancer l'indexation

