package controleur;


import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;

public class RechercheAudioController {

    @FXML
    private TextField cheminAudio;

    @FXML
    private Button retour, search;

    @FXML
    public void onSearchButtonClick() throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("affichageResultatRechercheAudio.fxml"));
        Stage stage = (Stage) search.getScene().getWindow();
        stage.setScene(new Scene(root));
    }

    @FXML
    public void onRetourButtonClick() throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("choixRechercheAudio.fxml"));
        Stage stage = (Stage) retour.getScene().getWindow();
        stage.setScene(new Scene(root));
    }

    @FXML
    public void onEnterAction(KeyEvent keyEvent) throws IOException {
        if (keyEvent.getCode().equals(KeyCode.ENTER)) {
            Parent root = FXMLLoader.load(getClass().getResource("affichageResultatRechercheAudio.fxml"));
            Stage stage = (Stage) cheminAudio.getScene().getWindow();
            stage.setScene(new Scene(root));
        }
    }

    public void onBrowseBoutonClick() {
        // Crée un FileChooser
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Choisir un fichier WAV");
        fileChooser.setInitialDirectory(new File(System.getProperty("user.home") + "/Téléchargements/PFR2/src/main/resources/son"));
        // Configure le FileChooser pour n'afficher que les fichiers texte
        FileChooser.ExtensionFilter extFilter =
                new FileChooser.ExtensionFilter("Fichiers AUDIO (*.wav)", "*.wav");
        fileChooser.getExtensionFilters().add(extFilter);
        // Affiche la boîte de dialogue de sélection de fichier et récupère le fichier sélectionné
        Stage stage = new Stage();
        File selectedFile = fileChooser.showOpenDialog(stage);

        // Vérifie si un fichier a été sélectionné, puis affiche son chemin
        if (selectedFile != null) {
            String filePath = selectedFile.getAbsolutePath();
            cheminAudio.setText(filePath);
        }
    }
}
