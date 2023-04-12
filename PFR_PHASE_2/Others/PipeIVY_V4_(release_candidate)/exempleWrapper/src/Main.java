import java.io.IOException;
import java.util.Map;

public class Main {
    public static void main(String[] args) throws IOException {
        while (true) {
            BoundaryRechercheComplexe boundaryRechercheComplexe = new BoundaryRechercheComplexe();
            Map<String, Double> resultats = boundaryRechercheComplexe.rechercheComplexe();
            System.out.println(resultats.toString());
            boundaryRechercheComplexe.getHistorique();

        }
    }
}