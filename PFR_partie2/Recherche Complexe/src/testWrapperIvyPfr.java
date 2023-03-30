import java.util.List;

public class testWrapperIvyPfr {
    public static void main(String[] args) {

        //Déclaration du wrapper (Démarre directement la liaison JAVA-C)
        wrapperIvyPfr wrapper = new wrapperIvyPfr();

        //Déclaration d'une liste ScorePath et envoi de la requete pour un traitement via le moteur de recherche textuel "T"
        //type_traitement : TEXTE "T", IMAGE "I", SON "S"
        List<ScorePath> scoreRequete1 = wrapper.sendRequete("T", "Football americain");

        //Affiche le résultat de la requete
        for (ScorePath scorePath : scoreRequete1) {
            System.out.println("JAVA\tScore : " + scorePath.getScore() + " - Path : " + scorePath.getPath());
        }

        //Deconnection du bus
        wrapper.stopBus();
    }
}
