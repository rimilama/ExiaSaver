#include "pbm.h"    //on importe la biblothèque des fonctions de ce programme

void pbm(int *tab, int x, int y)    //fonction qui converti le binaire des fichier pbm en caractère ascii
{
    int i = 0;
    int j = 0;
    for(;i<x;i++)   //on parcours chaque ligne du tableau
    {
        for(;j<y;j++)   //on parcours chaque caractère de la ligne
        {
            if(tab[i*y+j] == '0')   //on rentre dans la fonction si le caractère à cette case du tableau est un 0
            {
                tab[i*y+j] = ' ';   //on remplace alors le 0 par un espace ou un caractère vide ou blanc
            }
            else
            {
                if(tab[i*y+j] == '1')   //on rentre dans la fonction si le caractère à cette case du tableau est un 1
                {
                    tab[i*y+j] = '0';   //on remplace alors le 1 par un 0 ou un carctère visuelle ou noir
                }
            }
        }
        j = 0;
    }
}
