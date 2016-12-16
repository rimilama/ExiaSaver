#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#include "Interactif.h"
#include "pbm.h"    //on importe la librairie pbm.h pour utiliser le programme pbm.c

#define gotoxy(x, y) printf("\033[%d;%dH", (x), (y))    //Cette fonction permet d'utliser la fonction gotoxy(a, b) qui permet de placer le curseur à un certiain endroit dans la console


FILE *fichier3 = NULL;   //on crée un pointeru fichier pointant sur FILE(un fichier)


void interactif() //cette fonction est unpeu le main de ce programme
{
    system("clear");    //on commence par effacer toute la console
    fichier3 = (FILE *) malloc(sizeof(int));   //on alloue de la mémoire à la variable fichier de la taille d'un int
    int x = 0, y = 0;   //initialisation des valeurs qui donnerons la taille du tableau contenant l'image
    char q = '\0';  //le caractère '\0' est un caractère vide
    fichier3 = fopen("pbm3/avion.pbm", "r");
    if (fichier3 != NULL)     //on entre dans la boucle si un fichier est ouvert
    {
        taille_i(&x, &y);   //on entre dans la fonction taille pour determiner la taille du tableau selon la taille de l'image en envoyant l'adresse mémoire de x et y
        int tab[x][y];    //on initialise le tableau qui contiendra les valeurs de l'image pbm
        remplir_i((int *) tab, x, y);   //on entre dans la fonction remplir qui remplira le tableau avec les valeurs de l'image
        pbm((int *) tab, x, y);   //on entre dans la fonction pbm qui est situer dans un autre .c qui permet de convertir les 0 et 1 des images en caractère ascii
        affiche_i((int *) tab, x, y);   //on entre dans la fonction affiche qui affichera les caractère ascii stocker dans le tableau
        fclose(fichier3);    //on ferme le fichier contenant l'image
        fichier3 = NULL;   //on remet le pointeur fichier à NULL
        free(fichier3);    //on libère la mémoire précédemment alouer au fichier
        printf("\nL'avion est en maintenance pour une durée indeterminer. \nVeuillez nous excuser pour notre retard \n-SNVF\n");
        quit_i(q);    //on rentre dans la fonction quit qui est la seule porte de sortie normale du programme
    }
    else    //on arrive ici si aucune image n'a été trouvée pour la valeur random
    {
        printf("Impossible d'ouvrir le fichier .pbm\n");    //on précise à l'utilisateur qu'aucun fichier n'a été trouvé
        quit_i(q);    //on rentre dans la fonction quit qui est la seule porte de sortie normale du programme
    }
}




void taille_i(int *x, int *y)   //on est dans la fonction qui cherche la taille (hauteur, largeur) de l'image
{
    fseek(fichier3, 3, SEEK_SET);    //fonction qui permet de ce placer à la 3e posstion à partir du début du ficher
    fscanf(fichier3, "%d %d", y, x);   //fonction qui permet de lire dans un fichier
    *y = *y +1;   //on augmente la largeur de 1 pour prendre le "\n" de la ligne avec
}


void remplir_i(int *tab, int x, int y)    //on est dans la fonction qui parcours le fichier pour stocker caractère par caractère l'image dans le tableau
{
    int i = 0;
    int j = 0;
    fseek(fichier3, 7, SEEK_SET);    //on se positionne au 9e caractère du fichier, là où commence l'image
    //char test[20];    //on créé un chaine de caractère quqi va contenir tout l'image
    for (; i < x; i++)    //on se positionne à la 1re ligne du tableau
    {
        //fgets(test, 20, fichier3);   //on lit toute la nième ligne de l'image
        for (j=0; j < y; j++)   //on parcours la 1er ligne du tableau
        {
            tab[i * y + j] = fgetc(fichier3);    //le caractère lu va aller dans la case du tableau qui lui est attribuer
        }   //i*y+j permet de parcourir le tabeau case par case car à une nouvelle ligne la numérotation des case ne revient pas à 0 à chaque debut de ligne
    }
}


void center_i(int y, int b)   //on est dans la fonction qui permet de centrer l'image
{
    int a = (80 - y) / 2;   //on calcul à quel caractère de la ligne il faut commencer à affiché l'image
    gotoxy(b, a);   //on se positionne au coordonnée {a, b} dans le shell
}


void affiche_i(int *tab, int x, int y)    //on est dans la fonction qui permet d'affiché l'image et donc les caractère stocker dans le tableau
{
    int i = 0;
    int b = (25 - x) / 2;   //on calcul à quelle ligne on va se placer pour que l'image soit centrer
    for (; i < x; i++)    //on parcours chaque ligne du tableau
    {
        center_i(y, b);   //on appelle la fonction centrer pour commencer à affiché au bonne endroit pour centrer l'image dans le shell
        b++;    //on incrémente b pour commencer à écrire à la ligne suivante au même endroit mais une ligne en dessous
        for (int j = 0; j < y-1; j++)   //on parcours chaque caractère de la ligne
        {
            printf("%c",tab[i*y+j]);    //on affiche chaque caractère de l'image stocker dans le tableau
        }
    }
}

void quit_i(char q)   //on est dans la fonction qui quitte le programme si un touche du clavier est enfoncer
{
    initscr();
    cbreak();
    noecho();
    q = (char) getchar();
    if (q != '\0')
    {
        system("clear");
        echo();
        nocbreak();
        endwin();
    }
}

