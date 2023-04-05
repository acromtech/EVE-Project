import java.io.*;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.*;

public class Historique {
    public String sauvegardeHisto;
    private String pathHisto;
    private File fileHisto;
    private static Queue<String> fifoHisto = new LinkedList<>();

    /**
     * Constructeur Historique récupère le chemin du fichier contenant l'historique
     * @param pathHisto
     */
    public Historique(String pathHisto) {
        this.fileHisto = new File(pathHisto);
    }

    /**
     * Récupère l'historique dans un String
     * @return
     * @throws IOException
     */
    public String getHistorique() throws IOException { // System.err.println("Une erreur s'est produite lors de la lecture du fichier: " + e.getMessage());
        saveHisto();
        String histo = null;
        histo = Files.readString(Path.of(pathHisto));
        return histo;
    }
    
    /**
     * Met a jour le chemin du fichier contenant l'historique
     * @param pathHisto
     */
    public void setPathHisto(String pathHisto){
        this.pathHisto=pathHisto;
    }

    /**
     * Retourne le chemin du fichier contenant l'historique
     * @return
     */
    public String getPathHisto(){
        return pathHisto;
    }


    /**
     * Sauvegarde l'historique
     * @throws IOException
     */
    private void saveHisto() throws IOException, NoSuchElementException{ //historique.txt
        try (FileWriter writer = new FileWriter(fileHisto)) {
            for(String s : fifoHisto) {
                writer.write(s);
            }
            writer.append(getHistorique());
        }
        try (BufferedReader br = new BufferedReader(new FileReader(pathHisto))) {
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
        }
        fifoHisto.clear();
    }

    /**
     * 
     * @param block
     * @throws NoSuchElementException
     */
    private static void processBlock(List<String> block) throws NoSuchElementException {
        StringBuilder strBlock = new StringBuilder();
        for (String line : block) {
            strBlock.append(line).append("\n");
        }
        if (fifoHisto.size() > 15) {
            fifoHisto.remove();
            fifoHisto.add(strBlock.toString());
        }else fifoHisto.add(strBlock.toString());
    }
}

