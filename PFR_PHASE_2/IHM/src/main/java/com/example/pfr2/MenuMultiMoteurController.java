package com.example.pfr2;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.stage.Stage;

import java.io.IOException;

public class MenuMultiMoteurController {
private static int choixMoteur=0;

    @FXML
    Button moteurCreatif, multiMoteur, moteurPrecision;

    public void onMoteurCreatifButtonClick() throws IOException {

        Parent root = FXMLLoader.load(getClass().getResource("menu.fxml"));
        Stage stage = (Stage) moteurCreatif.getScene().getWindow();
        choixMoteur = 1;
        stage.setScene(new Scene(root));
    }

    public void onMultiMoteurButtonClick() throws IOException {

        Parent root = FXMLLoader.load(getClass().getResource("menu.fxml"));
        Stage stage = (Stage) multiMoteur.getScene().getWindow();
        choixMoteur=2;
        stage.setScene(new Scene(root));
    }

    @FXML
    private void onMoteurPrecisionButtonClick() throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("menu.fxml"));
        Stage stage = (Stage) moteurPrecision.getScene().getWindow();
        choixMoteur=3;
        stage.setScene(new Scene(root));
    }

    public static int getChoixMoteur(){
        return choixMoteur;
    }
}