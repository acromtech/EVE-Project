package controleur;
//permet de lancer l'interface
import javafx.application.Application;
import javafx.event.EventHandler;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;

import java.io.IOException;

public class HelloApplication extends Application {
    public static void main(String[] args) {
        launch();
    }

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
                System.out.println("L'application est fermée");
                System.exit(0);
            }
        });
    }
}