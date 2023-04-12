package com.example.pfr2;

import javafx.fxml.FXML;
import javafx.scene.Node;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;

public class HistoriqueController{

    @FXML
    private TableColumn<Historique, String> date;

    @FXML
    private TableColumn<Historique, String> resultat;

    @FXML
    private TableColumn<Historique, String> titre;

    @FXML
    private TableView<Historique> histo;



    public void initialize() {
                date.setCellValueFactory(new PropertyValueFactory<Historique, String>("date"));
                titre.setCellValueFactory(new PropertyValueFactory<Historique, String>("titre"));
                resultat.setCellValueFactory(new PropertyValueFactory<Historique, String>("resultat"));
                setupTable();
    }


    @FXML
    public void rowClicked(MouseEvent event) {

        Historique clicked = histo.getSelectionModel().getSelectedItem();
        if(!clicked.equals("")){
            System.out.println(String.valueOf(clicked.getTitre()));
            System.out.println(String.valueOf(clicked.getDate()));
            System.out.println(String.valueOf(clicked.getResultat()));
        }
    }

    private void setupTable(){
            Historique histos0 = new Historique("1","jingle.wav","corpus.wav = 29s");
            Historique histos1 = new Historique("2","27.jpg","27.jpeg = 100%");
            Historique histos2 = new Historique("3","violet","34.jpeg = 9%");
            Historique histos3 = new Historique("4","../BaseFichiersTexte/27-Le_Stade_de_France_s_ouvre.xml","06-Les_mauvais_comptes_d_une_Θlimination = 16,333332%");
            Historique histos4 = new Historique("5","+france-football","06-Les_mauvais_comptes_d_une_Θlimination.xml = 20");
            histo.getItems().addAll(histos0,histos1,histos2,histos3);
    }
}