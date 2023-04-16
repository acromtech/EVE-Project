package controleur;
//choix de la recherche voulu pour l'image: couleur ou chemin de l'image
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.stage.Stage;

public class ChoixRechercheImageController {

    @FXML
    private Button couleur;
    @FXML
    private Button similitude, retour;
//lance la recherche avec couleur
    public void onCouleurButtonClick() throws Exception {

        Parent root = FXMLLoader.load(getClass().getResource("rechercheCouleur.fxml"));
        Stage stage = (Stage) couleur.getScene().getWindow();
        stage.setScene(new Scene(root));
    }

//lance la recherche image
    public void onSimilitudeButtonClick() throws Exception {

        Parent root = FXMLLoader.load(getClass().getResource("rechercheImage.fxml"));
        Stage stage = (Stage) similitude.getScene().getWindow();
        stage.setScene(new Scene(root));
    }

//renvoie à la page précédente: menu
    @FXML
    public void onRetourButtonClick() throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("menu.fxml"));
        Stage stage = (Stage) retour.getScene().getWindow();
        stage.setScene(new Scene(root));
    }

}