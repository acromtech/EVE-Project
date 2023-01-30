# PFR-audio 

Dernière update : 27/01/2023

Auteur : **Emilien VESIN, Bastien LALANNE, Flavie THIBAULT, Alexis GIBERT et Mouléro DEGBEGNI**

module : Informatique

## Information
Le menu est une machine à état qui regroupe toutes les fonctionnalités du moteur de recherche.

## Prérequis
* Système d'exploitation : Linux

* Installer VLC

## Utilisation

Pour lancer l'application, il faut ouvrir un terminal et se placer dans le dossier Menu puis faire un make. L'application se lance et on arrive sur le menu principal.

## Notice Utilisateur

L'utilisateur peut alors choisir de se diriger vers le menu utilisateur en entrant 1 pour faire des recherches texte, image ou audio ou de se diriger vers le menu administrateur en tapant 2 pour faire des modifications sur l'application. Il peut aussi fermer l'application en tapant 3.

> ```
> ========================================================
>
> ==============   MENU PRINCIPAL   ======================
>
> ========================================================
>
>
> Selectionez l'opération à réaliser.
> 
>
>		1.  Menu utilisateur.
>
>		2.  Menu d'Administration.
>
>		3.  Fermer l'application.
> ```



### Menu Utilisateur
 
Voici les trois choix que peux réaliser l'utilisateur dans le menu utilisateur, soit une recherche texte en tapant le 2, soir une recherche image en rentrant le 3 soit une recherche audio en saisissant le 4. Il peut aussi à tout moment retourner au menu principal en tapant le 1.

> ```
> ===========================================================
>
> ================   MENU UTILISATEUR   =====================
>
> ===========================================================
>
>
>	Selectionez l'opération à réaliser.
>
>
>		2.  TEXTE.
>
>		3.  IMAGE.
>
>		4.  AUDIO.
>
>
>		1.  Retour.
> ```


#### Recherche Texte

Dans la "recherche texte", l'utilisateur a 2 possibilités majeures : faire une recherche par mot-clé en saisissant 2, faire une recherche par comparaison d'un fichier avec la base en rentrant 3. Il peut aussi à tout moment retourner en arrière en tapant le 1 ou fermer l'application en entrant le 4.

> ```
> ===========================================================
>
> ======================     TEXTE     ======================
>
> ===========================================================
>
>
>		2.  Recherche par mot clé.
>
>		3.  Comparaison d'un fichier à la base.
>
>		4.  Fermer l'application.
>
>
>		1.  Retour.
> ```

##### Recherche par mot clé

Si l'utilisateur choisi la recherche par mot-clé, le système va lui demander de saisir le mot qui servira à la comparaison (ex : stockage), il va ensuite afficher le temps de recherche et le(s) résultat(s). Dans le(s) résultat(s), on retrouve le nom du fichier et le nombre d'occurences du mot dans le fichier.

>```
> | Rechercher des fichiers texte par mot clé |
>
>
> Veuillez saisir le mot qui servira à la comparaison : 
>
> stockage
>
> Résultat(s) en 0,000047 secondes
>
>
> Le(s) fichier(s) dans lequel(lesquels) le mot "stockage" est significatif est(sont): (Nom_du_fichier : nombre_d'occurence de mot)
>
>	../BaseFichiersTexte/15-Capturer_et_emprisonner_le_CO2,.xml : 5
>
>	../BaseFichiersTexte/15-Capturer_et_emprisonner_le_CO.xml : 5
> ```

##### Recherche par comparaison d'un fichier avec la base

Si l'utilisateur choisi la recherche par comparaison d'un fichier avec la base, le système va lui demander de saisir le chemin du fichier à comparer avec la base (ex : ../BaseFichiersTexte/22-Grippe_aviaire___la_course.xml), il va ensuite afficher le temps de recherche et le(s) résultat(s). Dans le(s) résultat(s), on retrouve un ID pour ouvrir le fichier, le pourcentage de ressemblance et le chemin du fichier. L'application va ensuite demander l'ID entre parenthèses pour ouvrir le fichier que l'utilisateur souhaite voir.


> ```
> | Comparer un fichier texte à la base |
>
>
> Veuillez saisir le chemin du fichier à comparer
>
> ../BaseFichiersTexte/22-Grippe_aviaire___la_course.xml
>
> Résultat(s) en 0,002817 secondes
>
>
> (1)	100,000000%	../BaseFichiersTexte/22-Grippe_aviaire___la_course.xml
>
> (2)	21,361111%	../BaseFichiersTexte/06-Sensibiliser_α_la_vaccination_grippale.xml
>
> (3)	14,321428%	../BaseFichiersTexte/14-Grippe_aviaire___l_OMS_exhorte.xml
>
> (4)	9,000000%	../BaseFichiersTexte/26-Grippe_aviaire___une_sixiΦme.xml
>
> (5)	5,833333%	../BaseFichiersTexte/06-Les_mauvais_comptes_d_une_Θlimination.xml
>
> (6)	5,416667%	../BaseFichiersTexte/05-La_circoncision_pourrait_rΘduire_le.xml
>
> (7)	5,000000%	../BaseFichiersTexte/05-Le_thΘΓtre_de_texte_confrontΘ.xml
>
> (8)	5,000000%	../BaseFichiersTexte/10-La_rΘalitΘ_virtuelle_et_l_informatique.xml
>
> (9)	5,000000%	../BaseFichiersTexte/27-Le_Stade_de_France_s_ouvre.xml
>
> (10)	3,750000%	../BaseFichiersTexte/03-Des_chercheurs_parviennent_α_rΘgΘnΘrer.xml
>
>
> Rentrez le nombre entre parenthèse associé au fichier que vous souhaitez ouvrir
> 2
> ```

Plus de détails sur la recherche texte : [Recherche Texte Menu](https://github.com/acromtech/PFR/blob/menu/IndexationRechercheTexte/README.md),
[Recherche Texte](https://github.com/acromtech/PFR/blob/texte/README.md)


#### Recherche Image

Dans la "recherche image", l'utilisateur peut choisir de faire une recherche par histogramme en saisissant 2 ou faire une recherche par couleur en entrant 3. Il peut aussi à tout moment retourner en arrière en tapant le 1 ou fermer l'application en entrant le 4.

> ```
> ===========================================================
>
> ======================     IMAGE     ======================
>
> ===========================================================
>
>
>		2.  Recherche Histo.
>
>		3.  Recherche Couleur.
>
>		4.  Fermer l'application.
>
>
>		1.  Retour.
> ```


##### Recherche Histogramme

Si l'utilisateur choisi la recherche par histogramme, le système va lui demander de saisir le chemin ou le nom du fichier à comparer (ex : 12 ou ../IndexationImage/TXT/51.txt), il va ensuite afficher le(s) résultat(s). Dans le(s) résultat(s), on retrouve le chemin du fichier, un ID pour ouvrir le fichier, le pourcentage de ressemblance, le nom du fichier et si c'est une image en couleure ou une image en noir et blanc. L'application va ensuite demander l'ID entre parenthèses pour ouvrir le fichier que l'utilisateur souhaite voir.

Image Couleur :

> ```
> | Recherche par comparaison |
>
>
> Veuillez saisir le chemin ou le nom du fichier à comparer (numero_fichier ou chemin_vers_le_fichier)
>
> 12       
>
> ../IndexationImage/TXT/12.txt
>
> hehe = ../IndexationImage/TXT/12.txt
>
> (1)	100,000000%	12.jpg	Image couleur
>
> hehe = ../IndexationImage/TXT/04.txt
>
> (2)	77,894737%	04.jpg	Image couleur
>
> hehe = ../IndexationImage/TXT/24.txt
>
> (3)	76,842102%	24.jpg	Image couleur
>
> hehe = ../IndexationImage/TXT/02.txt
> 
> (4)	74,736839%	02.jpg	Image couleur
>
> hehe = ../IndexationImage/TXT/23.txt
> 
> (5)	73,684212%	23.jpg	Image couleur
> 
> hehe = ../IndexationImage/TXT/10.txt
>
>(6)	73,684212%	10.jpg	Image couleur
>
> hehe = ../IndexationImage/TXT/11.txt
>
> (7)	72,631577%	11.jpg	Image couleur
>
> hehe = ../IndexationImage/TXT/33.txt
>
> (8)	66,315788%	33.jpg	Image couleur
>
> hehe = ../IndexationImage/TXT/41.txt
>
> (9)	62,105263%	41.jpg	Image couleur
>
> hehe = ../IndexationImage/TXT/50.txt
>
> (10)	61,052631%	50.jpg	Image couleur
>
>
> Veuillez rentrer le nombre entre parenthèses associé au fichier que vous souhaitez ouvrir
>
>2
> ```

Image Noir et Blanc :

> ```
>| Recherche par comparaison |
>
>
> Veuillez saisir le chemin ou le nom du fichier à comparer (numero_fichier ou chemin_vers_le_fichier)
>
> ../IndexationImage/TXT/51.txt
>
> ../IndexationImage/TXT/51.txt
>
> hehe = ../IndexationImage/TXT/52.txt
>
> (1)	100,000000%	52.bmp	Image noir et blanc
>
> hehe = ../IndexationImage/TXT/51.txt
>
> (2)	100,000000%	51.bmp	Image noir et blanc
> 
> hehe = ../IndexationImage/TXT/53.txt
>
> (3)	98,958328%	53.bmp	Image noir et blanc
>
> hehe = ../IndexationImage/TXT/16.txt
>
> (4)	58,333332%	16.jpg	Image couleur
>
> hehe = ../IndexationImage/TXT/63.txt
>
> (5)	54,166668%	63.bmp	Image noir et blanc
>
> hehe = ../IndexationImage/TXT/58.txt
>
> (6)	43,750000%	58.bmp	Image noir et blanc
>
> hehe = ../IndexationImage/TXT/57.txt
>
> (7)	41,666664%	57.bmp	Image noir et blanc
>
> hehe = ../IndexationImage/TXT/62.txt
>
> (8)	38,541664%	62.bmp	Image noir et blanc
>
> hehe = ../IndexationImage/TXT/61.txt
>
> (9)	38,541664%	61.bmp	Image noir et blanc
>
> hehe = ../IndexationImage/TXT/60.txt
>
> (10)	38,541664%	60.bmp	Image noir et blanc
>
>
> Veuillez rentrer le nombre entre parenthèse associé au fichier que vous souhaitez ouvrir
>
> 2
> ```

##### Recherche par couleur

Si l'utilisateur choisi la recherche par couleur, le système va lui demander de saisir une couleur contenue dans la liste disponible (ex : violet), il va ensuite afficher le(s) résultat(s). Dans le(s) résultat(s), on retrouve le chemin du fichier, un ID pour ouvrir le fichier, le pourcentage de ressemblance, le nom du fichier et si c'est une image en couleur ou une image en noir et blanc. L'application va ensuite demander l'ID entre parenthèses pour ouvrir le fichier que l'utilisateur souhaite voir.

> ```
> | Recherche Couleur |
>
>
> Couleurs disponibles :	violet fushia orange saumon rouge vert bleu corail jaune kaki olive vertForet bleuMer eau cyan turquoise bleuMarine bleuNuit marron blanc noir ardoise 
>
>
> Formulez une requete de couleur
>
> violet
>
> hehe = ../IndexationImage/TXT/34.txt
>
> (1)	9,000000%	34.jpg	Image couleur
>
> hehe = ../IndexationImage/TXT/35.txt
>
> (2)	3,000000%	35.jpg	Image couleur
>
> hehe = ../IndexationImage/TXT/28.txt
>
> (3)	1,000000%	28.jpg	Image couleur
>
>
> Veuillez rentrer le nombre entre parenthèses associé au fichier que vous souhaitez ouvrir
>
> 1
> ```

Plus de détails sur la recherche image : [Recherche Image](https://github.com/acromtech/PFR/blob/image/README.md)


#### Recherche Audio

Dans la recherche audio, l'utilisateur peut faire une "recherche jingle" en tapant 2. Il peut aussi à tout moment retourner en arrière en tapant le 1 ou fermer l'application en entrant le 3.

> ```
> ===========================================================
>
> ======================     AUDIO     ======================
>
> ===========================================================
>
>
>		2.  Recherche Jingle.
>
>		3.  Fermer l'application.
>
>
>		1.  Retour.
>	```

##### Recherche jingle

Si l'utilisateur choisi la "recherche jingle", le système va lui demander de saisir le nom du fichier (ex : jingle_fi.wav), il va ensuite afficher le(s) résultat(s). Dans le(s) résultat(s), on retrouve le pourcentage de ressemblance, ainsi que la position temporelle de la correspondance. Le système vous demandera ensuite d'appuyer sur la touche "Entrer" afin de lancer la lecture du fichier à la position de la correspondance.

> ```
> | Recherche de la correspondance lancée ... |
>
>
> | Entrez le nom de votre fichier : jingle_fi.wav       
>
>
> | Veuillez patienter | 
>
>
> | Correspondance trouvé à 90,32% ... | 
>
>
> | Voici le résultat | 
>
>
> Le jingle demarre à environ 29 sec du corpus
>
>
> Appuyez sur entrée pour lancer l'audio... (3 sec avant) 
> ```

Plus de détails sur la recherche audio : [Recherche Audio](https://github.com/acromtech/PFR/blob/audio/README.md)



### Menu Administrateur

Afin de rentrer dans le menu administrateur, il faut posséder le mot de passe (Mdp : 1234), l'utilisateur a 3 essais pour rentrer le bon mot de passe, si le mot de passe n'est pas correct l'application se ferme et sinon l'utilisateur a le choix entre modifier le mot de passe en tapant 2, supprimer les bases descripteurs et les listes descripteurs en entrant 3, indexer les bases de fichier en saisissant 4, modifier les paramètres d'indexation en rentrant 5 et se diriger vers le menu utilisateur avec 6. Il peut aussi à tout moment retourner dans le menu principal en tapant le 1.

> ```
> ===========================================================
>
> =================   ADMINISTRATION   ======================
>
> ===========================================================
>
>	Veuillez vous authentifier 
>
>	Entrez votre mot de passe (nombre d'essais restant 3) 
>	: 1234
>
>
>	Selectionez l'opération à réaliser.
>
>
>		2.  Modifier le mot de passe.
>
>		3.  Supprimer la base d'indexation (TEXTE, IMAGE et AUDIO).
>
>		4.  Indexer la base de fichiers (TEXTE, IMAGE et AUDIO).
>
>		5.  Modifer les paramètres d'indexation.
>
>		6.  Vue utilisateur.
>
>
>		1.  Retour.
> ```


#### Modification du mot de passe

Dans la modification du mot de passe, l'utilisateur n'a que le choix de modifier le mot de passe. Il peut aussi à tout moment retourner en arrière en tapant le 1, mais il lui faudra le mot de passe pour revenir dans le menu administrateur ou fermer l'application en entrant le 3. Le mot de passe est contenu dans le .config.
> ```
> ===========================================================
>
> ==============   MODIFICATION MOT DE PASSE   ==============
>
> ===========================================================
>
>
>		2.  Modifer.
>
>		3.  Fermer l'application.
>
>
>		1.  Retour (Vous demandera de vous identifier à nouveau).
> ```

##### Modifier le MDP

Si l'utilisateur choisi de modifier le mot de passe, le système va lui demander de saisir le nouveau mot de passe (ex : 1505), il va ensuite afficher le nouveau mot de passe.

> ```
> | Changement de mot de passe |
>
>	Entrez le nouveau mot de passe (Nombre uniquement): 1505
>
>
> Mot de passe a été modifié !
>
>
> Le nouveau mot de passe est : 1505
> ```


#### Suppresion des Bases et des Listes

Dans la "suppression des bases et des listes", l'utilisateur n'a que le choix de supprimer les bases et les listes. Il peut aussi à tout moment retourner en arrière en tapant le 1 mais il lui faudra le mot de passe pour revenir vers le menu administrateur. Il peut aussi fermer l'application en entrant le 3. 

> ```
> ===========================================================
>
> ============   SUPPRIMER LA BASE D'INDEXATION   ===========
>
> ===========================================================
>
>
>		2.  Supprimer.
>
>		3.  Fermer l'application.
>
>
>		1.  Retour (Vous demandera de vous identifier à nouveau).
> ```

##### Supprimer les bases et les listes

> ```
> | Suppression de la base Indexée |
>
>
> | Suppression terminée ! |
> ```


#### Indexation
Dans l'indexation, l'utilisateur n'a que le choix d'indexer les bases de fichier. Il peut aussi à tout moment retouner en arrière en tapant le 1 mais il lui faudra le mot de passe pour revenir dans le menu administrateur ou fermer l'application en entrant le 3. 
> ```
> ===========================================================
>
> =============   INDEXER LA BASE DE FICHIERS   =============
>
> ===========================================================
>
>
>		2.  Indexer.
>
>		3.  Fermer l'application.
>
>
>		1.  Retour (Vous demandera de vous identifier à nouveau).
> ```

##### Indexer les bases de fichier

> ```
> | Indexation lancée. Veuillez patienter ... (20 sec)|
>
>
> | Indexation terminée ! |
> ```

###### Indexation Texte

Plus de détaille sur l'indexation texte : [Indexation Texte Menu](https://github.com/acromtech/PFR/blob/menu/IndexationRechercheTexte/README.md), [Indexation Texte](https://github.com/acromtech/PFR/blob/texte/README.md)

###### Indexation Image

Plus de détaille sur l'indexation image : [Indexation Image](https://github.com/acromtech/PFR/blob/image/README.md)

###### Indexation Audio

Plus de détaille sur l'indexation AUdio : [Indexation Audio](https://github.com/acromtech/PFR/blob/audio/README.md)


#### Configuration

Dans la rconfiguration, l'utilisateur a le choix entre lancer la modification en saisissant le 2 ou soit afficher le fichier de configuration en rentrant le 3. Il peut aussi à tout moment retouner en arrière en tapant le 1 ou fermer l'application en entrant le 4.

> ```
> ===========================================================
>
> ===============   MODIFICATION PARAMETRES   ===============
>
> ===========================================================
>
>
>		2.  Lancer la modification.
>
>		3.  Affichage du fichier de configuration.
>
>		4.  Fermer l'application.
>
>
>		1.  Retour (Vous demandera de vous identifier à nouveau).
> ```

##### Lancer la modification

Si l'utilisateur choisi de lancer la modification, le système va  afficher la configuration actuelle et va ensuite demander la ligne à modifier puis la valeur. il va ensuite afficher la nouveau configuration. Il va aussi demander si on veut réindexer les base de fichier avec la nouvelle configuration. Les valeurs ont des seuils  limites pour ne pas mettre de valeur négative ou par exemple mettre plus de 100 % au seuil  

> ```
> | Lancement de la modification du fichier config ... |
>
>
> 2 motdePasse 1505
>
> 3 indexationAudioN 1024
>
> 4 indexationAudioM 100
>
> 5 seuil 89
>
> 6 dureeAudioCorpus 70
>
> 7 nbListe 10
>
> 8 seuilMotSignificatif 3
>
>
> Entrez le numéro du paramètre qui doit être modifié : 7
>
> Entrez la nouvelle valeur pour le paramètre n° 7 : 5
>
>
> 2 motdePasse 1505
>
> 3 indexationAudioN 1024
>
> 4 indexationAudioM 100
>
> 5 seuil 89
>
> 6 dureeAudioCorpus 70
>
> 7 nbListe 5
>
> 8 seuilMotSignificatif 3
>
>
> | Voulez-vous reindexer avec la nouvelle modification ? [O/n] : n
> ```

###### Indication

Le seuil correspond au seuil de correspondance pour la comparaison de fichier pour la partie recherche audio et le nbListe correspond au nombre de résultat afficher pour la partie texte et image. 
