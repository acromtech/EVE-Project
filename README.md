# PFR-texte 

Dernière update : 27/01/2023

Auteur : **Alexis GIBERT et Mouléro DEGBEGNI**

module : Informatique

## Information

Cette partie a consisté à réaliser l'indexation d'une base de fichiers texte au format XML, realiser la recherche par mot clé des fichiers contenant ce mot en quantité "significative" et faire la comparaison de fichiers texte à la base de fichiers texte. Cette partie a été réalisé de façon collaborative par Alexis GIBERT et Mouléro DEGBEGNI.

## Prérequis
* Système d'exploitation : Linux

## Utilisation
### Indexation texte

Pour lancer l'indexation texte, il faut :
> ```
> 1 . Ouvrir un terminal depuis le repertoire de base
> 2 . Se placer dans le dossier **src** ( cd src)
> 3 . Faire un **make indexation**. Cela va lancer le fichier **tst_indexationTexte**, qui va recharger la base d'indexation puis indexer les nouveaux fichiers ajouter à la base depuis la derniere indexation. Si vous voulez supprimer la base puis refaire l',indexation il suffit de faire **make suppIndexation**, la base d'indexation sera donc supprimée et l'indexation sera faite juste après. 
> ```

Pour vérifier que l'indexation à été bien réalisée il suffit de se rendre dans le repertoire **../bin/fichiersIndexation/** depuis le répertoire **src**. Vous y trouverez trois différents fichiers :

> ```
> 1 base_indexation.csv : ce fichiers contient ligne par ligne les différents decripteurs obtenus après traitement des différents fichiers textes
> 2 liste_indexation.csv : celui ci contient ligne par ligne le chemin vers les différents fichiers indexer et leurs numero d'identification
> 3 table_indexation.csv : ce fichier quand a lui contient la liste des différents mot relevé comme étant signification et le numero d'identification des différents fichiers desquuelles ils ont été relevés
> ```

### Recherche Audio

Pour lancer la recherche par mot clé ou la comparaison de fichier il suffit de :

> ```
> 1. Ouvrir un nouveau terminal dans le repertoire src
> 2. Faire un make recherche vous aurrez après le choix de faire à la suite une comparaison de fichiers puis une recherche par mot clé. 
> 3. Suivre les différentes instructions
> ```
