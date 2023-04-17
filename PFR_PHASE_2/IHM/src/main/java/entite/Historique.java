package entite;

public class Historique {
        private String date;
        private String titre;
        private String resultat;

        public Historique(String date, String titre, String resultat) {
            this.date = date;
            this.titre = titre;
            this.resultat = resultat;
        }

        public String getDate() {
            return date;
        }

        public String getTitre() {
            return titre;
        }

        public String getResultat() {
            return resultat;
        }

        public void setDate(String date) {
            this.date = date;
        }

        public void setTitre(String titre) {
            this.titre = titre;
        }

        public void setResultat(String resultat) {
            this.resultat = resultat;
        }

        @Override
        public String toString() {
            return "Historique{" +
                    "date=" + date +
                    ", titre='" + titre + '\'' +
                    ", resultat='" + resultat + '\'' +
                    '}';
        }
    }
