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
    public boolean affConsole=false;       //Active ou désactive les affichage console
    public boolean acquitement=true;       //Active ou désactive les aquitements
    private boolean cConnected=false;
    private boolean ack=false;
    private boolean traitement_c_en_cours=false;
    private List<ScorePath> scorePathList = new ArrayList<>();

    //Constructeur
    public wrapperIvyPfr(){
        bus = new Ivy(""+Id.JAVA.getValue(),"",null);
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
        bus.bindMsg("^"+Id.JAVA.getValue()+" "+FrameType.TX_FRAME.getValue()+" (.*) (.*)",new IvyMessageListener(){
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
        bus.bindMsg("^"+Id.JAVA.getValue()+" "+FrameType.RX_FRAME.getValue()+" (.*) (.*) (.*)",new IvyMessageListener(){
            public void receive(IvyClient client, String[] args){
                if(Integer.parseInt(args[0])==Address.SCORE_CHEMIN.getValue()) {
                    if(Integer.parseInt(args[1])!=0xFF){
                        scorePathList.add(new ScorePath(Integer.parseInt(args[1]), args[2]));
                        try {
                            bus.sendMsg(Id.C.getValue()+" "+FrameType.RX_FRAME.getValue()+" "+Address.SCORE_CHEMIN.getValue());
                        } catch (IvyException e) {
                            e.printStackTrace();
                        }
                    } else traitement_c_en_cours=false;
                } else if(Integer.parseInt(args[0])==Address.CONNECTED.getValue()){
                    cConnected=true;
                    synchronized (bus) { bus.notify(); }
                } else System.out.println("JAVA\tErreur : Adresse de la trame RX inconnue");
            }
        });
    }

    public void launchIndexation(Address typeTraitement){
        if(typeTraitement.getValue()==Address.INDEXATION_ALL.getValue() 
        ||typeTraitement.getValue()==Address.INDEXATION_TEXTE.getValue()
        ||typeTraitement.getValue()==Address.INDEXATION_IMAGE.getValue()
        ||typeTraitement.getValue()==Address.INDEXATION_SON.getValue()){
            if(cConnected){
                try{
                    bus.sendMsg(Id.C.getValue()+" "+FrameType.TX_FRAME.getValue()+" "+typeTraitement.getValue()+" "+0+" "+0);
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
    public List<ScorePath> sendRequete(Address typeTraitement,String requete,int nombreResultatMax){
        scorePathList.clear();
        if(typeTraitement.getValue()==Address.TEXTE_FICHIER.getValue() 
        ||typeTraitement.getValue()==Address.TEXTE_MOTCLE.getValue()
        ||typeTraitement.getValue()==Address.IMAGE_FICHIER.getValue()
        ||typeTraitement.getValue()==Address.IMAGE_MOTCLE.getValue()
        ||typeTraitement.getValue()==Address.SON_FICHIER.getValue()){
            if(cConnected){
                try {
                    if(affConsole) System.out.println("JAVA\tTraitement "+typeTraitement);
                    bus.sendMsg(Id.C.getValue()+" "+FrameType.TX_FRAME.getValue()+" "+typeTraitement.getValue()+" "+requete+" "+nombreResultatMax);
                    
                    ack=false;
                    synchronized (bus) { while(!ack) bus.wait(); }
                    if(affConsole) System.out.println("JAVA\tACK");
                    traitement_c_en_cours=true;
                    synchronized (bus) { while(traitement_c_en_cours) bus.wait(); }
                    if(affConsole) System.out.println("JAVA\tTraitement effectué");

                    bus.sendMsg(Id.C.getValue()+" "+FrameType.RX_FRAME.getValue()+" "+Address.SCORE_CHEMIN.getValue());

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
        return scorePathList;
    }

    public void stopBus() {
        if(cConnected) {
            try {
                // Envoie un message de fin de traitement au C
                bus.sendMsg(Id.C.getValue() + " " + FrameType.TX_FRAME.getValue() + " " + Address.STOP_BUS.getValue() + " " + 0 + " " + 0);
                // Attend l'aquittement du C
                ack = false;
                synchronized (bus) { while(!ack) bus.wait(); }
                if(affConsole) System.out.println("JAVA\tDéconnexion du C dans quelques secondes");
            } catch (IvyException | InterruptedException e) {
                e.printStackTrace();
            }
        }
        // Arrête le bus côté JAVA
        bus.stop();
        if(affConsole) System.out.println("JAVA\tBus arrêté avec succès");
    }
    
}