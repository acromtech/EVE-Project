#include "menu_mae.h"


unsigned char etat_mae_main=ETAT_PRINCIPAL;


int main()
{
    while(1)
    {
        action_mae(&etat_mae_main);
        evolution_mae(&etat_mae_main);
    }
}



// int main(int argc, char **argv)
// {
//     while(fin)
//     {
//         menu_principal();
//     }
//     return 0;
// }