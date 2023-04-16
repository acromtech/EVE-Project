package controleur;
//rechercher un texte à l'aide de son chemin

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

public class RechercheTexteController {
//Un TexteField permet à l'utilisateur de rentrer sa recherche
    @FXML
    private TextField cheminTexte;
//Déclaration des boutons
    @FXML
    private Button retour, search, browse;
    //Lorsque le bouton search est activé cela lance la rechecrhe
    @FXML
    public void onSearchButtonClick() throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("affichageResultatRechercheTexte.fxml"));
        Stage stage = (Stage) search.getScene().getWindow();
        stage.setScene(new Scene(root));
    }
    //Lorsque le bouton retour est activé cela affiche la fenêtre juste d'avant
    @FXML
    public void onRetourButtonClick() throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("choixRechercheTexte.fxml"));
        Stage stage = (Stage) retour.getScene().getWindow();
        stage.setScene(new Scene(root));
    }
    //On peut également activer la recherche avec la touche "entrée" du clavier
    @FXML
    public void onEnterAction(KeyEvent keyEvent) throws IOException {
        if (keyEvent.getCode().equals(KeyCode.ENTER)) {
            Parent root = FXMLLoader.load(getClass().getResource("affichageResultatRechercheTexte.fxml"));
            Stage stage = (Stage) cheminTexte.getScene().getWindow();
            stage.setScene(new Scene(root));
        }
    }
//Ici on permet à l'utilisateur de chercher directement le texte recherché dans les fichiers de l'ordinateur
    public void onBrowseBoutonClick() {
        // Crée un FileChooser
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Choisir un fichier XML");
        fileChooser.setInitialDirectory(new File(System.getProperty("user.home") + "/Téléchargements/PFR2/src/main/resources/texte"));
        // Configure le FileChooser pour n'afficher que les fichiers texte
        FileChooser.ExtensionFilter extFilter =
                new FileChooser.ExtensionFilter("Fichiers XML (*.xml)", "*.xml");
        fileChooser.getExtensionFilters().add(extFilter);

        // Affiche la boîte de dialogue de sélection de fichier et récupère le fichier sélectionné
        Stage stage = new Stage();
        File selectedFile = fileChooser.showOpenDialog(stage);

        // Vérifie si un fichier a été sélectionné, puis affiche son chemin
        if (selectedFile != null) {
            String filePath = selectedFile.getAbsolutePath();
            cheminTexte.setText(filePath);
        }
    }


}
