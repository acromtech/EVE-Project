module com.example.pfr2 {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.desktop;


    opens controleur to javafx.fxml;
    exports controleur;
    exports entite;
    opens entite to javafx.fxml;
}