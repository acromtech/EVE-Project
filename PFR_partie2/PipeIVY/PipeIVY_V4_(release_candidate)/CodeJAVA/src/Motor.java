import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class Motor {

    private int id;
    private String makeTarget;
    private boolean connection;
    private boolean ack;
    private boolean endProcessing;
    private List<ScorePath> scorePaths = new ArrayList<>();

    //.config
    private BDconfig bdconfig = BDconfig.getInstance();
    private File configFile;

    //Mode ouvert / Mode fermé
    private boolean openMode;

    public Motor(int id, String makeTarget, String configPath) {
        this.id = id;
        this.makeTarget = makeTarget;
        this.connection = false;
        this.ack=false;
        this.endProcessing=false;
        this.configFile=new File(configPath);
    }

    protected int getId() {
        return id;
    }

    protected void setId(int id) {
        this.id=id;
    }

    protected String getMakeTarget() {
        return makeTarget;
    }

    protected void setMakeTarget(String makeTarget) {
        this.makeTarget=makeTarget;
    }

    protected boolean getConnection() {
        return connection;
    }

    protected void setConnection(boolean connection) {
        this.connection=connection;
    }

    protected boolean getAck() {
        return ack;
    }

    protected void setAck(boolean ack) {
        this.ack=ack;
    }

    protected boolean getEndProcessing() {
        return endProcessing;
    }

    protected void setEndProcessing(boolean endProcessing) {
        this.endProcessing=endProcessing;
    }
    
    protected List<ScorePath> getScorePaths(){
        return scorePaths;
    }

    protected void addScorePaths(ScorePath scorePath){
        scorePaths.add(scorePath);
    }

    protected void clearScorePaths(){
        scorePaths.clear();
    }

    protected int getIndexationAudioN() {
        return Integer.parseInt(bdconfig.getParametre("indexationAudioN"));
    }

    protected void setIndexationAudioN(int indexationAudioN) {
        bdconfig.updateConfig("indexationAudioN",""+indexationAudioN,configFile);
    }

    protected int getIndexationAudioM() {
        return Integer.parseInt(bdconfig.getParametre("indexationAudioM"));
    }

    protected void setIndexationAudioM(int indexationAudioM) {
        bdconfig.updateConfig("indexationAudioM",""+indexationAudioM,configFile);
    }

    protected int getSeuil() {
        return Integer.parseInt(bdconfig.getParametre("seuil"));
    }

    protected void setSeuil(int seuil) {
        bdconfig.updateConfig("seuil",""+seuil,configFile);
    }

    protected int getDureeAudioCorpus() {
        return Integer.parseInt(bdconfig.getParametre("dureeAudioCorpus"));
    }

    protected void setDureeAudioCorpus(int dureeAudioCorpus) {
        bdconfig.updateConfig("dureeAudioCorpus",""+dureeAudioCorpus,configFile);
    }

    protected int getNbListe() {
        return Integer.parseInt(bdconfig.getParametre("nbListe"));
    }

    protected void setNbListe(int nbListe) {
        bdconfig.updateConfig("nbListe",""+nbListe,configFile);
    }

    protected int getSeuilMotSignificatif() {
        return Integer.parseInt(bdconfig.getParametre("seuilMotSignificatif"));
    }

    protected void setSeuilMotSignificatif(int seuilMotSignificatif) {
        bdconfig.updateConfig("seuilMotSignificatif",""+seuilMotSignificatif,configFile);
    }

    protected void setMultiConfigParameters(Map<String, String> updates){
        bdconfig.multiUpdateConfig(updates,configFile);
    }
    
    protected boolean getOpenMode() {
        return openMode;
    }

    protected void setOpenMode(boolean openMode) {
        this.openMode=openMode;
    }
}