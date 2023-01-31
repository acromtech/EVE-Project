# Partie Image

Auteur : **Flavie THIBAULT, Alexis GIBERT et Mouléro DEGBEGNI**

module : Informatique

## Information

Cette partie a consisté à réaliser l'indexation d'une base de fichiers texte au format XML, realiser la recherche par mot clé des fichiers contenant ce mot en quantité "significative" et faire la comparaison de fichiers texte à la base de fichiers texte. Cette partie a été réalisé de façon collaborative par Alexis GIBERT et Mouléro DEGBEGNI.

## Prérequis
* Système d'exploitation : Linux
* Lecteur d'image : eog (Eye of Gnome)
## Utilisation
### Indexation texte

Pour lancer l'indexation texte, il faut :
> ```
> 1 . Ouvrir un terminal depuis le repertoire de base
> 2 . Se placer dans le dossier **Image** ( cd src)
> 3 . Faire un **make indexation**. Cela va lancer le fichier **test_indexationImage**, supprimer la base d'indexation puis indexer les de la base en utilisant les fichiers .TXT.
> ```

Pour vérifier que l'indexation à été bien réalisée depuis le répertoire **Image** vérifier le contenu des fichiers :

> ```
> 1 base_indexation.csv : ce fichiers contient ligne par ligne les différents decripteurs obtenus après traitement des différents fichiers textes
> 2 liste_indexation.csv : celui ci contient ligne par ligne le chemin vers les différents fichiers indexer et leur
> ```
## Fonctions de recherches
Deux fonctions de recherches sont présentes
* Une recherche par couleurs
* Une recherche par comparaison d'image

## Recherche par couleurs
__1. Suite au lancement du moteur de recherche de couleurs, celui-ci vous proposera de sélectionner entre différentes couleurs__

> ```
> Couleurs disponibles : violet, fushia, orange, saumon, rouge, vert, bleu, corail, jaune, kaki, olive, vert foret, bleu mer, eau, cyan, turquoise, bleu marine, bleu  nuit, marron, blanc, noir, ardoise
> ```

__2. Formulez alors la requete souhaitée__

Si la requete est invalide un *Warning* apparaitra et il vous sera demandé de formuler une nouvelle requete
> ```
> Formulez une requete de couleur
> TEST
> 
> Attention : Aucune image ne correspond à la couleur spécifiée : Essayez d'autres couleurs
> ```

> ```
> Formulez une requete de couleur
> 01
> 
> Attention : Aucune image ne correspond à la couleur spécifiée : Essayez d'autres couleurs
> ```

Si la requete est correctement formulée, un tableau de score trié par ordre décroissant sera affiché à l'écran.
> ```
> Formulez une requete de couleur
> violet
> (1)	9,000000%	34.jpg	Image couleur
> (2)	3,000000%	35.jpg	Image couleur
> (3)	1,000000%	28.jpg	Image couleur
> ```
> *Note : Le score représente le taux de correspondance avec la couleur choisie et vous sera exprimé en pourcentage.*

__3. Vous pourez ainsi sélectionner l'image que vous souhaiterez ouvrir en tapant au clavier le numéro inscrit entre parenthèse.__

Si la requete est invalide un *Warning* apparaitra et il vous sera demandé de formuler une nouvelle requete.
> ```
> Veuillez rentrer le nombre entre parenthèse associé au fichier que vous souhaitez ouvrir
> 10   
> Attention : Vous ne pouvez rentrer qu'un chiffre compris entre 1 et 3
> ```

Si la requete est correctement formulée, un message de confirmation sera affiché à l'écran et l'image sera ouverte automatiquement.
> ```
> Veuillez rentrer le nombre entre parenthèse associé au fichier que vous souhaitez ouvrir
> 1   
> -----------Recherche réalisée avec succès------------
> ```

## Recherche par comparaison d'image
__1. Suite au lancement du moteur de recherche dédié à la comparaison d'image, celui-ci vous proposera de taper au clavier__
* Soit un chemin vers l'image de référence,
* Soit le nom de l'image.

Si la requete est invalide un *Warning* apparaitra et il vous sera demandé de formuler une nouvelle requete.
> ```
> Veuillez saisir le chemin ou le nom du fichier à comparer
> TEST
> Attention : Aucune image ne correspond au chemin spécifiée
> ```

Si la requete est correctement formulée, un tableau de score trié par ordre décroissant sera affiché à l'écran.
> ```
> Veuillez saisir le chemin ou le nom du fichier à comparer
> 50  
> (1)	100,000000%	50.jpg	Image couleur
> (2)	68,888893%	40.jpg	Image couleur
> (3)	66,666672%	41.jpg	Image couleur
> (4)	66,666672%	33.jpg	Image couleur
> (5)	66,666672%	24.jpg	Image couleur
> (6)	66,666672%	23.jpg	Image couleur
> (7)	64,444443%	12.jpg	Image couleur
> (8)	62,222225%	19.jpg	Image couleur
> (9)	62,222225%	04.jpg	Image couleur
> (10)	61,111111%	39.jpg	Image couleur
> ```
> *Note : Le score représente le taux de correspondance avec l'image de référence choisie et vous sera exprimé en pourcentage.*

__3. Vous pourez ainsi sélectionner l'image que vous souhaiterez ouvrir en tapant au clavier le numéro inscrit entre parenthèse.__

Si la requete est invalide un *Warning* apparaitra et il vous sera demandé de formuler une nouvelle requete.
> ```
> Veuillez rentrer le nombre entre parenthèse associé au fichier que vous souhaitez ouvrir
> 10   
> Attention : Vous ne pouvez rentrer qu'un chiffre compris entre 1 et 3
> ```

Si la requete est correctement formulée, un tableau de score trié par ordre décroissant sera affiché à l'écran.
> ```
> Veuillez rentrer le nombre entre parenthèse associé au fichier que vous souhaitez ouvrir
> -1 
> ```

Si la requete est correctement formulée, un message de confirmation sera affiché à l'écran et l'image sera ouverte automatiquement.
> ```
> Veuillez rentrer le nombre entre parenthèse associé au fichier que vous souhaitez ouvrir
> 9   
> -----------Recherche réalisée avec succès------------
> ```

