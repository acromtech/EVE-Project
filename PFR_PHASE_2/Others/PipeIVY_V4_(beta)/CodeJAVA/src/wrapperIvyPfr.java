import java.io.BufferedReader;
import java.io.File;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.List;
import fr.dgac.ivy.Ivy;
import fr.dgac.ivy.IvyClient;
import fr.dgac.ivy.IvyException;
import fr.dgac.ivy.IvyMessageListener;

/**
 * Le wrapper utilise un protocole CAN SDO
 * Trames de la forme ID - ADDR - DATA1 - DATA2
*/
public class wrapperIvyPfr{

    //ID
    private static final int MASTER_ID                              = 0x00;
    //private static final int BROADCAST                              = 0xFF;

    //Adresses
    public static final int ADDR_CONNECTED                          = 0x01;
    public static final int ADDR_INDEXATION_TEXTE                   = 0x10;     //(TX_FRAME) Demande l'indexation des données textuelles (+ ACK)
    public static final int ADDR_INDEXATION_IMAGE                   = 0x11;     //(TX_FRAME) Demande l'indexation des données photographique (+ ACK)
    public static final int ADDR_INDEXATION_SON                     = 0x12;     //(TX_FRAME) Demande l'indexation des données sonores (+ ACK)
    public static final int ADDR_INDEXATION_ALL                     = 0x13;     //(TX_FRAME) Demande l'indexation de toutes les données (+ ACK)
    public static final int ADDR_TEXTE_MOTCLE                       = 0x20;     //(TX_FRAME) Demande de réaliser une recherche textuelle par mot clé (+ ACK)
    public static final int ADDR_TEXTE_FICHIER                      = 0x21;     //(TX_FRAME) Demande de réaliser une recherche textuelle par fichier (+ ACK)
    public static final int ADDR_IMAGE_MOTCLE                       = 0x30;     //(TX_FRAME) Demande de réaliser une recherche photographique par mot clé (+ ACK)
    public static final int ADDR_IMAGE_FICHIER                      = 0x31;     //(TX_FRAME) Demande de réaliser une recherche photographique par fichier (+ ACK) 
    public static final int ADDR_SON_FICHIER                        = 0x40;     //(TX_FRAME) Demande de réaliser une recherche sonore par fichier (+ ACK)
    public static final int ADDR_SCORE_CHEMIN                       = 0x50;     //(RX_FRAME) Récupère les données de résulats (+ ACK)
    public static final int ADDR_STOP_BUS                           = 0x60;     //(TX_FRAME) Ordonne l'arret de la connection au bus virtuel (+ ACK)
    public static final int ADDR_OPEN_MODE                          = 0x70;     //(TX_FRAME) Demande l'ouverture ou non de l'indexation (+ ACK)

   //Attributs
   private Ivy bus;
   private boolean affConsole=false;       //Active ou désactive les affichage console

   //Constructeur
   public wrapperIvyPfr(){
        bus = new Ivy(""+MASTER_ID,"",null);
        try{
            bus.start("127.255.255.255:2010");
            if(affConsole) System.out.println("JAVA\tInitialisation de la communication effectuée avec succès");
        }catch (IvyException e) {
            System.out.println("La connexion au bus a échoué");
        }
   }

   /**
    * Ajoute un moteur au bus : Compile et lance la cible du Makefile dans un thread séparé
    * @param motor
    */
   protected void addMotor(Motor motor){
       System.out.println("motor:"+motor.getId()+",master:"+MASTER_ID);
       try {
           subscribers(motor);
       } catch (IvyException e) {
           e.printStackTrace();
       }
       new Thread(new Runnable() {
           public void run() {
               try {
                   ProcessBuilder pb = new ProcessBuilder("make",""+motor.getMakeTarget());
                   pb.directory(new File(System.getProperty("user.dir") + "/CodeC"));
                   pb.redirectErrorStream(true);
                   Process p = pb.start();
                   BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
                   String line1;
                   while ((line1 = reader.readLine()) != null) {
                       System.out.println(line1);
                   }
                   p.waitFor();
               } catch (IOException | InterruptedException e) {
                   System.out.println("JAVA\tErreur 1 : La cible du makefile ("+motor.getMakeTarget()+") ou le répertoire de travail est incorrect");
               }
               try{
                   ProcessBuilder pb2 = new ProcessBuilder("./"+motor.getMakeTarget(),""+MASTER_ID,""+motor.getId());
                   System.out.println("./"+motor.getMakeTarget()+" "+MASTER_ID+" "+motor.getId());
                   pb2.directory(new File(System.getProperty("user.dir") + "/CodeC"));
                   pb2.redirectErrorStream(true);
                   Process p2 = pb2.start();
                   BufferedReader reader2 = new BufferedReader(new InputStreamReader(p2.getInputStream()));
                   String line2;
                   while ((line2 = reader2.readLine()) != null) {
                       System.out.println(line2);
                   }
                   p2.waitFor();
               } catch (IOException | InterruptedException e) {
                   System.out.println("JAVA\tErreur 2 : Le lancement du moteur avec les paramètres désirés a échoué");
               }
           }
       }).start();
       synchronized (bus) { 
           while(!motor.getConnection()){
               try {
                   bus.wait();
               } catch (InterruptedException e) {
                   System.out.println("JAVA\tErreur 3 : L'ajout du moteur "+motor.getId()+" de chemin "+motor.getMakeTarget()+" a échoué");
               }
           }
       }
   }
   
   /**
    * Retire le moteur du bus
    * @param motor
    */
   protected void removeMotor(Motor motor) {
       if(motor.getConnection()) sendFrame(motor,ADDR_STOP_BUS,"",0);
   }

   protected void subscribers(Motor motor) throws IvyException{
       bus.bindMsg("^"+MASTER_ID+" "+motor.getId()+" (.*) (.*) (.*)",new IvyMessageListener(){
           public void receive(IvyClient client, String[] args){
               if(Integer.parseInt(args[1])==0xFF && Integer.parseInt(args[2])==0xFF){
                   motor.setAck(true);
                   synchronized (bus) { bus.notify(); }
               } else if(Integer.parseInt(args[1])==0xFF && Integer.parseInt(args[2])==0xFE){
                   motor.setEndProcessing(true);
                   synchronized (bus) { bus.notify(); }
               } else if(Integer.parseInt(args[0])==ADDR_SCORE_CHEMIN) {
                   motor.addScorePaths(new ScorePath(Integer.parseInt(args[1]), args[2]));
                   try {
                       bus.sendMsg(motor.getId()+" "+MASTER_ID+" "+ADDR_SCORE_CHEMIN+" "+0x00+" "+0x00);
                   } catch (IvyException e) {
                       e.printStackTrace();
                   }
               } else if(Integer.parseInt(args[0])==ADDR_CONNECTED){
                   motor.setConnection(true);
                   synchronized (bus) { bus.notify(); }
               }
           }
       });
   }

   /**
    * Lance un traitement d'indexation
    * @param motor
    * @param addrTypeTraitement
    */
   protected void launchIndexation(Motor motor,final int addrTypeTraitement){
       if(addrTypeTraitement==ADDR_INDEXATION_ALL || addrTypeTraitement==ADDR_INDEXATION_TEXTE || addrTypeTraitement==ADDR_INDEXATION_IMAGE || addrTypeTraitement==ADDR_INDEXATION_SON){
           if(motor.getConnection()) sendFrame(motor,addrTypeTraitement,""+0x00,0x00);
           else System.out.println("JAVA\tErreur : Impossible d'envoyer la requete car le moteur "+motor.getId()+" est déconnecté");
       } else System.out.println("JAVA\tErreur : Le traitement que vous tenter de lancer n'est pas un traitement d'indexation");
   }
   
   /**
    * Envoi une trame sur le bus
    * Forme de la trame : MOTOR ID - MASTER ID - TYPE DE TRAITEMENT - DATA1 - DATA2
    * @param motor
    * @param addrTypeTraitement
    * @param data1
    * @param data2
    */
   private void sendFrame(Motor motor, final int addrTypeTraitement, String data1, int data2){
       if(affConsole) System.out.println("JAVA\tTraitement "+addrTypeTraitement);
       try {
           bus.sendMsg(motor.getId()+" "+MASTER_ID+" "+addrTypeTraitement+" "+data1+" "+data2);
           motor.setAck(false);
           synchronized (bus) { while(!motor.getAck()) bus.wait(); }
           if(affConsole) System.out.println("JAVA\tACK");
           motor.setEndProcessing(false);
           synchronized (bus) { while(!motor.getEndProcessing()) bus.wait(); }
           if(affConsole) System.out.println("JAVA\tTraitement effectué");
       } catch (IvyException | InterruptedException e) {
           System.out.println("L'envoi de la trame "+motor.getId()+" "+MASTER_ID+" "+addrTypeTraitement+" "+data1+" "+data2+" a échoué");
       }
   }

   /**
    * Lance une requete sur un moteur de recherche
    * @param motor
    * @param addrTypeTraitement
    * @param requete
    * @param nombreResultatMax
    * @return
    */
   protected List<ScorePath> sendRequete(Motor motor, final int addrTypeTraitement,String requete,int nombreResultatMax){
       motor.clearScorePaths();
       if(addrTypeTraitement==ADDR_TEXTE_FICHIER || addrTypeTraitement==ADDR_TEXTE_MOTCLE || addrTypeTraitement==ADDR_IMAGE_FICHIER  || addrTypeTraitement==ADDR_IMAGE_MOTCLE || addrTypeTraitement==ADDR_SON_FICHIER){
           if(motor.getConnection()){
               sendFrame(motor,addrTypeTraitement,requete,nombreResultatMax);
               sendFrame(motor,ADDR_SCORE_CHEMIN,""+0x00,0x00);
           }
           else System.out.println("JAVA\tErreur : Impossible d'envoyer la requete car le moteur "+motor.getId()+" est déconnecté");
       }else System.out.println("JAVA\tErreur : Le traitement que vous tentez de lancer n'est pas un traitement de recherche");
       return motor.getScorePaths();
   }

   /**
    * Lance une requete sur tous les moteurs de recherche connecté sur le bus (Broadcast)
    * @param addrTypeTraitement
    * @param requete
    * @param nombreResultatMax
    * @return
    */
   /*
   protected List<List<ScorePath>> sendAllRequete(final int addrTypeTraitement,String requete,int nombreResultatMax){
    motor.clearScorePaths();
    if(addrTypeTraitement==ADDR_TEXTE_FICHIER || addrTypeTraitement==ADDR_TEXTE_MOTCLE || addrTypeTraitement==ADDR_IMAGE_FICHIER  || addrTypeTraitement==ADDR_IMAGE_MOTCLE || addrTypeTraitement==ADDR_SON_FICHIER){
        if(motor.getConnection()){
            sendFrame(motor,addrTypeTraitement,requete,nombreResultatMax);
            sendFrame(motor,ADDR_SCORE_CHEMIN,""+0x00,0x00);
        }
        else System.out.println("JAVA\tErreur : Impossible d'envoyer la requete car le moteur "+motor.getId()+" est déconnecté");
    }else System.out.println("JAVA\tErreur : Le traitement que vous tentez de lancer n'est pas un traitement de recherche");
    return motor.getScorePaths();
    }
    */
   
   /**
    * Arrête le bus
    */
   protected void stopBus() {
       bus.stop();
       if(affConsole) System.out.println("JAVA\tBus arrêté avec succès");
   }

    /**
     * Affiche les informations critiques sur le terminal
     * @param affConsole
     */
    protected void setAffConsole(boolean affConsole){
       this.affConsole=affConsole;
    }

    /**
     * Renvoi l'état de affConsole
     * @return
     */
    protected boolean getAffConsole(){
       return affConsole;
    }

    /**
     * Renvoi l'état de OpenMode
     * @param motor
     * @return
     */
    protected boolean getOpenMode(Motor motor) {
        return motor.getOpenMode();
    }

    /**
     * Active (true) ou désactive (false) l'OpenMode
     * @param motor
     * @param openMode
     */
    protected void setOpenMode(Motor motor, boolean openMode) {
        sendFrame(motor, ADDR_OPEN_MODE, ""+openMode, 0x00);
        motor.setOpenMode(openMode);
    }
}