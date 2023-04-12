package com.example.pfr2;

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
    Button texte,image,audio,admin,retour;
    @FXML
    public ImageView attention;
    public Label error;
    public void onTexteButtonClick() throws IOException {

        Parent root = FXMLLoader.load(getClass().getResource("choixRechercheTexte.fxml"));
        Stage stage = (Stage) texte.getScene().getWindow();
        stage.setScene(new Scene(root));
    }
    public void onHistoriqueButtonClick() throws IOException {
        Stage stage= new Stage();
        Parent root = FXMLLoader.load(getClass().getResource("historique.fxml"));
        Scene scene = new Scene(root, stage.getX(), stage.getY());
        stage.setTitle("Historique");
        stage.setScene(scene);
        stage.show();
        stage.setResizable(false);

    }


    @FXML
    private void onAdminButtonClick() throws IOException {
        if (MenuMultiMoteurController.getChoixMoteur() != 2) {
            Parent root = FXMLLoader.load(getClass().getResource("login.fxml"));
            Stage stage = (Stage) admin.getScene().getWindow();
            stage.setScene(new Scene(root));
        }else{ attention.setVisible(true);
            error.setText("Configuration indisponible en mode Multimoteur, Retournez en arrière et selectionnez un moteur à configurer");
        }

    }
    public void onImageButtonClick() throws IOException {

        Parent root = FXMLLoader.load(getClass().getResource("choixRechercheImage.fxml"));
        Stage stage = (Stage) image.getScene().getWindow();
        stage.setScene(new Scene(root));
    }


    public void onAudioButtonClick() throws IOException {

        Parent root = FXMLLoader.load(getClass().getResource("choixRechercheAudio.fxml"));
        Stage stage = (Stage) audio.getScene().getWindow();
        stage.setScene(new Scene(root));

        }

    @FXML
    public void onRetourButtonClick() throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("menuMultiMoteur.fxml"));
        Stage stage = (Stage) retour.getScene().getWindow();
        stage.setScene(new Scene(root));
    }

}