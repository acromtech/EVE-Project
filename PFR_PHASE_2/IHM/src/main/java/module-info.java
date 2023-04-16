module com.example.pfr2 {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.desktop;


    opens controleur to javafx.fxml;
    exports controleur;
    exports Entite;
    opens Entite to javafx.fxml;
}