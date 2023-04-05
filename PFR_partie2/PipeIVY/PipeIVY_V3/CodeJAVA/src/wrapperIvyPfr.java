import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import fr.dgac.ivy.Ivy;
import fr.dgac.ivy.IvyClient;
import fr.dgac.ivy.IvyException;
import fr.dgac.ivy.IvyMessageListener;

public class wrapperIvyPfr{

    //Identifiants
    public static final int JAVA_ID                  = 0x01;     //Identifiant JAVA
    public static final int C_ID                     = 0x02;     //Identifiant C

    //Types de trame
    private static final int ADDR_TX_FRAME           = 0x10;     //Signale qu'il s'agit d'une trame TX
    private static final int ADDR_RX_FRAME           = 0x20;     //Signale qu'il s'agit d'une trame RX

    //Adresses
    public static final int ADDR_CONNECTED           = 0x01;
    public static final int ADDR_INDEXATION_TEXTE    = 0x10;     //(TX_FRAME) Demande l'indexation des données textuelles (+ ACK)
    public static final int ADDR_INDEXATION_IMAGE    = 0x11;     //(TX_FRAME) Demande l'indexation des données photographique (+ ACK)
    public static final int ADDR_INDEXATION_SON      = 0x12;     //(TX_FRAME) Demande l'indexation des données sonores (+ ACK)
    public static final int ADDR_INDEXATION_ALL      = 0x13;     //(TX_FRAME) Demande l'indexation de toutes les données (+ ACK)
    public static final int ADDR_TEXTE_MOTCLE        = 0x20;     //(TX_FRAME) Demande de réaliser une recherche textuelle par mot clé (+ ACK)
    public static final int ADDR_TEXTE_FICHIER       = 0x21;     //(TX_FRAME) Demande de réaliser une recherche textuelle par fichier (+ ACK)
    public static final int ADDR_IMAGE_MOTCLE        = 0x30;     //(TX_FRAME) Demande de réaliser une recherche photographique par mot clé (+ ACK)
    public static final int ADDR_IMAGE_FICHIER       = 0x31;     //(TX_FRAME) Demande de réaliser une recherche photographique par fichier (+ ACK) 
    public static final int ADDR_SON_FICHIER         = 0x40;     //(TX_FRAME) Demande de réaliser une recherche sonore par fichier (+ ACK)
    public static final int ADDR_SCORE_CHEMIN        = 0x50;     //(RX_FRAME) Récupère les données de résulats (+ ACK)
    public static final int ADDR_STOP_BUS            = 0x60;     //(TX_FRAME) Ordonne l'arret de la connection au bus virtuel (+ ACK)

    //Attributs
    private Ivy bus;
    public boolean affConsole=false;       //Active ou désactive les affichage console
    private boolean cConnected=false;
    private boolean ack=false;
    private boolean traitement_c_en_cours=false;
    private List<ScorePath> scorePaths = new ArrayList<>();

    //Constructeur
    public wrapperIvyPfr(){
        bus = new Ivy(""+JAVA_ID,"",null);
        try{
            subACK();                       //S'abonne aux différents messages d'aquitements
            subRXFrame();                   //S'abonne aux différents messages RX
            new Thread(new Runnable() {     //Exécute le script bash
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
            bus.start("127.255.255.255:2010");                          //Démarre la connection
            if(affConsole) System.out.println("JAVA\tAttente de la réponse du C");
            synchronized (bus) { while(!cConnected) bus.wait(); }      //Attend que le code C soit connecté au bus
            if(affConsole) System.out.println("JAVA\tInitialisation de la communication effectuée avec succès");
        }catch (IvyException | InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void subACK() throws IvyException{
        bus.bindMsg("^"+JAVA_ID+" "+ADDR_TX_FRAME+" (.*) (.*)",new IvyMessageListener(){
            public void receive(IvyClient client, String[] args){
                if(Integer.parseInt(args[1])==0){
                    ack=true;
                    synchronized (bus) { bus.notify(); }
                }
                else if(Integer.parseInt(args[1])==1){
                    traitement_c_en_cours=false;
                    synchronized (bus) { bus.notify(); }
                }
                else System.out.println("JAVA\tErreur : La valeur transmise est incorrecte");
            }
        });
    }
    
    private void subRXFrame() throws IvyException{
        bus.bindMsg("^"+JAVA_ID+" "+ADDR_RX_FRAME+" (.*) (.*) (.*)",new IvyMessageListener(){
            public void receive(IvyClient client, String[] args){
                if(Integer.parseInt(args[0])==ADDR_SCORE_CHEMIN) {
                    if(Integer.parseInt(args[1])!=0xFF){
                        scorePaths.add(new ScorePath(Integer.parseInt(args[1]), args[2]));
                        try {
                            bus.sendMsg(C_ID+" "+ADDR_RX_FRAME+" "+ADDR_SCORE_CHEMIN);
                        } catch (IvyException e) {
                            e.printStackTrace();
                        }
                    } else traitement_c_en_cours=false;
                } else if(Integer.parseInt(args[0])==ADDR_CONNECTED){
                    cConnected=true;
                    synchronized (bus) { bus.notify(); }
                } else System.out.println("JAVA\tErreur : Adresse de la trame RX inconnue");
            }
        });
    }

    public void launchIndexation(final int addrTypeTraitement){
        if(addrTypeTraitement==ADDR_INDEXATION_ALL 
        ||addrTypeTraitement==ADDR_INDEXATION_TEXTE
        ||addrTypeTraitement==ADDR_INDEXATION_IMAGE
        ||addrTypeTraitement==ADDR_INDEXATION_SON){
            if(cConnected){
                try{
                    bus.sendMsg(C_ID+" "+ADDR_TX_FRAME+" "+addrTypeTraitement+" "+0+" "+0);
                    ack=false;
                    synchronized (bus) { while(!ack) bus.wait(); }
                    if(affConsole) System.out.println("JAVA\tACK");
                    traitement_c_en_cours=true;
                    synchronized (bus) { while(traitement_c_en_cours) bus.wait(); }
                    if(affConsole) System.out.println("JAVA\tIndexation terminée avec succès");
                } catch (IvyException | InterruptedException e) {
                    e.printStackTrace();
                }
            } else System.out.println("JAVA\tErreur : Impossible d'envoyer la requete car l'hote C est déconnecté");
        } else System.out.println("JAVA\tErreur : Le traitement que vous tenter de lancer n'est pas un traitement d'indexation");
    }
    
    /**
     * SendRequete permet d'envoyer le mot sur un moteur de recherche donné au C et récupérer les résultats dans une liste
     * @param typeTraitement
     * @param mot
     */
    public List<ScorePath> sendRequete(final int addrTypeTraitement,String requete,int nombreResultatMax){
        scorePaths.clear();
        if(addrTypeTraitement==ADDR_TEXTE_FICHIER 
        ||addrTypeTraitement==ADDR_TEXTE_MOTCLE
        ||addrTypeTraitement==ADDR_IMAGE_FICHIER
        ||addrTypeTraitement==ADDR_IMAGE_MOTCLE
        ||addrTypeTraitement==ADDR_SON_FICHIER){
            if(cConnected){
                try {
                    if(affConsole) System.out.println("JAVA\tTraitement "+addrTypeTraitement);
                    bus.sendMsg(C_ID+" "+ADDR_TX_FRAME+" "+addrTypeTraitement+" "+requete+" "+nombreResultatMax);
                    
                    ack=false;
                    synchronized (bus) { while(!ack) bus.wait(); }
                    if(affConsole) System.out.println("JAVA\tACK");
                    traitement_c_en_cours=true;
                    synchronized (bus) { while(traitement_c_en_cours) bus.wait(); }
                    if(affConsole) System.out.println("JAVA\tTraitement effectué");

                    bus.sendMsg(C_ID+" "+ADDR_RX_FRAME+" "+ADDR_SCORE_CHEMIN);

                    ack=false;
                    synchronized (bus) { while(!ack) bus.wait(); }
                    if(affConsole) System.out.println("JAVA\tACK");
                    traitement_c_en_cours=true;
                    synchronized (bus) { while(traitement_c_en_cours) bus.wait(); }
                    if(affConsole) System.out.println("JAVA\tDonnées récupérées");

                } catch (IvyException | InterruptedException e) {
                    e.printStackTrace();
                }
            }
            else System.out.println("JAVA\tErreur : Impossible d'envoyer la requete car l'hote C est déconnecté");
        }else System.out.println("JAVA\tErreur : Le traitement que vous tentez de lancer n'est pas un traitement de recherche");
        return scorePaths;
    }

    public void stopBus() {
        if(cConnected) {
            try {
                // Envoie un message de fin de traitement au C
                bus.sendMsg(C_ID + " " + ADDR_TX_FRAME + " " + ADDR_STOP_BUS + " " + 0 + " " + 0);
                // Attend l'aquittement du C
                ack = false;
                synchronized (bus) { while(!ack) bus.wait(); }
                if(affConsole) System.out.println("JAVA\tDéconnexion du C");
            } catch (IvyException | InterruptedException e) {
                e.printStackTrace();
            }
        }
        // Arrête le bus côté JAVA
        bus.stop();
        if(affConsole) System.out.println("JAVA\tBus arrêté avec succès");
    }
}