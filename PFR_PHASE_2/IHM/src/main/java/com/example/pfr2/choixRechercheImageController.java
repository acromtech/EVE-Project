package com.example.pfr2;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.stage.Stage;

public class choixRechercheImageController {

    @FXML
    private Button couleur;
    @FXML
    private Button similitude,retour;

    public void onCouleurButtonClick() throws Exception {

        Parent root = FXMLLoader.load(getClass().getResource("rechercheCouleur.fxml"));
        Stage stage = (Stage) couleur.getScene().getWindow();
        stage.setScene(new Scene(root));
    }



    public void onSimilitudeButtonClick() throws Exception {

        Parent root = FXMLLoader.load(getClass().getResource("rechercheImage.fxml"));
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