package controleur;
//permet de chercher une image en rentrant la couleur prédominante

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

public class RechercheCouleurController {

    @FXML
    private TextField couleur;
    @FXML
    private Button retour, search;

    //lance la recherche
    @FXML
    public void onSearchButtonClick() throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("affichageResultatRechercheCouleur.fxml"));
        Stage stage = (Stage) search.getScene().getWindow();
        stage.setScene(new Scene(root));
    }

    //revient à la page précédente
    @FXML
    public void onRetourButtonClick() throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("choixRechercheImage.fxml"));
        Stage stage = (Stage) retour.getScene().getWindow();
        stage.setScene(new Scene(root));
    }

    //permet de lancer la recherche grâce à la touche "entrée" du clavier
    @FXML
    public void onEnterAction(KeyEvent keyEvent) throws IOException {
        if (keyEvent.getCode().equals(KeyCode.ENTER)) {
            Parent root = FXMLLoader.load(getClass().getResource("affichageResultatRechercheCouleur.fxml"));
            Stage stage = (Stage) couleur.getScene().getWindow();
            stage.setScene(new Scene(root));
        }
    }

    //paramètre la barre de recherche à la couleur "violet"
    @FXML
    public void onVioletButtonClick(){
        couleur.setText("violet");
    }

    //paramètre la barre de recherche à la couleur "orange"
    @FXML
    public void onOrangeButtonClick(){
        couleur.setText("orange");
    }

    //paramètre la barre de recherche à la couleur "ardoise"
    @FXML
    public void onArdoiseButtonClick(){
        couleur.setText("ardoise");
    }

    //paramètre la barre de recherche à la couleur "corail"
    @FXML
    public void onCorailButtonClick(){
        couleur.setText("corail");
    }

    //paramètre la barre de recherche à la couleur "cyan"
    @FXML
    public void onCyanButtonClick(){
        couleur.setText("cyan");
    }

    //paramètre la barre de recherche à la couleur "kaki"
    @FXML
    public void onKakiButtonClick(){
        couleur.setText("kaki");
    }

    //paramètre la barre de recherche à la couleur "jaune"
    @FXML
    public void onJauneButtonClick(){
        couleur.setText("jaune");
    }
}

