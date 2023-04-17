package controleur;
//affiche les résultats de la recherche image en permettant à l'utilisateur d'agrandir les images qui l'intéresse parmis
//les résultats
//affiche le score et le nom de l'image

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;

public class AffichageResultatRechercheImageController {
    private final String filename1 = "27.jpg";
    private final String filename2 = "18.jpg";
    private final String filename3 = "37.jpg";
    private final String filename4 = "25.jpg";
    private final String filename5 = "01.jpg";
    private final String filename6 = "";
    private final String filename7 = "";
    private final String filename8 = "";
    @FXML
    private VBox VboxPremierPlan;
    @FXML
    private ImageView image1, image2, image3, image4, image5, image6, image7, image8, image9;
    @FXML
    private Label score1, score2, score3, score4, score5, score6, score7, score8;
    @FXML
    private Label titre1, titre2, titre3, titre4, titre5, titre6, titre7, titre8, texteAide;
    @FXML
    private Button retour;

    @FXML
    public void onRetourButtonClick() throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("rechercheImage.fxml"));
        Stage stage = (Stage) retour.getScene().getWindow();
        stage.setScene(new Scene(root));
    }

    @FXML
    public void onChangeTexteAide(){
        texteAide.setText("(Aide cliquez sur l'image pour la fermer)");
    }

    @FXML
    public void onBaseTexteAide(){
        texteAide.setText("(Aide cliquez sur l'image pour l'afficher en grand)");
    }

    //résultats qui vont être affichés
    @FXML
    public void onAfficheImage() throws IOException {
        File dir1 = new File("src/main/resources/images/JPG/" + filename1);
        File dir2 = new File("src/main/resources/images/JPG/" + filename2);
        File dir3 = new File("src/main/resources/images/JPG/" + filename3);
        File dir4 = new File("src/main/resources/images/JPG/" + filename4);
        File dir5 = new File("src/main/resources/images/JPG/" + filename5);
        File dir6 = new File("src/main/resources/images/JPG/" + filename6);
        File dir7 = new File("src/main/resources/images/JPG/" + filename7);
        File dir8 = new File("src/main/resources/images/JPG/" + filename8);

        Image img1 = new Image(dir1.toURI().toURL().toExternalForm());
        Image img2 = new Image(dir2.toURI().toURL().toExternalForm());
        Image img3 = new Image(dir3.toURI().toURL().toExternalForm());
        Image img4 = new Image(dir4.toURI().toURL().toExternalForm());
        Image img5 = new Image(dir5.toURI().toURL().toExternalForm());
        Image img6 = new Image(dir6.toURI().toURL().toExternalForm());
        Image img7 = new Image(dir7.toURI().toURL().toExternalForm());
        Image img8 = new Image(dir8.toURI().toURL().toExternalForm());

        image1.setImage(img1);
        image2.setImage(img2);
        image3.setImage(img3);
        image4.setImage(img4);
        image5.setImage(img5);
        image6.setImage(img6);
        image7.setImage(img7);
        image8.setImage(img8);

        titre1.setText("27.jpg");
        titre2.setText("18.jpg");
        titre3.setText("37.jpg");
        titre4.setText("25.jpg");
        titre5.setText("01.jpg");
        score1.setText("100%");
        score2.setText("15%");
        score3.setText("10%");
        score4.setText("9%");
        score5.setText("9%");
    }

    //agrandissement de l'image lorsque l'on "clique" dessus
    @FXML
    void onOuvreImage1() throws IOException {
        File dir1 = new File("src/main/resources/images/JPG/" + filename1);
        Image img1 = new Image(dir1.toURI().toURL().toExternalForm());
        VboxPremierPlan.toBack();
        image9.toFront();
        image9.setVisible(true);
        image9.setImage(img1);
    }

    @FXML
    void onOuvreImage2() throws IOException {
        File dir1 = new File("src/main/resources/images/JPG/" + filename2);
        Image img1 = new Image(dir1.toURI().toURL().toExternalForm());
        VboxPremierPlan.toBack();
        image9.toFront();
        image9.setVisible(true);
        image9.setImage(img1);
    }

    @FXML
    void onOuvreImage3() throws IOException {
        File dir1 = new File("src/main/resources/images/JPG/" + filename3);
        Image img1 = new Image(dir1.toURI().toURL().toExternalForm());
        VboxPremierPlan.toBack();
        image9.toFront();
        image9.setVisible(true);
        image9.setImage(img1);
    }

    @FXML
    void onOuvreImage4() throws IOException {
        File dir1 = new File("src/main/resources/images/JPG/" + filename4);
        Image img1 = new Image(dir1.toURI().toURL().toExternalForm());
        VboxPremierPlan.toBack();
        image9.toFront();
        image9.setVisible(true);
        image9.setImage(img1);
    }

    @FXML
    void onOuvreImage5() throws IOException {
        File dir1 = new File("src/main/resources/images/JPG/" + filename5);
        Image img1 = new Image(dir1.toURI().toURL().toExternalForm());
        VboxPremierPlan.toBack();
        image9.toFront();
        image9.setVisible(true);
        image9.setImage(img1);
    }

    @FXML
    void onOuvreImage6() throws IOException {
        File dir1 = new File("src/main/resources/images/JPG/" + filename6);
        Image img1 = new Image(dir1.toURI().toURL().toExternalForm());
        VboxPremierPlan.toBack();
        image9.toFront();
        image9.setVisible(true);
        image9.setImage(img1);
    }

    @FXML
    void onOuvreImage7() throws IOException {
        File dir1 = new File("src/main/resources/images/JPG/" + filename7);
        Image img1 = new Image(dir1.toURI().toURL().toExternalForm());
        VboxPremierPlan.toBack();
        image9.toFront();
        image9.setVisible(true);
        image9.setImage(img1);
    }

    @FXML
    void onOuvreImage8() throws IOException {
        File dir1 = new File("src/main/resources/images/JPG/" + filename8);
        Image img1 = new Image(dir1.toURI().toURL().toExternalForm());
        VboxPremierPlan.toBack();
        image9.toFront();
        image9.setVisible(true);
        image9.setImage(img1);
    }

    @FXML
    void onFermeImage(){
        image9.setVisible(false);
        image9.toBack();
        VboxPremierPlan.toFront();
    }
}

