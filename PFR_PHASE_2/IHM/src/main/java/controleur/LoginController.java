package controleur;
//controler la connexion administrateur: identifianr et mot de passe
import Entite.BDconfig;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.image.ImageView;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;

public class LoginController {
    private static int cpt = 3;
    private final BDconfig bDconfig = BDconfig.getInstance();
    private final File pathConfigMoteur1 = new File("PFR_partie1/Configuration/.config");
    private final File pathmdp = new File("motdePasse/.mdp");
    @FXML
    private TextField id;

    @FXML
    private PasswordField mdp;

    @FXML
    private Button retour;

    @FXML
    private Button valider;

    @FXML
    private Label error;

    @FXML
    private ImageView attention;

//renvoie au menu
    @FXML
    public void onRetourButtonClick() throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("menu.fxml"));
        Stage stage = (Stage) retour.getScene().getWindow();
        stage.setScene(new Scene(root));
        cpt = 3;
    }

//permet de valider la saisie du mdp avec la touche "entrée" du clavier
    @FXML
    public void onEnterAction(KeyEvent keyEvent) throws IOException {
        if (keyEvent.getCode().equals(KeyCode.ENTER)) {
            cpt--;
            loginAdmin(cpt);
            if (cpt == 0) {
                Parent root = FXMLLoader.load(getClass().getResource("menu.fxml"));
                Stage stage = (Stage) mdp.getScene().getWindow();
                stage.setScene(new Scene(root));
                cpt = 3;
            }
        }
    }
//valider le mdp
    public void onClickButtonValid() throws IOException {
        cpt--;
        loginAdmin(cpt);
        if (cpt == 0) {
            Parent root = FXMLLoader.load(getClass().getResource("menu.fxml"));
            Stage stage = (Stage) valider.getScene().getWindow();
            stage.setScene(new Scene(root));
            cpt = 3;
        }
    }
//vérification de la validité de l'identifiant et du mdp
    @FXML
    public void loginAdmin(int cpt) throws IOException {
        String identifiant;
        String motDePasse;

        identifiant = id.getText().trim();
        motDePasse = mdp.getText().trim();
        if (isValidAdmin(identifiant, motDePasse)) {
            Parent root = FXMLLoader.load(getClass().getResource("modificationAdmin.fxml"));
            Stage stage = (Stage) valider.getScene().getWindow();
            stage.setScene(new Scene(root));

        } else {
            attention.setVisible(true);
            error.setText(" Mot de passe ou Identifiant incorrect, il vous reste " + cpt + " tentantive(s) !!! ");
            id.setText("");
            mdp.setText("");
        }
    }

    private boolean isValidAdmin(String identifiant, String motDePasse) {

        return identifiant.equals("Admin") && motDePasse.equals(bDconfig.getmdp());
    }


}
