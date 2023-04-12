module com.example.pfr2 {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.desktop;


    opens com.example.pfr2 to javafx.fxml;
    exports com.example.pfr2;
}