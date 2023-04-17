import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
/**
 * Auteur : Emilien VESIN
 */
public class BDconfig {
    private Map<String, String> configMap = new HashMap<String, String>();

    private BDconfig() {
    }

    private static class BDconfigHolder {
        private static final BDconfig instance = new BDconfig();
    }

    /**
     * Recupère l'instance
     * @return
     */
    public static BDconfig getInstance() {
        return BDconfigHolder.instance;
    }

    /**
     * Récupère un paramètre dans le .config
     * @param key
     * @return
     */
    public String getParametre(String key){
        return configMap.get(key);
    }
    public void readConfig(File path) {
        try {
            File configFile = path;
            BufferedReader bufferedReader = new BufferedReader(new FileReader(configFile));

            String line;
            while ((line = bufferedReader.readLine()) != null) {
                // Traitement de chaque ligne du fichier .config

                String[] subParts = line.split(" ");// On sépare la ligne en numeroLigne puis clé-valeur
                String numLigne = subParts[0];
                String key = subParts[1];
                String value = subParts[2];

                //String[] keyValue = line.split(" ");
                System.out.println(key + value);
                configMap.put(key, value); // On ajoute la clé et la valeur dans la Map

                //System.out.println(line);
            }
            bufferedReader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    /**
     * Met a jour UN paramètre du .config
     * @param key
     * @param value
     * @param path
     */
    public void updateConfig(String key, String value, File path) {
        try {
            // Ouvre le fichier .config en mode lecture
            File configFile = path;
            BufferedReader bufferedReader = new BufferedReader(new FileReader(configFile));

            // Lit chaque ligne du fichier .config et stocke les résultats dans une liste
            List<String> lines = new ArrayList<>();
            String line;
            while ((line = bufferedReader.readLine()) != null) {
                String[] subParts = line.split(" ");//ex : subParts[0]= 1 + subParts[1] = nbrLigne + subParts[2] = 8
                if (subParts[1].equals(key)) {
                    // Si la ligne correspond à la clé donnée, modifie sa valeur
                    line = subParts[0] + " " + key + " " + value;
                }
                lines.add(line);
            }
            bufferedReader.close();

            // Écrit les lignes modifiées dans le fichier .config
            BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(configFile));
            for (int i = 0; i < lines.size(); i++) {
                bufferedWriter.write(lines.get(i));
                bufferedWriter.newLine();
            }
            bufferedWriter.flush(); // Vide le tampon de sortie
            bufferedWriter.close();

            // Met à jour la valeur de la clé dans la Map
            configMap.put(key, value);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Met a jour PLUSIEURS paramètres du .config
     * @param updates
     * @param path
     */
    public void multiUpdateConfig(Map<String, String> updates, File path) {
        try {
            // Lit chaque ligne du fichier .config et stocke les résultats dans une liste
            File configFile = path;
            List<String> lines = new ArrayList<>();
            BufferedReader bufferedReader = new BufferedReader(new FileReader(configFile));
            String line;
            while ((line = bufferedReader.readLine()) != null) {
                String[] subParts = line.split(" ");
                for (Map.Entry<String, String> entry : updates.entrySet()) {
                    String key = entry.getKey();
                    String value = entry.getValue();
                    if (subParts[1].equals(key)) {
                        // Si la ligne correspond à la clé donnée, modifie sa valeur
                        line = subParts[0] + " " + key + " " + value;
                        // Met à jour la valeur de la clé dans la Map
                        configMap.put(key, value);
                    }
                }
                lines.add(line);
            }
            bufferedReader.close();

            // Écrit chaque ligne modifiée dans le fichier .config
            BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(configFile));
            for (String updatedLine : lines) {
                bufferedWriter.write(updatedLine);
                bufferedWriter.newLine();
            }
            bufferedWriter.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Affiche le contenu du .config
     */
    public String toString() {
        return "Valeur " + configMap;
    }


}




