package com.example.pfr2;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.stage.Stage;

public class choixRechercheTexteController {


    @FXML
    private Button similitude,retour,mot_cles;

    public void onMotClesButtonClick() throws Exception {

        Parent root = FXMLLoader.load(getClass().getResource("rechercheMotCles.fxml"));
        Stage stage = (Stage) mot_cles.getScene().getWindow();
        stage.setScene(new Scene(root));
    }



    public void onSimilitudeButtonClick() throws Exception {

        Parent root = FXMLLoader.load(getClass().getResource("rechercheTexte.fxml"));
        Stage stage = (Stage) similitude.getScene().getWindow();
        stage.setScene(new Scene(root));
    }


    @FXML
    public void onRetourButtonClick() throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("menu.fxml"));
        Stage stage = (Stage) retour.getScene().getWindow();
        stage.setScene(new Scene(root));
    }

}