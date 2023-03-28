# Wrapper IVY V2
Ce wrapper permet de renvoyer les résultats obtenu par le programme C au controlleur JAVA.
**Un .jar sera disponible sous peu**

**Pour lancer le programme de test ouvrez le répertoire CodeJAVA/src/testWrapperIvyPfr.java**

```
//PROGRAMME DE TEST

import java.util.List;

public class testWrapperIvyPfr{
    public static void main(String[] args) {
        //Déclaration du wrapper (Démarre directement la liaison JAVA-C)
        wrapperIvyPfr wrapper = new wrapperIvyPfr();

        //Désactive les affichages du terminal
        wrapper.affConsole=false;

        //Indexation de toute la base de données
        wrapper.launchIndexation(Address.INDEXATION_ALL);

        //Déclaration d'une liste ScorePath et envoi de la requete pour un traitement via le moteur de recherche textuel
        List<ScorePath> scoreRequete1=wrapper.sendRequete(Address.TEXTE_MOTCLE,"mot",10);
        
        //Affiche le résultat de la requete
        for (ScorePath scorePath : scoreRequete1) {
            System.out.println("JAVA\tScore : " + scorePath.getScore() + " - Path : " + scorePath.getPath());
        }

        //Deconnection du bus
        wrapper.stopBus();
    }
}

```

A titre d'exemple (tous les cas ne sont pas présents), la forme du programme main.c sera la suivante
```
#include <stdlib.h>
#include <stdio.h>
#include "unistd.h"
#include "wrapperPFR.h"

#define ATTENTE_REQUETE 	0x01
#define TRAITEMENT 		0x02
#define ENVOI_RESULTATS 	0x03

int main(int argc, char**argv){
	ResListToSend resListToSend;
	char etat=ATTENTE_REQUETE;
	int boucle=1;
	
	startBus();

	while(boucle){
		switch(etat){
		case ATTENTE_REQUETE:
			sleep(1);
			if(typeTraitement!=-1) etat=TRAITEMENT;
			break;

		case TRAITEMENT:
			switch (typeTraitement){
			case INDEXATION_ALL:
				//appel de la fonction d'indexation
				traitementEffectue();
				break;
			case TEXTE_MOTCLE:
				//appel de la fonction de texte
				resListToSend=filList();
				traitementEffectue();
				break;
			case IMAGE_FICHIER:
				//appel de la fonction image
				resListToSend=filList();
				traitementEffectue();
				break;
			case SON_FICHIER:
				//appel de la fonction son
				resListToSend=filList();
				traitementEffectue();
				break;
			case SCORE_CHEMIN:
				sendAllResBus(resListToSend);
				traitementEffectue();
				break;
			case STOP_BUS:
				stopBus();
				return 0;
			default:
				printf("\nC\tErreur : Traitement non effectué %x",typeTraitement);
				return 0;
			}
			etat=ATTENTE_REQUETE;
			break;

		default:
			printf("\nC\tErreur : Résultats non envoyés");
			return 0;
		}
	}
	return 0;
}

```

## Fonctions / Variables utilisable
### En C
```
extern int autorisation_envoie_trame;
extern char typeTraitement;
extern char* requete;

void startBus();
void traitementEffectue();
void sendAllResBus(ResListToSend resListToSend);
void stopBus();
```
### En JAVA
```
public boolean affConsole=false;       //Active ou désactive les affichage console (initialisé a false)
public boolean acquitement=true;       //Active ou désactive les aquitements (initialisé a true)

public void launchIndexation(Address typeTraitement)
public List<ScorePath> sendRequete(Address typeTraitement,String requete,int nombreResultatMax)
public void stopBus();
```
> Notez que la connection au bus se fait directement dans le constructeur
> ```
> wrapperIvyPfr wrapper = new wrapperIvyPfr();
> ```
