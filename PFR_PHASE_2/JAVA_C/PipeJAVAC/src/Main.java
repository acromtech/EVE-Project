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
