package controleur;
//enregistrer les recherches effectuées dans l'historique pour permettre à l'utilisateur de
//les visualiser
//l'historique est composé de la date de la recherche, ses résultats et son titre

import entite.Historique;
import javafx.fxml.FXML;
import javafx.scene.control.TableCell;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;

public class HistoriqueController {

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
        if (event.getClickCount() != 1 && event.getTarget() instanceof TableCell) {
            // Ne rien faire si l'utilisateur a cliqué sur le bandeau de la TableView
            Historique clicked = histo.getSelectionModel().getSelectedItem();
            if (clicked != null) {
                System.out.println(clicked.getTitre());
                System.out.println(clicked.getDate());
                System.out.println(clicked.getResultat());
            }
        }
    }

    private void setupTable() {
        Historique histos0 = new Historique("1", "jingle.wav", "corpus.wav = 29s");
        Historique histos1 = new Historique("2", "27.jpg", "27.jpeg = 100%");
        Historique histos2 = new Historique("3", "violet", "34.jpeg = 9%");
        Historique histos3 = new Historique("4", "../BaseFichiersTexte/27-Le_Stade_de_France_s_ouvre.xml", "06-Les_mauvais_comptes_d_une_Θlimination.xml = 16,333332%");
        Historique histos4 = new Historique("5", "+france-football", "06-Les_mauvais_comptes_d_une_Θlimination.xml = 20");
        histo.getItems().addAll(histos0, histos1, histos2, histos3, histos4);
    }
}