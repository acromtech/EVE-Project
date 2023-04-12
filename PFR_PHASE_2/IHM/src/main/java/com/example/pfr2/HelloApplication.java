package com.example.pfr2;

import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

import java.io.IOException;

public class HelloApplication extends Application {
    @Override
    public void start(Stage stage) throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(HelloApplication.class.getResource("menuMultiMoteur.fxml"));
        Scene scene = new Scene(fxmlLoader.load(), stage.getX(), stage.getY());
        stage.setTitle("UPSSIWEB");
        stage.setScene(scene);
        stage.show();
        stage.setResizable(false);
        stage.setOnCloseRequest(new EventHandler<WindowEvent>() {
            @Override
            public void handle(WindowEvent e) {
                System.out.println("Slt");
                System.exit(0);
            }
        });
    }

    public static void main(String[] args) {
        launch();
    }
}