import java.util.ArrayList;
import java.util.List;

public class Motor {

    private int id;
    private String makeTarget;
    private boolean connection;
    private boolean ack;
    private boolean endProcessing;
    private List<ScorePath> scorePaths = new ArrayList<>();

    public Motor(int id, String makeTarget) {
        this.id = id;
        this.makeTarget = makeTarget;
        this.connection = false;
        this.ack=false;
        this.endProcessing=false;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id=id;
    }

    public String getMakeTarget() {
        return makeTarget;
    }

    public void setMakeTarget(String makeTarget) {
        this.makeTarget=makeTarget;
    }

    public boolean getConnection() {
        return connection;
    }

    public void setConnection(boolean connection) {
        this.connection=connection;
    }

    public boolean getAck() {
        return ack;
    }

    public void setAck(boolean ack) {
        this.ack=ack;
    }

    public boolean getEndProcessing() {
        return endProcessing;
    }

    public void setEndProcessing(boolean endProcessing) {
        this.endProcessing=endProcessing;
    }
    
    public List<ScorePath> getScorePaths(){
        return scorePaths;
    }

    public void addScorePaths(ScorePath scorePath){
        scorePaths.add(scorePath);
    }

    public void clearScorePaths(){
        scorePaths.clear();
    }

}
