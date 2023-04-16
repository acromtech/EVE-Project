package Entite;

import java.io.*;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class BDconfig {
    private Map<String, String> configMap = new HashMap<String, String>();
    private String mdp;
    File pathmdp = new File("motdePasse/.mdp");

    private BDconfig() {
    }

    private static class BDconfigHolder {
        private static final BDconfig instance = new BDconfig();
    }

    public static BDconfig getInstance() {
        return BDconfigHolder.instance;
    }


    public String getParametre(String key,File path){
        readConfig(path);
        return configMap.get(key);
    }


    public void readConfig(File path) {
        try {
            BufferedReader bufferedReader = new BufferedReader(new FileReader(path));

            String line;
            while ((line = bufferedReader.readLine()) != null) {
                // Traitement de chaque ligne du fichier .config

                String[] subParts = line.split(" ");// On sépare la ligne en numeroLigne puis clé-valeur
                String numLigne = subParts[0];
                String key = subParts[1];
                String value = subParts[2];

                //String[] keyValue = line.split(" ");
                //System.out.println(key + " " + value);
                if(key.equals("motdePasse"))
                {
                    this.mdp=value;
                }else {
                    configMap.put(key, value); // On ajoute la clé et la valeur dans la Map
                }
                //System.out.println(line);
            }
            bufferedReader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
    public String getmdp(){
        readConfig(pathmdp);
        return this.mdp;
    }

    public void updateConfig(String key, String value, File path) {
        try {
            // Ouvre le fichier .config en mode lecture
            BufferedReader bufferedReader = new BufferedReader(new FileReader(path));

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
            BufferedWriter bufferedWriter = new BufferedWriter(new FileWriter(path));
            for (int i = 0; i < lines.size(); i++) {
                bufferedWriter.write(lines.get(i));
                bufferedWriter.newLine();
            }
            bufferedWriter.flush(); // Vide le tampon de sortie
            bufferedWriter.close();

            if(key=="motdePasse")
            {
                // Met à jour le mdp
                this.mdp=value;
            }
            else {
                // Met à jour la valeur de la clé dans la Map
                configMap.put(key, value);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

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




    public String toString() {
        return "Valeur " + configMap;
    }


}




