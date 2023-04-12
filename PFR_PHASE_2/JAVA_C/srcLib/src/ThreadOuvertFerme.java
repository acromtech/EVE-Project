import java.io.File;
import java.util.Arrays;

public class ThreadOuvertFerme extends Thread{
    private boolean condition;
    private String path;
    private String[] files;
    private Motor motor;
    private Bus bus;

    public ThreadOuvertFerme(String name, String path, boolean condition, Motor motor, Bus bus) {
        super(name);
        this.path = path;
        File file = new File(path);
        this.files = file.list();
        this.condition = condition;
        this.motor = motor;
        this.bus = bus;
    }

    @Override
    public void run() {
        System.out.println("Thread starté");
        while (condition) {
            try {
                Thread.sleep(10000); // attendre 10 secondes
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            
            File directory = new File(path);
            String[] currentFiles = directory.list();
            if(currentFiles == null){
                //supprimer base descripteur
            }
            Arrays.sort(currentFiles);
            Arrays.sort(files);

            if (!Arrays.equals(currentFiles, files)) {
                System.out.println("Changes in directory " + path + ":");
                for (String file : currentFiles) {
                    if (!Arrays.asList(files).contains(file)) {
                        this.bus.launchIndexation(motor, Bus.ADDR_INDEXATION_ALL);
                        System.out.println(" + " + file);
                    }
                    
                }
                for (String file : files) {
                    if (!Arrays.asList(currentFiles).contains(file)) {
                        if(this.path.endsWith("Texte")) {
                            this.bus.sendFrame(motor, Bus.ADDR_SUPPRIMER_DESCRIPTEUR, "TEXTE", 0x00);
                        }
                        else if(this.path.endsWith("Image")){
                            this.bus.sendFrame(motor, Bus.ADDR_SUPPRIMER_DESCRIPTEUR, "IMAGE", 0x00);
                        }
                        else if(this.path.endsWith("Son")){
                            this.bus.sendFrame(motor, Bus.ADDR_SUPPRIMER_DESCRIPTEUR, "SON", 0x00);
                        }
                        
                        System.out.println(" - " + file);
                    }
                }
                files = currentFiles;
            }
        }
    }

    public void arret(){
        this.condition = false;
        System.out.println("Thread arreté");
    }
    
    public synchronized void pauseThread() {
        System.out.println("Thread paused");
        this.condition = false;
    }
    
    public synchronized void resumeThread() {
        System.out.println("Thread resumed");
        this.condition = true;
        notifyAll();
    }
    /*
    public static void main(String[] args) {
        String path = "IndexationImage/TXT";
        ThreadOuvertFerme thread = new ThreadOuvertFerme("thread", path, true);
        thread.start();
    }
    */
}
