//POSSIBILITE 1 + PERFORMANT CAR PAS BESOIN DE SE RECONNECTER AU BUS
    //On demarre le prog C avec les param ./main
    //Trame RX TYPE_TRAITEMENT (REQUETE) -> C RENVOI UN ACK A LA FIN DU TRAITEMENT
    //Trame RX SCORE+CHEMIN -> C RENVOI LES DATA
    //Trame RX SCORE+CHEMIN -> C RENVOI UN ACK (CAR PLUS DE DONNES)

    //BONUS : WATCHDOG
    //Trame RX toute les n ms

    enum Address{
        CONNECTED           (0x01), 
        INDEXATION_TEXTE    (0x10), //(TX_FRAME) Demande l'indexation des données textuelles (+ ACK)
        INDEXATION_IMAGE    (0x11), //(TX_FRAME) Demande l'indexation des données photographique (+ ACK)
        INDEXATION_SON      (0x12), //(TX_FRAME) Demande l'indexation des données sonores (+ ACK)
        INDEXATION_ALL      (0x13), //(TX_FRAME) Demande l'indexation de toutes les données (+ ACK)
        TEXTE_MOTCLE        (0x20), //(TX_FRAME) Demande de réaliser une recherche textuelle par mot clé (+ ACK)
        TEXTE_FICHIER       (0x21), //(TX_FRAME) Demande de réaliser une recherche textuelle par fichier (+ ACK)
        IMAGE_MOTCLE        (0x30), //(TX_FRAME) Demande de réaliser une recherche photographique par mot clé (+ ACK)
        IMAGE_FICHIER       (0x31), //(TX_FRAME) Demande de réaliser une recherche photographique par fichier (+ ACK) 
        SON_FICHIER         (0x40), //(TX_FRAME) Demande de réaliser une recherche sonore par fichier (+ ACK)
        SCORE_CHEMIN        (0x50), //(RX_FRAME) Récupère les données de résulats
        STOP_BUS            (0x60); //(TX_FRAME) Ordonne l'arret de la connection au bus virtuel (+ ACK)
        
        private final int value;
        
        Address(int value) {
            this.value = value;
        }
        
        public int getValue() {
            return value;
        }
        
        }
