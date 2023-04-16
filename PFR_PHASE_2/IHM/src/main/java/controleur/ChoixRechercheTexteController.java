package controleur;
//phase de choix pour l'utilisateur, il peut choisir texte ou mot clés
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.stage.Stage;

public class ChoixRechercheTexteController {


    @FXML
    private Button similitude, retour, mot_cles;
//lance la recherche mot clés
    public void onMotClesButtonClick() throws Exception {

        Parent root = FXMLLoader.load(getClass().getResource("rechercheMotCles.fxml"));
        Stage stage = (Stage) mot_cles.getScene().getWindow();
        stage.setScene(new Scene(root));
    }

//lance la recherche avec un chemin texte
    public void onSimilitudeButtonClick() throws Exception {

        Parent root = FXMLLoader.load(getClass().getResource("rechercheTexte.fxml"));
        Stage stage = (Stage) similitude.getScene().getWindow();
        stage.setScene(new Scene(root));
    }

//renvoie à la page précédente ici: menu
    @FXML
    public void onRetourButtonClick() throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("menu.fxml"));
        Stage stage = (Stage) retour.getScene().getWindow();
        stage.setScene(new Scene(root));
    }

}