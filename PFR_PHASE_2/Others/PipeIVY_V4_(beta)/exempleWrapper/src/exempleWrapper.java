import java.util.List;

public class exempleWrapper{
    public static void main(String[] args) {
        //Attributs
        //int dureeAudioCorpus;

        //Déclaration du wrapper (Démarre directement la liaison JAVA-C)
        wrapperIvyPfr bus = new wrapperIvyPfr();

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
        bus.launchIndexation(motor1,wrapperIvyPfr.ADDR_INDEXATION_ALL);

        //Déclare une liste ScorePath et envoi de la requete pour un traitement via le moteur de recherche textuel
        List<ScorePath> scoreRequete1 = bus.sendRequete(motor1,wrapperIvyPfr.ADDR_TEXTE_MOTCLE,"mot",10);
        List<ScorePath> scoreRequete2 = bus.sendRequete(motor2,wrapperIvyPfr.ADDR_TEXTE_MOTCLE,"mot",10);

        //Affiche le résultat de la requete
        System.out.println("\nscoreRequete1");
        for (ScorePath scorePath1 : scoreRequete1) {
            System.out.println("JAVA\tScore : " + scorePath1.getScore() + " - Path : " + scorePath1.getPath());
        }
        System.out.println("\nscoreRequete2");
        for (ScorePath scorePath2 : scoreRequete2) {
            System.out.println("JAVA\tScore : " + scorePath2.getScore() + " - Path : " + scorePath2.getPath());
        }

        //Déconnecte le moteur du bus
        bus.removeMotor(motor1);
        bus.removeMotor(motor2);

        //Déconnecte le JAVA (master) du bus
        bus.stopBus();
    }
}
