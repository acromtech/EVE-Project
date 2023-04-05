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
