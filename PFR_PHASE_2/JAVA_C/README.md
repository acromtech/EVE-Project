# Pipe IVY
Ce pipe permet de renvoyer les résultats obtenu par le programme C au controlleur JAVA.

**Pour lancer le programme de test déplacez-vous dans le répertoire PipeJava et lancer la commande suivante : `sudo java -jar Main.jar`**

```
//PROGRAMME DE TEST
public class Main{
    public static void main(String[] args) {
        //Déclaration du Bus (Démarre directement la liaison JAVA-C)
        Bus bus = new Bus("127.255.255.255:2010");

        //Désactive les affichages du terminal
        bus.setAffConsole(false);

        //Instantie un nouveau moteur et le monte sur le bus (ATTENTION ID DIFFERENT DE 0 -> 0 = MASTER (JAVA))
        Motor motor1=new Motor(1,"/Moteur1/CodeC/","main",".config1");   //1 étant l'id souhaité, "main" la cible du makefile et .config le fichier de configuration associé au moteur
        Motor motor3=new Motor(3,"/Moteur3/CodeC/","main",".config3");    //2 étant l'id souhaité, "main" la cible du makefile et .config le fichier de configuration associé au moteur
        bus.addMotor(motor1);
        bus.addMotor(motor3);
        
        //Lance l'OpenMode
        ThreadOuvertFerme threadOuvertFerme = new ThreadOuvertFerme("texte", "BaseFichier/Texte", true, motor3, bus);
        threadOuvertFerme.start();
        
        //Indexe toute la base de données
        threadOuvertFerme.pauseThread();
        bus.launchIndexation(motor1,Bus.ADDR_INDEXATION_ALL);
        bus.launchIndexation(motor3,Bus.ADDR_INDEXATION_ALL);
        threadOuvertFerme.resumeThread();
        
        //Lance une requete SIMPLE sur le motor1 pour un traitement TEXTE_MOTCLE et retourne une liste contenant les 10 meilleurs résultats puis les affiches
        threadOuvertFerme.pauseThread();
        Tools.printScorePathList(bus.sendRequest(motor1,Bus.ADDR_TEXTE_MOTCLE, "mot",10));  //n'existe pas dans la base de donnée -> pas de résultats
        threadOuvertFerme.resumeThread();
        
        //Lance une requete COMPLEXE sur le motor3 pour un traitement TEXTE_MOTCLE et retourne une liste contenant les 10 meilleurs résultats puis les affiches
        threadOuvertFerme.pauseThread();
        Tools.printScorePathList(bus.sendRequest(motor3,Bus.ADDR_TEXTE_MOTCLE, "-stockage +grippe",10));
        threadOuvertFerme.resumeThread();

        //Lance une requete SIMPLE sur le motor1 pour un traitement TEXTE_MOTCLE et retourne une liste contenant les 10 meilleurs résultats puis les affiches
        threadOuvertFerme.pauseThread();
        Tools.printScorePathList(bus.sendRequest(motor1,Bus.ADDR_TEXTE_MOTCLE, "stockage",10));
        threadOuvertFerme.resumeThread();
        
        //Lance une requete SIMPLE sur le motor3 pour un traitement IMAGE_MOTCLE et retourne une liste contenant les 10 meilleurs résultats puis les affiches
        threadOuvertFerme.pauseThread();
        Tools.printScorePathList(bus.sendRequest(motor3,Bus.ADDR_IMAGE_MOTCLE,"violet",10));
        threadOuvertFerme.resumeThread();

        //Lance une requete COMPLEXE sur le motor3 pour un traitement IMAGE_MOTCLE et retourne une liste contenant les 10 meilleurs résultats puis les affiches
        threadOuvertFerme.pauseThread();
        Tools.printScorePathList(bus.sendRequest(motor3,Bus.ADDR_IMAGE_MOTCLE,"+orange -kaki",10));
        threadOuvertFerme.resumeThread();

        //Déconnecte les moteurs du bus
        threadOuvertFerme.pauseThread();
        bus.removeMotor(motor1);
        bus.removeMotor(motor3);
        threadOuvertFerme.resumeThread();
        
        //Déconnecte le JAVA (master) du bus
        bus.stopBus();
    }
}
```

## Les adresses des trames (Communication C-JAVA)
```
CONNECTED                                   0x01 
INDEXATION_TEXTEIVY                         0x10    //(TX_FRAME) Demande l'indexation des données textuelles (+ ACK)
INDEXATION_IMAGEIVY                         0x11    //(TX_FRAME) Demande l'indexation des données photographique (+ ACK)
INDEXATION_SONIVY                           0x12    //(TX_FRAME) Demande l'indexation des données sonores (+ ACK)
INDEXATION_ALL                              0x13    //(TX_FRAME) Demande l'indexation de toutes les données (+ ACK)
TEXTE_MOTCLE                                0x20    //(TX_FRAME) Demande de réaliser une recherche textuelle par mot clé (+ ACK)
TEXTE_FICHIER                               0x21    //(TX_FRAME) Demande de réaliser une recherche textuelle par fichier (+ ACK)
IMAGE_MOTCLE                                0x30    //(TX_FRAME) Demande de réaliser une recherche photographique par mot clé (+ ACK)
IMAGE_FICHIER                               0x31    //(TX_FRAME) Demande de réaliser une recherche photographique par fichier (+ ACK) 
SON_FICHIER                                 0x40    //(TX_FRAME) Demande de réaliser une recherche sonore par fichier (+ ACK)
SCORE_CHEMIN                                0x50    //(RX_FRAME) Récupère les données de résulats
STOP_BUS                                    0x60    //(TX_FRAME) Ordonne l'arret de la connection au bus virtuel (+ ACK)
ADDR_OPEN_MODE                              0x70    //(TX_FRAME) Demande l'ouverture ou non de l'indexation (+ ACK)
SUPPRIMER_DESCRIPTEUR                       0x23    //(TX_FRAME) SUPPRESSION descripteur (+ ACK)
```

## Méthodes utilisables
### En JAVA
#### Méthodes liées au bus virtuel
```
Bus(String port)                                                //Constructeur JAVA (lance le bus virtuel sur le port spécifié)
void addMotor(Motor motor)                                      //Ajoute un moteur sur le bus virtuel
void removeMotor(Motor motor)                                   //Retire un moteur sur le bus virtuel
void launchIndexation(Motor motor,final int addrTypeTraitement) //Démarre un processus d'indexation spécidique
List<ScorePath> sendWord(Motor motor, final int addrTypeTraitement,String requete,int nombreResultatMax) //Envoie un mot au moteur C
List<ScorePath> sendRechercheComplexe(Motor motor, int typeTraitement, String recherche, int nbResultMax) //lance une recherche complexe (plusieurs mots) sur le moteur de recherche C
void stopBus()                                                  //Se déconnecte du bus virtuel
void setAffConsole(boolean affConsole)                          //Active ou désactive les affichages console
boolean getAffConsole()                                         //Donne l'état de l'affichage console
boolean getOpenMode(Motor motor)                                //Donne l'état de l'OpenMode
void setOpenMode(Motor motor, boolean openMode)                 //Met a jour l'état de l'OpenMode
```

#### Méthodes liées a l'OpenMode (Thread)
```
ThreadOuvertFerme(String name, String path, boolean condition, Motor motor, Bus bus) //Constructeur du thread de l'OpenMode
void arret()            //Arrete le thread de l'OpenMode
void pauseThread()      //Met en pause le thread de l'OpenMode
void resumeThread()     //Relance le thread de l'OpenMode
```

#### Méthode de la classe Tools
```
String DateDuJour()                                         //Donne la date du jour au format : year + "-" + month + "-" + day + " " + hour + ":" + minute
printScorePathList(List<ScorePath> ScorePathList)           //Affiche le contenu de la Liste de ScorePath
```

#### Méthode liées au moteur
```
Motor(int id, String pathMakefile, String makeTarget, String configPath) //Constructeur d'un moteur
```
*Le moteur dispose de tout un tas de setteur et de getteurs pour mettre a jour les données critiques et les paramètres de configuration d'un moteur*

### En C
#### Les variables globales
```
extern int autorisation_envoie_trame;
extern char typeTraitement;     //Adresse du traitement en cours
extern char* requete;           //Requete en cours de traitement
extern char masterId;           //ID du controlleur JAVA (envoyé au lancement du programme C)
extern char motorId;            //ID du moteur C (Défini par l'utilisateur lors de l'instanciation JAVA et mis a jour au lancement du programme)
```

#### Les fonctions
```
void startBus(char*);
void traitementEffectue();
void attenteRequete();
void sendAllResBus(ResListToSend* resListToSend);
void stopBus();
```

*Alexis GIBERT*
