package controleur;
//résultats de la recherche audio qui se lance au moment recherché par l'utilisateur

import entite.Resultat;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TableCell;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;

import javax.sound.sampled.*;
import java.io.File;
import java.io.IOException;

public class AffichageResultatRechercheAudioController {

    @FXML
    private Button retour;
    @FXML
    private TableColumn<Resultat, Integer> numero;
    @FXML
    private TableColumn<Resultat, String> chemin;
    @FXML
    private TableColumn<Resultat, String> resultat;
    @FXML
    private TableColumn<Resultat, String> titre;
    @FXML
    private TableView<Resultat> resultatAudio;
    private Clip clip;

    @FXML
    public void onRetourButtonClick() throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("rechercheAudio.fxml"));
        Stage stage = (Stage) retour.getScene().getWindow();
        stage.setScene(new Scene(root));
    }

    public void onMetPause(){
        clip.stop();
    }

    public void initialize() {
        numero.setCellValueFactory(new PropertyValueFactory<Resultat, Integer>("numero"));
        titre.setCellValueFactory(new PropertyValueFactory<Resultat, String>("titre"));
        resultat.setCellValueFactory(new PropertyValueFactory<Resultat, String>("resultat"));
        chemin.setCellValueFactory(new PropertyValueFactory<Resultat, String>("chemin"));
        setupTable();
    }

    @FXML
    public void rowClicked(MouseEvent event){
        if (event.getClickCount() != 1 && event.getTarget() instanceof TableCell) {
            // Ne rien faire si l'utilisateur a cliqué sur le bandeau de la TableView

            Resultat clicked = resultatAudio.getSelectionModel().getSelectedItem();
            if (clip != null && clip.isRunning()) {
                clip.stop();
            }
            String audioFilePath = clicked.getChemin();

            try {
                // Créer un objet File à partir du chemin du fichier audio
                File audioFile = new File(audioFilePath);

                // Créer un flux audio à partir du fichier audio
                AudioInputStream audioStream = AudioSystem.getAudioInputStream(audioFile);

                // Obtenir un clip audio à partir du flux audio
                clip = AudioSystem.getClip();

                // Ouvrir le clip audio avec le flux audio
                clip.open(audioStream);
                int val = Integer.parseInt(clicked.getResultat());
                // Définir la position de départ en millisecondes
                long startPosition = (long) val * 1000; // par exemple 5 secondes
                clip.setMicrosecondPosition(startPosition * 1000);
                // Lancer la lecture du clip audio
                clip.start();

            } catch (IOException | UnsupportedAudioFileException | LineUnavailableException ex) {
                System.err.println("Erreur lors de la lecture du fichier audio : " + ex.getMessage());
            }
        }
    }

    //résultats qui vont être affichés
    private void setupTable() {
        Resultat histos0 = new Resultat(1, "Corpus_fi.wav", "29", "src/main/resources/son/corpus_fi.wav");
        Resultat histos1 = new Resultat(2, "Corpus_fi.wav", "25", "src/main/resources/son/corpus_fi.wav");
        Resultat histos2 = new Resultat(3, "Corpus_fi.wav", "33", "src/main/resources/son/corpus_fi.wav");
        resultatAudio.getItems().addAll(histos0, histos1, histos2);
    }
}
