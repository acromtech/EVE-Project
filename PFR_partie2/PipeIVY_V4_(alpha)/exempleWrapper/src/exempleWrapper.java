import java.util.List;

public class exempleWrapper{
    public static void main(String[] args) {
        //Déclaration du wrapper (Démarre directement la liaison JAVA-C)
        wrapperIvyPfr wrapper = new wrapperIvyPfr();

        //Désactive les affichages du terminal
        wrapper.setAffConsole(false);

        //Instantie un nouveau moteur et le monte sur le bus (ATTENTION ID DIFFERENT DE 0 -> 0 = MASTER (JAVA))
        Motor motor1=new Motor(1,"main.out");   //1 étant l'id souhaité et "main.out" la cible du makefile
        Motor motor2=new Motor(2,"main.out");   //2 étant l'id souhaité et "main.out" la cible du makefile
        wrapper.addMotor(motor1);
        wrapper.addMotor(motor2);

        //Indexation de toute la base de données
        wrapper.launchIndexation(motor1,wrapperIvyPfr.ADDR_INDEXATION_ALL);

        //Déclaration d'une liste ScorePath et envoi de la requete pour un traitement via le moteur de recherche textuel
        List<ScorePath> scoreRequete1 = wrapper.sendRequete(motor1,wrapperIvyPfr.ADDR_TEXTE_MOTCLE,"mot",10);
        List<ScorePath> scoreRequete2 = wrapper.sendRequete(motor2,wrapperIvyPfr.ADDR_TEXTE_MOTCLE,"mot",10);

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
        wrapper.removeMotor(motor1);
        wrapper.removeMotor(motor2);

        //Déconnecte le JAVA (master) du bus
        wrapper.stopBus();
    }
}
