package controleur;
//permet de modifer les paramètres accessibles par l'administrateur

import entite.BDconfig;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.image.ImageView;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;
import java.util.HashMap;

public class ModificationAdminController {

    private final BDconfig bDconfig = BDconfig.getInstance();
    private final File pathConfigMoteur1 = new File("PFR_partie1/Configuration/.config");
    private final File pathConfigMoteur2 = new File("PFR_partie1/Configuration/.config2");
    private final File pathmdp = new File("motdePasse/.mdp");
    private final HashMap<String, String> maHashMap = new HashMap<>();
    @FXML
    private Label error;
    @FXML
    private ImageView attention;
    @FXML
    private CheckBox ferme;
    @FXML
    private TextField indexM;
    @FXML
    private TextField indexN;
    @FXML
    private Button indexerBase;
    @FXML
    private PasswordField mdp;
    @FXML
    private TextField nbListe;
    @FXML
    private CheckBox ouvert;
    @FXML
    private Button retour;
    @FXML
    private TextField seuilAudio;
    @FXML
    private TextField seuilTexte;
    @FXML
    private String index1;
    @FXML
    private String index2;
    @FXML
    private String seuilA;
    @FXML
    private String nbL;
    @FXML
    private String seuilT;
    @FXML
    private String motdePasse, savmdp;

    public void onRetourButtonClick() throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("menu.fxml"));
        Stage stage = (Stage) retour.getScene().getWindow();
        stage.setScene(new Scene(root));
    }

    //permet de sauvegarder les paramètres modififiés
    public void onSauvegardeButtonClick(){

        switch (MenuMultiMoteurController.getChoixMoteur()) {
            //choix moteur créatif TODO
            case 1:
                maHashMap.put("indexationAudioN", index1);
                maHashMap.put("indexationAudioM", index2);
                maHashMap.put("seuil", seuilA);
                maHashMap.put("nbListe", nbL);
                maHashMap.put("seuilMotSignificatif", seuilT);
                bDconfig.multiUpdateConfig(maHashMap, pathConfigMoteur1);
                break;
            //choix moteur précision TODO
            case 3:
                maHashMap.put("indexationAudioN", index1);
                maHashMap.put("indexationAudioM", index2);
                maHashMap.put("seuil", seuilA);
                maHashMap.put("nbListe", nbL);
                maHashMap.put("seuilMotSignificatif", seuilT);
                bDconfig.multiUpdateConfig(maHashMap, pathConfigMoteur2);
                break;
        }
        savmdp = mdp.getText().trim();
        if (!savmdp.equals("")) {
            motdePasse = mdp.getText().trim();
            bDconfig.updateConfig("motdePasse", motdePasse, pathmdp);
        }
        error.setText("Sauvegarde effectué");
    }

    //cette fonction permet de lancer l'indexation
    public void onIndexationButtonClick() throws Exception {
        Parent root = FXMLLoader.load(getClass().getResource("loading.fxml"));
        Stage stage = (Stage) retour.getScene().getWindow();
        stage.setScene(new Scene(root));
    }

    //cette fonction permet de supprimer les bases descripteurs
    public void onSupprimeButtonClick() throws Exception {
        attention.setVisible(true);
        error.setText("La base a bien été suprimmé");
    }

    //permet de rentrer que des chiffres dans la case mdp
    public void onBlockLetterPassWordField() throws IOException {
        blockLetters(mdp);

    }

    //permet de pouvoir rentrer que des chiffres
    public void onBlockLetterTexteField() throws IOException {
        blockLetters2(seuilAudio);
        blockLetters2(seuilTexte);
        blockLetters2(indexN);
        blockLetters2(indexM);
        blockLetters2(nbListe);
    }

    public void indexMValeur() throws IOException {
        index1 = indexM.getText().trim();
        //Si la case n'est pas vide
        if (!index1.equals("")) {
            //<0
            //Conversion en Int pour comparer
            if (Integer.parseInt(index1) <= 0) {
                attention.setVisible(true);
                indexM.setText("");
                error.setText(" La valeur n'est pas positive !!!");
            }
        }

    }

    public void indexNValeur() throws IOException {

        index2 = indexN.getText().trim();
        //Si la case n'est pas vide
        if (!index2.equals("")) {
            //<0
            //Conversion en Int pour comparer
            if (Integer.parseInt(index2) <= 0) {
                attention.setVisible(true);
                indexN.setText("");
                error.setText(" La valeur n'est pas positive !!!");
            }
        }
    }

    //Rentrer le seuil voulu pour l'audio, un message d'erreur apparaît si la valeur n'est pas comprise entre 0 et 100
    public void seuilAudioValeur() throws IOException {
        seuilA = seuilAudio.getText().trim();
        if (!seuilA.equals("")) {
            //<0 & >100
            if (Integer.parseInt(seuilA) < 0 || Integer.parseInt(seuilA) > 100) {
                attention.setVisible(true);
                seuilAudio.setText("");
                error.setText(" La valeur n'est pas comprise entre 0 et 100 !!!");
            }
        }

    }

    //Rentrer le nombre de valeur désiré, un message d'erreur apparaît si la valeur n'est pas positive
    public void nbListeValeur() throws IOException {
        nbL = nbListe.getText().trim();
        if (!nbL.equals(""))
            //<0
            if (Integer.parseInt(nbL) <= 0 || Integer.parseInt(nbL) > 8) {
                attention.setVisible(true);
                nbListe.setText("");
                error.setText(" La valeur n'est pas positive !!!");
            }

    }

    //Rentrer le seuil voulu pour le texte, un message d'erreur apparaît si la valeur n'est pas comprise entre 2 et 10
    public void seuilTexteValeur() throws IOException {
        seuilT = seuilTexte.getText().trim();
        if (!seuilT.equals("")) {
            //<2 && >=10
            if (Integer.parseInt(seuilT) < 2 || Integer.parseInt(seuilT) >= 10) {
                attention.setVisible(true);
                seuilTexte.setText("");
                error.setText(" La valeur n'est pas comprise entre 2 et 10 !!! ");
            }
        }
    }

    public void handleOuvertBox() {
        if (ouvert.isSelected()) {
            ferme.setSelected(false);
        }
    }

    public void handleFermeBox() {
        if (ferme.isSelected()) {
            ouvert.setSelected(false);
        }
    }

    //Possibilité de rentrer que des chiffres
    public void blockLetters2(TextField texteWordField) {
        texteWordField.setOnKeyTyped(event -> {
            String character = event.getCharacter();
            if (!character.matches("[0-9]")) {
                event.consume();
                attention.setVisible(true);
                texteWordField.setText("");
                error.setText(" Les valeurs ne sont pas correctes, veuillez les modifier et mettre que des chiffres !!! ");
            } else {
                System.out.println(character);
                attention.setVisible(false);
                error.setText("");
            }
        });
    }

    public void blockLetters(PasswordField passwordField) {
        passwordField.setOnKeyTyped(event -> {
            String character = event.getCharacter();
            if (!character.matches("[0-9]")) {
                event.consume();
                attention.setVisible(true);
                passwordField.setText("");
                error.setText(" Les valeurs ne sont pas correcte, veuillez les modifiers et mettre que des chiffres !!! ");
            } else {
                System.out.println(character);
                attention.setVisible(false);
                error.setText("");
            }
        });
    }

    //Permet de rentrer les valeurs selon le moteur sélectionné
    public void setValeur() {
        switch (MenuMultiMoteurController.getChoixMoteur()) {
            //choix moteur créatif TODO
            case 1:

                index1 = bDconfig.getParametre("indexationAudioN", pathConfigMoteur1);
                index2 = bDconfig.getParametre("indexationAudioM", pathConfigMoteur1);
                seuilA = bDconfig.getParametre("seuil", pathConfigMoteur1);
                nbL = bDconfig.getParametre("nbListe", pathConfigMoteur1);
                seuilT = bDconfig.getParametre("seuilMotSignificatif", pathConfigMoteur1);
                motdePasse = bDconfig.getmdp();
                break;
            //choix moteur précision TODO
            case 3:

                index1 = bDconfig.getParametre("indexationAudioN", pathConfigMoteur2);
                index2 = bDconfig.getParametre("indexationAudioM", pathConfigMoteur2);
                seuilA = bDconfig.getParametre("seuil", pathConfigMoteur2);
                nbL = bDconfig.getParametre("nbListe", pathConfigMoteur2);
                seuilT = bDconfig.getParametre("seuilMotSignificatif", pathConfigMoteur2);
                motdePasse = bDconfig.getmdp();
                break;
        }
        mdp.setPromptText(motdePasse);
        indexN.setPromptText(index1);
        indexM.setPromptText(index2);
        seuilAudio.setPromptText(seuilA);
        seuilTexte.setPromptText(seuilT);
        nbListe.setPromptText(nbL);
    }
}
