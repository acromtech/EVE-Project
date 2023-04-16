package controleur;

//Recherche d'un texte par mot clés (simple ou complex)
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextField;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.stage.Stage;

import java.io.IOException;

public class RechercheMotClesController {
//TextField pour permettre à l'utilisateur de rentrer ses mot clés
    @FXML
    private TextField cheminMotCles;

    @FXML
    private Button retour, search;
//Lancer la recherche
    @FXML
    public void onSearchButtonClick() throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("affichageResultatRechercheMotCles.fxml"));
        Stage stage = (Stage) search.getScene().getWindow();
        stage.setScene(new Scene(root));
    }
//Renvoie à la page d'avant
    @FXML
    public void onRetourButtonClick() throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("choixRechercheTexte.fxml"));
        Stage stage = (Stage) retour.getScene().getWindow();
        stage.setScene(new Scene(root));
    }
//Permet de valider la recherche grâce à la touche "entrée"
    @FXML
    public void onEnterAction(KeyEvent keyEvent) throws IOException {
        if (keyEvent.getCode().equals(KeyCode.ENTER)) {
            Parent root = FXMLLoader.load(getClass().getResource("affichageResultatRechercheMotCles.fxml"));
            Stage stage = (Stage) cheminMotCles.getScene().getWindow();
            stage.setScene(new Scene(root));
        }
    }
}
