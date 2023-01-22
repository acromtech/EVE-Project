
					/*-------------------------------------------/
					/ AUTEUR : LALANNE Bastien                   /
                    /-------------------------------------------*/    

/* Rôle : Permet la modifcitaion, l'affichage et l'écriture des paramètres dans le .config*/


#ifndef configuration
#define configuration


// Permet de modifier la valeur d'un paramètre dans le .config
void editConfig(int nouv_num_ligne, int nouv_val);
// Interface pour modifier la valeur d'un paramètre dans le .config
void saisieConfig();
// Affichage du .config
void affichConfig();
// Permet la récupération de la valeur du paramètre donner en paramètre
int config(char nom[]);


#endif
