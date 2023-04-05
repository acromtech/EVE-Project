import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.*;

public class ControlRechercheComplexe {
    static File fileHisto = new File("historique.txt");
    String sauvegardeHisto;
    private static Queue<String> fifoHisto = new LinkedList<>();

    public ControlRechercheComplexe() {
    }

    private static void processBlock(List<String> block) {
        StringBuilder strBlock = new StringBuilder();
        for (String line : block) {
            strBlock.append(line).append("\n");
        }
        if (fifoHisto.size() > 15) {
            try {
                fifoHisto.remove();
            }catch (NoSuchElementException ignored){
            }


            fifoHisto.add(strBlock.toString());
        }else fifoHisto.add(strBlock.toString());
    }
    public Map<String, Double> rechercheComplexe(String recherche){
        return RechercheComplexe.getInstance().recherche(recherche);

    }

    public String getHistorique() {
        saveHisto();
        String histo = null;
        try {
            histo = Files.readString(Path.of("historique.txt"));
        } catch (IOException e) {
            System.err.println("Une erreur s'est produite lors de la lecture du fichier: " + e.getMessage());
        }
        return histo;
    }

    private void saveHisto() {

        try (FileWriter writer = new FileWriter(fileHisto)) {
            for(String s : fifoHisto) {
                writer.write(s);

            }
            writer.append(RechercheComplexe.getInstance().getHistorique());
        } catch (IOException e) {
            e.printStackTrace();
        }

        try (BufferedReader br = new BufferedReader(new FileReader("historique.txt"))) {
            List<String> block = new ArrayList<>();
            String line;
            int count = 0;
            while ((line = br.readLine()) != null) {
                block.add(line);
                count++;
                if (count == 4) {
                    processBlock(block);
                    block.clear();
                    count = 0;
                }
            }

            if (!block.isEmpty()) {
                processBlock(block);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        fifoHisto.clear();
    }
}

