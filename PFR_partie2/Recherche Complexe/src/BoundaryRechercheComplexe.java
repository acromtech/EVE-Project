import java.io.IOException;
import java.util.Map;

public class BoundaryRechercheComplexe {
    private final ControlRechercheComplexe controlRechercheComplexe;
    private String recherche;
    String historique;
    private boolean modeOuvertFerme;    //1=ferme; 0=ouvert

    public BoundaryRechercheComplexe() {
        this.controlRechercheComplexe = new ControlRechercheComplexe();
    }

    public Map<String, Double> rechercheComplexe() throws IOException {
        System.out.println("entrez les mots clef de la recherche séparés par un espace : \r");
        recherche = Clavier.entrerClavierString();
        return controlRechercheComplexe.rechercheComplexe(recherche);
    }

    public void getHistorique() {
        historique = controlRechercheComplexe.getHistorique();
        System.out.printf(historique);
    }

    public void basculerModeOuvertFerme() {
        modeOuvertFerme = !modeOuvertFerme;
    }

}
