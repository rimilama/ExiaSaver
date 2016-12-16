#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <string.h>

#include "Statique.h"   //on importe la librairie des différentes fonction de Statique.c
#include "pbm.h"    //on importe la librairie pbm.h pour utiliser le programme pbm.c

#define gotoxy(x, y) printf("\033[%d;%dH", (x), (y))    //Cette fonction permet d'utliser la fonction gotoxy(a, b) qui permet de placer le curseur à un certiain endroit dans la console


FILE *fichier = NULL;   //on crée un pointeru fichier pointant sur FILE(un fichier)


void statique(int random)   //cette fonction est unpeu le main de ce programme
{
    system("clear");    //on commence par effacer toute la console
    pid_t pid;    //pid_t est un type de valeur : le PID d'un processus
    pid=fork();   //avec fork() on duplique le processus en un processus fils et le PID du fils est stocker dans pid initialiser au dessus
    if (pid == 0)   //si le PID=0 c'est que nous sommes dans le processus fils
    {
      fichier=(FILE*)malloc(sizeof(int));   //on alloue de la mémoire à la variable fichier de la taille d'un int
      int x = 0, y = 0;   //initialisation des valeurs qui donnerons la taille du tableau contenant l'image
      char q = '\0';  //le caractère '\0' est un caractère vide
      choix_pbm(random);    //on envoie dans la fonction la valeur random donnée par l'éxecuteur pour choisir une des 5 images au hasard
      if (fichier != NULL) {    //on entre dans la boucle si un fichier est ouvert
          taille(&x, &y);   //on entre dans la fonction taille pour determiner la taille du tableau selon la taille de l'image en envoyant l'adresse mémoire de x et y
          int tab[x][y];    //on initialise le tableau qui contiendra les valeurs de l'image pbm
          remplir((int *) tab, x, y);   //on entre dans la fonction remplir qui remplira le tableau avec les valeurs de l'image
          pbm((int *) tab, x, y);   //on entre dans la fonction pbm qui est situer dans un autre .c qui permet de convertir les 0 et 1 des images en caractère ascii
          affiche((int *) tab, x, y);   //on entre dans la fonction affiche qui affichera les caractère ascii stocker dans le tableau
          fclose(fichier);    //on ferme le fichier contenant l'image
          fichier = NULL;   //on remet le pointeur fichier à NULL
          free(fichier);    //on libère la mémoire précédemment alouer au fichier
          quit(q);    //on rentre dans la fonction quit qui est la seule porte de sortie normale du programme
      }
      else    //on arrive ici si aucune image n'a été trouvée pour la valeur random
      {
          printf("Impossible d'ouvrir le fichier .pbm\n");    //on précise à l'utilisateur qu'aucun fichier n'a été trouvé
          quit(q);    //on rentre dans la fonction quit qui est la seule porte de sortie normale du programme
      }
    }
    else    //on arrive ici si on est pas dans processus fils
    {
        wait(NULL);   //on attent d'être dans le processus fils
   }
}


void choix_pbm(int random)    //on est dans la fonction qui va choisir l'image selon la valeur donnée précédemment et l'ouvrir puis la stocker dans fichier
{
    switch (random)   //un switch permet d'aller dans la case que l'on souhaite selon la valeur de random et si aucun ne convient c'est la case default qui est lancée
    {
        case 1:
            fichier = fopen("pbm/OW.pbm", "r");   //on ouvre l'image du logo d'overwatch et on la stock dans fichier
            break;
        case 2:
            fichier = fopen("pbm/ghost.pbm", "r");    //on ouvre l'image d'un fantome de pacman et on la stock dans fichier
            break;
        case 3:
            fichier = fopen("pbm/genji.pbm", "r");    //on ouvre l'image du masque de genji (un personnage de overwatch) et on la stock dans fichier
            break;
        case 4:
            fichier = fopen("pbm/issac.pbm", "r");    //on ouvre l'image de issac (un personnage du jeu the binding of issac) et on la stock dans fichier
            break;
        case 5:
            fichier = fopen("pbm/SW.pbm", "r");   //on ouvre l'image du casque d'un stormtrooper et on la stock dans fichier
            break;
        default:
            fichier = fopen("pbm/castle.pbm", "r");   //on ouvre l'image d'un château qui est donnée dans le sujet d'overwatch et on la stock dans fichier
            break;
    }
}


void taille(int *x, int *y)   //on est dans la fonction qui cherche la taille (hauteur, largeur) de l'image
{
    fseek(fichier, 3, SEEK_SET);    //fonction qui permet de ce placer à la 3e posstion à partir du début du ficher
    fscanf(fichier, "%d %d", x, y);   //fonction qui permet de lire dans un fichier
    *y = *y +1;   //on augmente la largeur de 1 pour prendre le "\n" de la ligne avec
}


void remplir(int *tab, int x, int y)    //on est dans la fonction qui parcours le fichier pour stocker caractère par caractère l'image dans le tableau
{
    int i = 0;
    int j = 0;
    fseek(fichier, 9, SEEK_SET);    //on se positionne au 9e caractère du fichier, là où commence l'image
    for (; i < x; i++)    //on se positionne à la 1re ligne du tableau
    {
        for (j=0; j < y; j++)   //on parcours la 1er ligne du tableau
        {
            tab[i * y + j] = fgetc(fichier);    //le caractère lu va aller dans la case du tableau qui lui est attribuer
        }   //i*y+j permet de parcourir le tabeau case par case car à une nouvelle ligne la numérotation des case ne revient pas à 0 à chaque debut de ligne
    }
}


void center(int y, int b)   //on est dans la fonction qui permet de centrer l'image
{
    int a = (80 - y) / 2;   //on calcul à quel caractère de la ligne il faut commencer à affiché l'image
    gotoxy(b, a);   //on se positionne au coordonnée {a, b} dans le shell
}


void affiche(int *tab, int x, int y)    //on est dans la fonction qui permet d'affiché l'image et donc les caractère stocker dans le tableau
{
    int i = 0;
    int b = (25 - x) / 2;   //on calcul à quelle ligne on va se placer pour que l'image soit centrer
    for (; i < x; i++)    //on parcours chaque ligne du tableau
    {
        center(y, b);   //on appelle la fonction centrer pour commencer à affiché au bonne endroit pour centrer l'image dans le shell
        b++;    //on incrémente b pour commencer à écrire à la ligne suivante au même endroit mais une ligne en dessous
        for (int j = 0; j < y-1; j++)   //on parcours chaque caractère de la ligne
        {
            printf("%c",tab[i*y+j]);    //on affiche chaque caractère de l'image stocker dans le tableau
        }
    }
}

void quit(char q)   //on est dans la fonction qui quitte le programme si un touche du clavier est enfoncer
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
