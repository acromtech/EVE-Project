#!/bin/bash

# arreter immédiatement le le script si une commande retourne une valeur de sortie non nul
set -e

# global variables
tags=(titre article phrase resume texte)


# validation de la validité et de l'existance du fichier entré en parametre 
if [ ! -f "$1" ]
then
    echo "Error: le fichier d'entré n'est pas valide ou n'existe pas !"
    exit 1
fi


# supprimer les premières lignes, on verifie d'abord qu'il contient plus de 4 lignes. Ceci nous permet de nous débarassé des lignes relatives à la version xml, la date, et l'auteur
if [ `wc -l < $1` -ge 4 ]
then
    sed -i '1,4d' $1 # l'option -i permet de faire 
fi

# remplacer '-' par ' ' 
#sed -i -e "s/-/ /g" $1

# supprimer toutes les balises
for tag in "${tags[@]}"
do
    sed -i -e "s/<$tag>//g" $1
    sed -i -e "s/<\/$tag>//g" $1
done

# supprimer toutes les url 

sed -i -E "s#https?:\/\/[^ ]*##g" $1

# supprimer toutes les ponctuations sauf "'"

sed -i -e "s/[^[:alnum:][:space:]']/ /g" $1

# remplacer tous les "'" par des "' " avec x dans {d, s, m, l}
sed -i -e "s/'/' /g" $1

# convertir en minuscule les majuscules
sed -i 'y/ABCDEFGHIJKLMNOPQRSTUVWXYZ/abcdefghijklmnopqrstuvwxyz/' $1


# supprimer toutes les lignes vides après traitement 
sed -i '/^$/d' $1

# afficher le fichier après traitement // Pour debuger
# cat $1

exit 0
