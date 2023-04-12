package com.example.pfr2;

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
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;

public class affichageResultatRechercheMotClesController {


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
                System.out.println(clicked.getNumero());
                System.out.println(clicked.getTitre());
                System.out.println(clicked.getResultat());
                System.out.println(clicked.getChemin());


                Stage stage = new Stage();
                stage.setResizable(false);

                // Crée un composant TextArea pour afficher le contenu du fichier
                TextArea textArea = new TextArea();

                // Crée une mise en page et y ajoute le composant TextArea
                StackPane root = new StackPane();
                root.getChildren().add(textArea);

                // Configure la fenêtre principale (Stage) et y ajoute la mise en page
                stage.setTitle("Affichage Texte");
                stage.setScene(new Scene(root, 750, 750));

                // Chemin du fichier à ouvrir
                String filePath = "/home/bast4722/files.txt";

                // Lit les données du fichier et les affiche dans le composant TextArea
                try (Scanner scanner = new Scanner(new File(filePath))) {
                    StringBuilder sb = new StringBuilder();
                    while (scanner.hasNextLine()) {
                        sb.append(scanner.nextLine()).append("\n");
                    }
                    textArea.setText(sb.toString());
                } catch (FileNotFoundException e) {
                    e.printStackTrace();
                }

                // Affiche la fenêtre principale
                stage.show();
            }
        }
    }

    private void setupTable() {
        Resultat histos0 = new Resultat(1, "06-Les_mauvais_comptes_d_une_Θlimination", "20", "../BaseFichiersTexte/06-Les_mauvais_comptes_d_une_Θlimination.xml");
        Resultat histos1 = new Resultat(2, "22-Ted_Stanger,_l_AmΘricain_de_service", "13", "../BaseFichiersTexte/22-Ted_Stanger,_l_AmΘricain_de_service.xml");
        Resultat histos2 = new Resultat(3, "27-Le_Stade_de_France_s_ouvre", "11", "../BaseFichiersTexte/27-Le_Stade_de_France_s_ouvre.xml");
        Resultat histos3 = new Resultat(4, "17-De_la_difficultΘ_d_anticiper_les", "9", "../BaseFichiersTexte/17-De_la_difficultΘ_d_anticiper_les.xml");
        Resultat histos4 = new Resultat(4, "15-_Si_on_veut_aller_trop", "8", "../BaseFichiersTexte/15-_Si_on_veut_aller_trop.xml");
        resultatMotCles.getItems().addAll(histos0, histos1, histos2, histos3, histos4);
    }
}