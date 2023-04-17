import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

/**
 * Auteur : Alexis GIBERT
*/
public class Motor {

    private int id;
    private String makeTarget;
    private boolean connection;
    private boolean ack;
    private boolean endProcessing;
    private ArrayList<ScorePath> scorePaths = new ArrayList<>();
    private String pathMakefile;

    //.config
    private BDconfig bdconfig = BDconfig.getInstance();
    private File configFile;

    //Mode ouvert / Mode fermé
    private boolean openMode;

    /**
     * Constructeur du moteur de recherche
     * @param id id du moteur 
     * @param pathMakefile chemin d'accès au Makefile du moteur de recherche
     * @param makeTarget nom de la cible du Makefile a lancer
     * @param configPath chemin d'accès au .config asscocié
     */
    public Motor(int id, String pathMakefile, String makeTarget, String configPath) {
        this.id = id;
        this.makeTarget = makeTarget;
        this.pathMakefile = pathMakefile;
        this.connection = false;
        this.ack=false;
        this.endProcessing=false;
        this.configFile=new File(configPath);
    }

    /**
     * Récupère le chemin d'accès au Makefile du moteur de recherche
     * @return
     */
    protected String getPathMakefile() {
        return pathMakefile;
    }

    /**
     * Met a jour le chemin d'accès au Makefile du moteur de recherche
     * @param pathMakefile
     */
    protected void setPathMakefile(String pathMakefile) {
        this.pathMakefile=pathMakefile;
    }

    /**
     * Récupère l'id du moteur
     * @return
     */
    protected int getId() {
        return id;
    }

    /**
     * Met a jour l'id du moteur
     * @param id
     */
    protected void setId(int id) {
        this.id=id;
    }

    /**
     * Récupère la cible du Makefile
     * @return
     */
    protected String getMakeTarget() {
        return makeTarget;
    }

    /**
     * Met a jour la cible du Makefile
     * @param makeTarget
     */
    protected void setMakeTarget(String makeTarget) {
        this.makeTarget=makeTarget;
    }

    /**
     * Récupère l'état du moteur
     * @return
     */
    protected boolean getConnection() {
        return connection;
    }

    /**
     * Met a jour l'état du moteur
     * @param connection
     */
    protected void setConnection(boolean connection) {
        this.connection=connection;
    }

    /**
     * Informe si la trame envoyé par le moteur a bien été acquité
     * @return
     */
    protected boolean getAck() {
        return ack;
    }

    /**
     * Met a jour l'état de l'aquitement du moteur
     * @param ack
     */
    protected void setAck(boolean ack) {
        this.ack=ack;
    }

    /**
     * Informe du la fin du traitement du moteur
     * @return
     */
    protected boolean getEndProcessing() {
        return endProcessing;
    }

    /**
     * Met a jour l'état de la fin de traitement du moteur
     * @param endProcessing
     */
    protected void setEndProcessing(boolean endProcessing) {
        this.endProcessing=endProcessing;
    }
    
    /**
     * Récupère la liste de Score/Chemin
     * @return
     */
    protected List<ScorePath> getScorePaths(){
        return scorePaths;
    }

    /**
     * Ajoute un score et son chemin asscocié a la liste de Score/Chemin
     * @param scorePath
     */
    protected void addScorePaths(ScorePath scorePath){
        scorePaths.add(scorePath);
    }
    
    /**
     * Supprime le contenu de la liste de Score/Chemin
     */
    protected void clearScorePaths(){
        this.scorePaths = null;
    }

    /**
     * Récupère le paramètre IndexationAudioN du .config
     * @return
     */
    protected int getIndexationAudioN() {
        return Integer.parseInt(bdconfig.getParametre("indexationAudioN"));
    }

    /**
     * Met a jour le paramètre IndexationAudioN du .config
     * @param indexationAudioN
     */
    protected void setIndexationAudioN(int indexationAudioN) {
        bdconfig.updateConfig("indexationAudioN",""+indexationAudioN,configFile);
    }

    /**
     * Récupère le paramètre IndexationAudioM du .config
     * @return
     */
    protected int getIndexationAudioM() {
        return Integer.parseInt(bdconfig.getParametre("indexationAudioM"));
    }

    /**
     * Met a jour le paramètre IndexationAudioM du .config
     * @param indexationAudioM
     */
    protected void setIndexationAudioM(int indexationAudioM) {
        bdconfig.updateConfig("indexationAudioM",""+indexationAudioM,configFile);
    }

    /**
     * Récupère le paramètre Seuil du .config
     * @return
     */
    protected int getSeuil() {
        return Integer.parseInt(bdconfig.getParametre("seuil"));
    }

    /**
     * Met a jour le paramètre Seuil du .config
     * @param seuil
     */
    protected void setSeuil(int seuil) {
        bdconfig.updateConfig("seuil",""+seuil,configFile);
    }

    /**
     * Récupère le paramètre DuréeAudioCorpus du .config
     * @return
     */
    protected int getDureeAudioCorpus() {
        return Integer.parseInt(bdconfig.getParametre("dureeAudioCorpus"));
    }

    /**
     * Met a jour le paramètre DuréeAudioCorpus du .config
     * @param dureeAudioCorpus
     */
    protected void setDureeAudioCorpus(int dureeAudioCorpus) {
        bdconfig.updateConfig("dureeAudioCorpus",""+dureeAudioCorpus,configFile);
    }

    /**
     * Récupère le paramètre NbListe du .config
     * @return
     */
    protected int getNbListe() {
        return Integer.parseInt(bdconfig.getParametre("nbListe"));
    }

    /**
     * Met a jour le paramètre NbListe du .config
     * @param nbListe
     */
    protected void setNbListe(int nbListe) {
        bdconfig.updateConfig("nbListe",""+nbListe,configFile);
    }

    /**
     * Récupère le paramètre SeuilMotSignificatif du .config
     * @return
     */
    protected int getSeuilMotSignificatif() {
        return Integer.parseInt(bdconfig.getParametre("seuilMotSignificatif"));
    }

    /**
     * Met a jour le paramètre SeuilMotSignificatif du .config
     * @param seuilMotSignificatif
     */
    protected void setSeuilMotSignificatif(int seuilMotSignificatif) {
        bdconfig.updateConfig("seuilMotSignificatif",""+seuilMotSignificatif,configFile);
    }

    /**
     * Met a jour plusieurs paramètres dans le .config
     */
    protected void setMultiConfigParameters(Map<String, String> updates){
        bdconfig.multiUpdateConfig(updates,configFile);
    }
    
    /**
     * Récupère l'état de l'OpenMode
     * @return
     */
    protected boolean getOpenMode() {
        return openMode;
    }

    /**
     * Met a jour l'état de l'OpenMode
     * @param openMode
     */
    protected void setOpenMode(boolean openMode) {
        this.openMode=openMode;
    }

    /**
     * Déclare un nouveau ScorePath
     */
    public void setScorePath() {
        this.scorePaths = new ArrayList<>();
    }
}
