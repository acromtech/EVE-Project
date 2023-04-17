package controleur;
//recherche d'image avec le chemin d'une autre image

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

public class RechercheImageController {

    @FXML
    private TextField cheminImage;
    @FXML
    private Button retour, search;

    //lance la recherche
    @FXML
    public void onSearchButtonClick() throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("affichageResultatRechercheImage.fxml"));
        Stage stage = (Stage) search.getScene().getWindow();
        stage.setScene(new Scene(root));
    }

    //renvoie à la page précédente
    @FXML
    public void onRetourButtonClick() throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("choixRechercheImage.fxml"));
        Stage stage = (Stage) retour.getScene().getWindow();
        stage.setScene(new Scene(root));
    }

    //lance la recherche grâce à la touche clavier "entrée"
    @FXML
    public void onEnterAction(KeyEvent keyEvent) throws IOException {
        if (keyEvent.getCode().equals(KeyCode.ENTER)) {
            Parent root = FXMLLoader.load(getClass().getResource("affichageResultatRechercheImage.fxml"));
            Stage stage = (Stage) cheminImage.getScene().getWindow();
            stage.setScene(new Scene(root));
        }
    }

    //premet de sélectionner l'image recherchée directement dans l'ordinateur
    public void onBrowseBoutonClick() {
        // Crée un FileChooser
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Choisir un fichier BMP ou JPG");
        fileChooser.setInitialDirectory(new File(System.getProperty("user.home") + "/Téléchargements/PFR2/src/main/resources/images"));
        // Configure le FileChooser pour n'afficher que les fichiers texte
        FileChooser.ExtensionFilter extFilter =
                new FileChooser.ExtensionFilter("Fichiers IMAGE (*.jpg)", "*.jpg");
        FileChooser.ExtensionFilter extFilter1 =
                new FileChooser.ExtensionFilter("Fichiers IMAGE (*.bmp)", "*.bmp");
        fileChooser.getExtensionFilters().add(extFilter);
        fileChooser.getExtensionFilters().add(extFilter1);
        // Affiche la boîte de dialogue de sélection de fichier et récupère le fichier sélectionné
        Stage stage = new Stage();
        File selectedFile = fileChooser.showOpenDialog(stage);

        // Vérifie si un fichier a été sélectionné, puis affiche son chemin
        if (selectedFile != null) {
            String filePath = selectedFile.getAbsolutePath();
            cheminImage.setText(filePath);
        }
    }
}
