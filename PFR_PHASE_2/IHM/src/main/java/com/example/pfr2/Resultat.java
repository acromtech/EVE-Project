package com.example.pfr2;

public class Resultat {
    private String titre;
    private int numero;
    private String chemin;
    private String resultat;

    public Resultat(int numero, String titre, String resultat, String chemin) {
        this.titre = titre;
        this.numero = numero;
        this.chemin = chemin;
        this.resultat = resultat;
    }

    public String getTitre() {
        return titre;
    }

    public int getNumero() {
        return numero;
    }

    public String getChemin() {
        return chemin;
    }

    public void setTitre(String titre) {
        this.titre = titre;
    }

    public void setNumero(int numero) {
        this.numero = numero;
    }

    public void setChemin(String chemin) {
        this.chemin = chemin;
    }

    public void setResultat(String resultat) {
        this.resultat = resultat;
    }

    public String getResultat() {
        return resultat;

    }

    @Override
    public String toString() {
        return "Resultat{" +
                "titre='" + titre + '\'' +
                ", numero=" + numero +
                ", chemin='" + chemin + '\'' +
                ", resultat='" + resultat + '\'' +
                '}';
    }
}
