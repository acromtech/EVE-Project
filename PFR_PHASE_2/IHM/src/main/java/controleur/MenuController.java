package controleur;
//le menu propose à l'utilisateur trois types de recherche: texte audio image, à la suite de ça
//l'utilisateur est redirigé sur les possibilités de recherche de chacune de ces trois possibilités

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.ImageView;
import javafx.stage.Stage;

import java.io.IOException;

public class MenuController {

    @FXML
    public ImageView attention;
    public Label error;
    @FXML
    Button texte, image, audio, admin, retour;

//envoie sur les différents moyens de recherche texte: mot clés ou texte
    public void onTexteButtonClick() throws IOException {

        Parent root = FXMLLoader.load(getClass().getResource("choixRechercheTexte.fxml"));
        Stage stage = (Stage) texte.getScene().getWindow();
        stage.setScene(new Scene(root));
    }
//cette fonction permet à l'utilisateur d'ouvrir l'historique de ses recherches sur une nouvelle fenêtre
//il peut alors effectuer ses recherches en voyant les anciens résultats

    public void onHistoriqueButtonClick() throws IOException {
        Stage stage = new Stage();
        Parent root = FXMLLoader.load(getClass().getResource("historique.fxml"));
        Scene scene = new Scene(root, stage.getX(), stage.getY());
        stage.setTitle("Historique");
        stage.setScene(scene);
        stage.show();
        stage.setResizable(false);

    }

//cette fonction permet d'amener l'utilisateur sur la page modification administrateur lorsque l'on clique sur le bouton
//admin

    @FXML
    private void onAdminButtonClick() throws IOException {
        if (MenuMultiMoteurController.getChoixMoteur() != 2) {
            Parent root = FXMLLoader.load(getClass().getResource("login.fxml"));
            Stage stage = (Stage) admin.getScene().getWindow();
            stage.setScene(new Scene(root));
        } else {
            attention.setVisible(true);
            error.setText("Configuration indisponible en mode Multimoteur, Retournez en arrière et selectionnez un moteur à configurer");
        }

    }
//envoie sur les différents moyens de recherche image: couleur ou chemin image

    public void onImageButtonClick() throws IOException {

        Parent root = FXMLLoader.load(getClass().getResource("choixRechercheImage.fxml"));
        Stage stage = (Stage) image.getScene().getWindow();
        stage.setScene(new Scene(root));
    }

    //envoie sur la recherche audio
    public void onAudioButtonClick() throws IOException {

        Parent root = FXMLLoader.load(getClass().getResource("choixRechercheAudio.fxml"));
        Stage stage = (Stage) audio.getScene().getWindow();
        stage.setScene(new Scene(root));

    }
//renvoie à la fenêtre précédente, au choix di moteur de recherche
    @FXML
    public void onRetourButtonClick() throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("menuMultiMoteur.fxml"));
        Stage stage = (Stage) retour.getScene().getWindow();
        stage.setScene(new Scene(root));
    }

}