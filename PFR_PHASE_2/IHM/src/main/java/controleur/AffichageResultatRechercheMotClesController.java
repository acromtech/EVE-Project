package controleur;
//affiche les résultats de la recherche mot clés du texte
import Entite.OpenFile;
import Entite.Resultat;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;

import java.io.File;
import java.io.IOException;

public class AffichageResultatRechercheMotClesController {


    @FXML
    private Button retour;

    @FXML
    private TableColumn<Resultat, Integer> numero;

    @FXML
    private TableColumn<Resultat, String> chemin;

    @FXML
    private TableColumn<Resultat, String> resultat;

    @FXML
    private TableColumn<Resultat, String> titre;

    @FXML
    private TableView<Resultat> resultatMotCles;

    @FXML
    public void onRetourButtonClick() throws IOException {
        Parent root = FXMLLoader.load(getClass().getResource("rechercheMotCles.fxml"));
        Stage stage = (Stage) retour.getScene().getWindow();
        stage.setScene(new Scene(root));
    }


    public void initialize() {
        numero.setCellValueFactory(new PropertyValueFactory<Resultat, Integer>("numero"));
        titre.setCellValueFactory(new PropertyValueFactory<Resultat, String>("titre"));
        resultat.setCellValueFactory(new PropertyValueFactory<Resultat, String>("resultat"));
        chemin.setCellValueFactory(new PropertyValueFactory<Resultat, String>("chemin"));
        setupTable();
    }


    @FXML
    public void rowClicked(MouseEvent event) {
        if (event.getClickCount() != 1 && event.getTarget() instanceof TableCell) {
            // Ne rien faire si l'utilisateur a cliqué sur le bandeau de la TableView
            Resultat clicked = resultatMotCles.getSelectionModel().getSelectedItem();
            if (clicked != null) {
                String titre = clicked.getTitre();
                String filename = clicked.getChemin();
                File file = new File(filename);
                String result = OpenFile.openFile(file.getAbsolutePath());
                System.out.println(file.getAbsolutePath());
                Stage stage = new Stage();

                // Crée un composant TextArea pour afficher le contenu du fichier
                TextArea textArea = new TextArea();

                // Crée une mise en page et y ajoute le composant TextArea
                StackPane root = new StackPane();
                root.getChildren().add(textArea);

                // Configure la fenêtre principale (Stage) et y ajoute la mise en page
                stage.setTitle(titre);
                stage.setScene(new Scene(root, 750, 750));
                textArea.setText(result);
                stage.show();

            }
        }
    }
//résultats qui vont être affichés
    private void setupTable() {
        Resultat histos0 = new Resultat(1, "06-Les_mauvais_comptes_d_une_Θlimination.xml", "20", "src/main/resources/texte/06-Les_mauvais_comptes_d_une_Θlimination.xml");
        Resultat histos1 = new Resultat(2, "22-Ted_Stanger,_l_AmΘricain_de_service.xml", "13", "src/main/resources/texte/22-Ted_Stanger,_l_AmΘricain_de_service.xml");
        Resultat histos2 = new Resultat(3, "27-Le_Stade_de_France_s_ouvre.xml", "11", "src/main/resources/texte/27-Le_Stade_de_France_s_ouvre.xml");
        Resultat histos3 = new Resultat(4, "17-De_la_difficultΘ_d_anticiper_les.xml", "9", "src/main/resources/texte/17-De_la_difficultΘ_d_anticiper_les.xml");
        Resultat histos4 = new Resultat(5, "15-_Si_on_veut_aller_trop.xml", "8", "src/main/resources/texte/15-_Si_on_veut_aller_trop.xml");
        resultatMotCles.getItems().addAll(histos0, histos1, histos2, histos3, histos4);
    }
}