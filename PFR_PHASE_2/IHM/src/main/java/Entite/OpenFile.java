package Entite;

import java.io.*;

public class OpenFile {

        public static String openFile(String filename) {
            String result = "";
            try (BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(filename), "ISO-8859-1"))) {
                String line;
                while ((line = br.readLine()) != null) {
                    result = result + line + "\n";
                }
            } catch (IOException e) {
                System.err.println("Error reading file: " + e.getMessage());
            }
            return result;
        }
}



// Affiche la fenêtre principale
//
//    String result = "";
//        try (BufferedReader br = new BufferedReader(new FileReader(filename))) {
//        String line;
//        while ((line = br.readLine()) != null) {
//            result = result + line +"\n";
//        }
//    } catch (IOException e) {
//        System.err.println("Error reading file: " + e.getMessage());
//    }
//        return result;
//}