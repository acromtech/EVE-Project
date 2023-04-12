package com.example.pfr2;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressBar;
import javafx.stage.Stage;

import java.io.IOException;

public class loadingController {

    @FXML
    private ProgressBar load;

    @FXML
    private Label index;

    public void setLoad() throws IOException {
        index.setText("L'indexation est terminée");
        Parent root = FXMLLoader.load(getClass().getResource("modificationAdmin.fxml"));
        Stage stage = (Stage) index.getScene().getWindow();
        stage.setScene(new Scene(root));
    }
}
