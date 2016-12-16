#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "Dynamique.h"    //on importe la librairie des différentes fonction de Dynamique.c
#include "pbm.h"    //on importe la librairie pbm.h pour utiliser le programme pbm.c

#define gotoxy(x, y) printf("\033[%d;%dH", (x), (y))    //Cette fonction permet d'utliser la fonction gotoxy(a, b) qui permet de placer le curseur à un certiain endroit dans la console


FILE* fichier_d = NULL;   //on crée un pointeru fichier_d pointant sur FILE(un fichier)

void dynamique()    //cette fonction est unpeu le main de ce programme
{
    int RefreshT = 6;   //valeur donnant le nombre de seconde avant d'actualisé l'horloge
    int ctrlc = 0;    //valeur permettant de faire la boucle while à l'infini sauf ctrl+c
    int tab[8] = {0};   //initialisation du tableau qui va contenir les valeur le l'heure
    int a = 20,b = 20,c = 7,d = 13;   //initialisation des différents valeur qui permetterons de se possitionner dans le shell
    int x, y;   //initialisation des valeurs qui donnerons la taille du tableau contenant l'image
    system("clear");    //on commence par effacer toute la console
    while (ctrlc != 1)    //boucle infini excepter un Ctrl+c
    {
        int e = 20, f = 67;   //initialisation de valeurs pour centrer la phrase d'actualisation de l'heure
        c = 7;    //on remet les valeurs d'affichage centrer de l'heure à leur valeurs initials
        d = 13;   //de même
        take_time((int *) tab);   //on entre dans un fonction qui va resortir leurs actuelle et la stocker dans un tableau
        for (int z=0; z<=7; z++)    //boucle qui se répète autant de fois qu'il y a d'image de l'heure à affiché
        {
            choix(tab[z]);    //on entre dans la fonction qui choisie l'image du nombre qui va avec celui de l'heure à affiché
            if (fichier_d != NULL)    //on entre dans si on a reussi à ouvir l'image du chiffre de l'heure
            {
                taille_d(&x, &y);   //on entre dans la fonction taille pour determiner la taille du tableau selon la taille de l'image en envoyant l'adresse mémoire de x et y
                int img[x][y];    //on initialise le tableau qui contiendra les valeurs de l'image pbm
                remplir_d((int *) img, x, y);   //on entre dans la fonction remplir qui remplira le tableau avec les valeurs de l'image
                pbm((int *) img, x, y);   //on entre dans la fonction pbm qui est situer dans un autre .c qui permet de convertir les 0 et 1 des images en caractère ascii
                affiche_d((int *) img, x, y, c, d);   //on entre dans la fonction affiche qui affichera les caractère ascii stocker dans le tableau
                c = 7;    //on se place là où il faut pour affiché l'image suivante de l'heure
                d = d + 7;    //de même
                fclose(fichier_d);    //on ferme le fichier de l'image
                fichier_d = NULL;   //on remet le pointeur du fichier à NULL
            }
            else    //on arrive ici si aucune image n'a été trouvée pour la valeur du chiffre de l'heure
            {
                printf("Les fichiers .pbm ne peuvent s'ouvrir\n");    //on précise à l'utilisateur qu'aucun fichier n'a été trouvé
                exit(1);  //on quit le programme
            }
        }
        gotoxy(a,b);    //on se place dans le shell là où sera affiché que l'heure va être actualisé
        printf("Cet écran sera actualisé dans quelques secondes \n");   //on indique à l'utilisateur que l'heure va bientot s'actualisé

        for (int i=0; i<RefreshT; i++)    //boucle qui se répète autant de fois que la valeur de refresh que nous avons donné au début
        {
            sleep(1);   //on attend une seconde
            gotoxy(e,f);    //on se place a l'endroit où l'on va affiché les "." qui se rajoute à chaque seconde
            printf(".\n");    //on affiche le points à la fin de la phrase
            f++;    //on augmente f de 1 pour se possitionner au caractère suivant
        }
        f=f-RefreshT;   //au remet f au bonne endoit pour commencer à affiché les points au début de la phrase
        gotoxy(e, f);   //on se repositionne à la fin de la phrase pour effacer les points
        printf("                            ");   //on affiche des espace pour "supprimé" les points
        system("clear");    //on efface toute la console
    }
}


void take_time(int * tab)   //fonction qui sort, calcule et stock dans un tableau l'heure actuelle
{
    time_t secondes;    //on initialise la variable seconde de type time
    struct tm instant;    //on ajoute la structure pour pouvoir récuperé le temps actuelle
    time(&secondes);    //on récupère l'heure en seconde et on la stock dans la variable seconde
    instant = *localtime(&secondes);    //on stocke le pointeur de se temps dans la structure
    int S1 = (instant.tm_sec) / 10;   //on calule à l'aide des seconde la valeur d'unité des secondes
    int S2 = (instant.tm_sec) - (S1 * 10);    //on calule à l'aide des seconde la valeur des dixaines des secondes
    int M1 = (instant.tm_min) / 10;     //on calule à l'aide des seconde la valeur d'unité des minutes
    int M2 = (instant.tm_min) - (M1 * 10);    //on calule à l'aide des seconde la valeur des dixaines des minutes
    int H1 = (instant.tm_hour) / 10;    //on calule à l'aide des seconde la valeur d'unité des heures
    int H2 = (instant.tm_hour) - (H1 * 10);   //on calule à l'aide des seconde la valeur des dixaines des heures
    tab[0] = H1;    //on stocke les dixaines d'heure dans la case qui lui ai attribuer dans le tableau
    tab[1] = H2;    //on stocke les unités d'heure dans la case qui lui ai attribuer dans le tableauu
    tab[2] = 15;    //on stocke la valeur pour avoir l'image des ":" dans la case qui lui ai attribuer dans le tableau
    tab[3] = M1;    //on stocke les dixaines de minutes dans la case qui lui ai attribuer dans le tableau
    tab[4] = M2;    //on stocke les unités de minutes dans la case qui lui ai attribuer dans le tableau
    tab[5] = 15;    //on stocke la valeur pour avoir l'image des ":" dans la case qui lui ai attribuer dans le tableau
    tab[6] = S1;    //on stocke les dixaines de secondesdans la case qui lui ai attribuer dans le tableau
    tab[7] = S2;    //on stocke les unités de secondes dans la case qui lui ai attribuer dans le tableau
}


void choix(int a)   //on est dans la fonction qui va choisir l'image selon la valeur du tableau des heures et l'ouvrir puis la stocker dans fichier
{
    switch (a) {    //un switch permet d'aller dans la case que l'on souhaite selon la valeur du tablleau et si aucun ne convient c'est la case default qui est lancée
        case 0:
            fichier_d = fopen("pbm2/0.pbm", "r");
            break;
        case 1:
            fichier_d = fopen("pbm2/1.pbm", "r");
            break;
        case 2:
            fichier_d = fopen("pbm2/2.pbm", "r");
            break;
        case 3:
            fichier_d = fopen("pbm2/3.pbm", "r");
            break;
        case 4:
            fichier_d = fopen("pbm2/4.pbm", "r");
            break;
        case 5:
            fichier_d = fopen("pbm2/5.pbm", "r");
            break;
        case 6:
            fichier_d = fopen("pbm2/6.pbm", "r");
            break;
        case 7:
            fichier_d = fopen("pbm2/7.pbm", "r");
            break;
        case 8:
            fichier_d = fopen("pbm2/8.pbm", "r");
            break;
        case 9:
            fichier_d = fopen("pbm2/9.pbm", "r");
            break;
        case 15:
            fichier_d = fopen("pbm2/point.pbm", "r");
            break;
        default:
            printf("Chiffre inconnue");
            break;
    }
}


void taille_d(int *x, int *y)   //on est dans la fonction qui cherche la taille (hauteur, largeur) de l'image
{

    fseek(fichier_d, 3, SEEK_SET);    //fonction qui permet de ce placer à la 3e posstion à partir du début du ficher
    fscanf(fichier_d, "%d %d", y, x);     //fonction qui permet de lire dans un fichier

}

void remplir_d(int *img, int x, int y)    //on est dans la fonction qui parcours le fichier pour stocker caractère par caractère l'image dans le tableau
{
    int i = 0;
    int j = 0;
    char test[20];    //on créé un chaine de caractère quqi va contenir tout l'image
    fseek(fichier_d, 7, SEEK_SET);    //on se positionne au 7e caractère du fichier, là où commence l'image
    for (; i <x; i++)     //on se positionne à la 1re ligne du tableau
    {
        fgets(test, 20, fichier_d);   //on lit toute la nième ligne de l'image
        for (j=0; j <y; j++)    //on parcours la 1er ligne du tableau
        {
            img[i * y + j] = test[j];   //on entre caractère par caractère de la chaine de caractère lu dans chaque case du tableau
        }
    }
}


void affiche_d(int *img, int x, int y, int c, int d)    //on est dans la fonction qui permet d'affiché l'image et donc les caractère stocker dans le tableau
{
    int i = 0;
    for (; i < x; i++)    //on parcours chaque ligne du tableau
    {
        gotoxy(c,d);    //on se positionne dans le shell pour affiché l'image centrer dans l'affichage de l'heure

        for (int j = 0; j < y; j++)     //on parcours chaque caractère de la ligne
        {
            int l = img[i*y+j];     //on sort le caractère du tableau pour le mettre dans la variable "l"
            if(l == 48 || l == 32 || l == 10)   //on vérifie que la valeur de "l" est bien une des valeurs ascii que nous voulons affiché
            {
                printf("%c",l);   //si la valeur de "l" est bonne alors on  l'affiche
            }
        }
        c++;    //on incrémente "c" pour se positionner à la ligne du dessous et donc écrire un ligne plus bass
    }
}
