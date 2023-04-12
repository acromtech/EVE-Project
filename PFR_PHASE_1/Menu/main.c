#include "menu_mae.h"


unsigned char etat_mae_main=ETAT_PRINCIPAL;


int main()
{
    system("clear");
    while(1)
    {
        action_mae(&etat_mae_main);
        evolution_mae(&etat_mae_main);
        system("clear");
    }
}