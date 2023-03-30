import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;

public class ControlRechercheComplexe {
    static File fileHisto = new File("src\\historique.txt");
    private Queue<String> fifoHisto = new LinkedList<>();
    String sauvegardeHisto;

    public ControlRechercheComplexe() {
    }

    public Map<String, Double> rechercheComplexe(String recherche) throws IOException {
        Map<String, Double> mapRes = RechercheComplexe.getInstance().recherche(recherche);
        saveHisto();
        return mapRes;

    }

    public String getHistorique() {
        String histo = null;
        try {
            histo = Files.readString(Path.of("src\\historique.txt"));
        } catch (IOException e) {
            System.err.println("Une erreur s'est produite lors de la lecture du fichier: " + e.getMessage());
        }
        return histo;
    }




    private void saveHisto() {

        try (BufferedReader br = new BufferedReader(new FileReader("src\\historique.txt"))) {
            String line;
            while ((line = br.readLine()) != null) {
                fifoHisto.add(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        fifoHisto.add(RechercheComplexe.getInstance().getHistorique());

        try (FileWriter writer = new FileWriter(fileHisto, true)) {
                writer.append(RechercheComplexe.getInstance().getHistorique());
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
