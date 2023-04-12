package com.example.pfr2;


import java.io.File;
import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) {

        BDconfig bdconfig = BDconfig.getInstance();
        File pathConfigMoteur1 = new File("PFR_partie1/Configuration/.config");
        File pathmdp = new File("motdePasse/.mdp");

        System.out.println("Hello world!");
        bdconfig.readConfig(pathConfigMoteur1);
        System.out.println(bdconfig.toString());
        System.out.println("Pas encore modifié\n");


        System.out.println("\nModification seuil et dureeAudioCorpus");
        Map<String, String> updates = new HashMap<>();
        updates.put("seuil", "89"); //De base 89
        updates.put("dureeAudioCorpus", "70");// De base 70
        bdconfig.multiUpdateConfig(updates, pathConfigMoteur1);


        System.out.println(bdconfig.toString());
        System.out.println("\nAncien mdp :" + bdconfig.getmdp());

        bdconfig.updateConfig("motdePasse","1234",pathmdp);
        System.out.println("\nNouveau mdp :" + bdconfig.getmdp());
        System.out.println(bdconfig.getParametre("dureeAudioCorpus", pathConfigMoteur1));

    }
}