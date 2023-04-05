import java.util.List;
import java.util.Map;

public class Main{
    public static void main(String[] args) {
        //Attributs
        //int dureeAudioCorpus;

        //Déclaration du wrapper (Démarre directement la liaison JAVA-C)
        Bus bus = new Bus();

        //Désactive les affichages du terminal
        bus.setAffConsole(true);

        //Instantie un nouveau moteur et le monte sur le bus (ATTENTION ID DIFFERENT DE 0 -> 0 = MASTER (JAVA))
        Motor motor1=new Motor(1,"main.out",".config1");   //1 étant l'id souhaité et "main.out" la cible du makefile
        Motor motor2=new Motor(2,"main.out",".config2");   //2 étant l'id souhaité et "main.out" la cible du makefile
        bus.addMotor(motor1);
        bus.addMotor(motor2);
/*
        //Récupère un paramètre de configurations du moteur1
        dureeAudioCorpus = motor1.getDureeAudioCorpus();
        System.out.println("JAVA\tdureeAudioCorpus : "+dureeAudioCorpus);

        //Set le paramètre du moteur1
        motor1.setDureeAudioCorpus(60);

        //Récupère le paramètre de configurations du moteur1 pour vérifier qu'il a bien été mis a jour
        dureeAudioCorpus = motor1.getDureeAudioCorpus();
        System.out.println("JAVA\tdureeAudioCorpus : "+dureeAudioCorpus);
*/
        //Indexe toute la base de données
        bus.launchIndexation(motor1,Bus.ADDR_INDEXATION_ALL);

        //Déclare et envoi le MOT pour un traitement via UN MOTEUR pour une recherche texte par mot clé
        List<ScorePath> scoreRequete1=bus.sendWord(motor1,Bus.ADDR_TEXTE_MOTCLE,"mot",10);
        Tools.printScorePathList(scoreRequete1);
        List<ScorePath> scoreRequete2=bus.sendWord(motor2,Bus.ADDR_TEXTE_MOTCLE,"mot",3);
        Tools.printScorePathList(scoreRequete2);

        //(TEST)Traitement dans une boucle for
        /*
        List<ScorePath> scoreRequete3 = new ArrayList<>();
        for(int i=0;i<10;i++){
            scoreRequete3=bus.sendWord(motor1,Bus.ADDR_TEXTE_MOTCLE,"mot",4);
            Tools.printScorePathList(scoreRequete3);
        }
        */

        //Déclare et envoi la requete COMPLEXE pour un traitement texte par mot clé
        Map<String,Double> scoreRequete4=bus.sendRechercheComplexe(motor2,Bus.ADDR_TEXTE_MOTCLE, "+mot1 -mot2 -mot3",10);
        Tools.printStringDoubleMap(scoreRequete4);

        //Déconnecte le moteur du bus
        bus.removeMotor(motor1);
        bus.removeMotor(motor2);

        //Déconnecte le JAVA (master) du bus
        bus.stopBus();
    }
}