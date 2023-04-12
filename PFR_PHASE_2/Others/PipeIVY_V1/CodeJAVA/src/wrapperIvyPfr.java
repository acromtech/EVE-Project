import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;

import fr.dgac.ivy.*;

public class wrapperIvyPfr{
    //Attributs
    private Ivy bus;
    private int nombreScore;
    private boolean traitement_c_en_cours=false;
    private boolean cConnected=false;
    private List<ScorePath> scorePathList = new ArrayList<>();

    /**
     * Constructeur de la classe JAVA
     */
    wrapperIvyPfr(){
        bus = new Ivy("hoteJava", "B", null);

        //S'abonne aux différents messages
        try {
            subCConnected();
            subCDisconnected();
            subBeginNewTrame();
            subCReady();
            subScoreChemin();
            subEndTraitement();
        } catch (IvyException e) {
            e.printStackTrace();
        }

        new Thread(new Runnable() {
            public void run() {
                try {
                    ProcessBuilder pb = new ProcessBuilder("bash","c.sh");
                    pb.directory(new File(System.getProperty("user.dir"))); // Répertoire de travail
                    pb.redirectErrorStream(true);
                    Process p = pb.start();
                    BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
                    String line;
                    while ((line = reader.readLine()) != null) {
                        System.out.println(line);
                    }
                    p.waitFor();
                } catch (IOException | InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }).start();
        
        //Démarre la connection
        try {
            bus.start("127.255.255.255:2010");
        } catch (IvyException e) {
            e.printStackTrace();
        }

        //Attend que le code C soit connecté au bus
        synchronized (bus) {
            while(!cConnected){
                try {
                    bus.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }
    }
    
    //Méthodes
    /**
     * S'abonne aux messages "A" : L'hote C indique au JAVA qu'il est connecté 
     * @throws IvyException
     */
    private void subCConnected()throws IvyException{
        bus.bindMsg("^A",new IvyMessageListener(){
            public void receive(IvyClient client, String[] args){
                cConnected=true;
                synchronized (bus) {
                    bus.notify();
                }
            }
        });
    }
    /**
     * S'abonne aux messages "K" : L'hote C indique au JAVA qu'il est déconnecté 
     * @throws IvyException
     */
    private void subCDisconnected()throws IvyException{
        bus.bindMsg("^K",new IvyMessageListener(){
            public void receive(IvyClient client, String[] args){
                cConnected=false;
            }
        });
    }
    /**
     * S'abonne aux messages "D" : L'hote C prévient JAVA qu'il va lui envoyer n data
     * La Callback JAVA récupère la valeur correspondant au nombre de paquets qui va lui transmettre et réinitialise la liste
     * @throws IvyException
     */
    private void subBeginNewTrame()throws IvyException{
        bus.bindMsg("^D (.*)",new IvyMessageListener(){
            public void receive(IvyClient client, String[] args){
                nombreScore=Integer.parseInt(args[0]);
                System.out.println("JAVA\t"+nombreScore);
                scorePathList.clear();
            }
        });
    }
    /**
     * S'abonne aux messages "R" : L'hote C est prêt a envoyer les data
     * La Callback JAVA autorise l'envoi de la nouvelle trame de data
     * @throws IvyException
     */
    private void subCReady()throws IvyException{
        bus.bindMsg("^R",new IvyMessageListener(){
            public void receive(IvyClient client, String[] args){
                try {
                    bus.sendMsg("C");
                } catch (IvyException e) {
                    e.printStackTrace();
                }
            }
        });
    }
    /**
     * S'abonne au messages "X" et "P" : Trame contenant les scores et les chemins
     * La Callback JAVA sauvegarde les scores et les chemins dans une liste
     * @throws IvyException
     */
    private void subScoreChemin()throws IvyException{
        bus.bindMsg("^X (.*) P (.*)",new IvyMessageListener(){
            public void receive(IvyClient client, String[] args){
                scorePathList.add(new ScorePath(Integer.parseInt(args[0]), args[1]));
            }
        });
    }
    /**
     * S'abonne aux messages "F" : Trame indiquant la fin du traitement du C
     * @throws IvyException
     */
    private void subEndTraitement() throws IvyException{
        bus.bindMsg("^F",new IvyMessageListener(){
            public void receive(IvyClient client, String[] args){
                traitement_c_en_cours=false;
                synchronized (bus) {
                    bus.notify();
                }
            }
        });
    }
    /**
     * SendRequete permet d'envoyer la requete sur un moteur de recherche donné au C 
     * @param type_traitement T:TEXTE, I:IMAGE, S:SON
     * @param requete la chaine de caractère à envoyer au C
     */
    public List<ScorePath> sendRequete(String type_traitement,String requete){
        if(cConnected){
            try {
                bus.sendMsg(type_traitement+" "+requete);
            } catch (IvyException e) {
                e.printStackTrace();
            }
            traitement_c_en_cours=true;
            synchronized (bus) {
                while(traitement_c_en_cours){
                    try {
                        bus.wait();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        }
        else System.out.println("JAVA\tErreur : Impossible d'envoyer la requete car l'hote C est déconnecté");
        return scorePathList;
    }

    public void stopBus(){
        bus.stop();
    }
}