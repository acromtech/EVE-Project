package controleur;
//choix recherche audio: similitude
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.stage.Stage;

public class ChoixRechercheAudioController {
    @FXML
    Button retour, similitude;
//renvoie au menu
    public void onRetourButtonClick() throws Exception {

        Parent root = FXMLLoader.load(getClass().getResource("menu.fxml"));
        Stage stage = (Stage) retour.getScene().getWindow();
        stage.setScene(new Scene(root));
    }
//amène à la recherche audio
    public void onSimilitudeButtonClick() throws Exception {

        Parent root = FXMLLoader.load(getClass().getResource("rechercheAudio.fxml"));
        Stage stage = (Stage) retour.getScene().getWindow();
        stage.setScene(new Scene(root));
    }
}
