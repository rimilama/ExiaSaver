#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "Statique.h"
#include "pbm.h"
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <string.h>
#define gotoxy(x, y) printf("\033[%d;%dH", (x), (y))


FILE *fichier = NULL;


void statique(int random) {
    system("clear");

    pid_t pid;
    pid=fork();
    if (pid == 0)
    {
    fichier=(FILE*)malloc(sizeof(int));
    int x = 0;
    int y = 0;
    char q = '\0';
    choix_pbm(random);
    if (fichier != NULL) {

        taille(&x, &y);
        int tab[x][y];
        remplir((int *) tab, x, y);
        pbm((int *) tab, x, y);
        affiche((int *) tab, x, y);
        fclose(fichier);
        fichier = NULL;
        quit(q);
        free(fichier);

    } else {
        printf("Impossible d'ouvrir le fichier .pbm\n");
        quit(q);
        }
    }
    else{
            wait(NULL);



   }

}


void choix_pbm(int random) {

    switch (random) {
        case 1:
            fichier = fopen("pbm/OW.pbm", "r");
            break;
        case 2:
            fichier = fopen("pbm/ghost.pbm", "r");
            break;
        case 3:
            fichier = fopen("pbm/genji.pbm", "r");
            break;
        case 4:
            fichier = fopen("pbm/issac.pbm", "r");
            break;
        case 5:
            fichier = fopen("pbm/SW.pbm", "r");
            break;
        default:
            fichier = fopen("pbm/castle.pbm", "r");
            break;
    }
}


void taille(int *x, int *y) {
    fseek(fichier, 3, SEEK_SET);
    fscanf(fichier, "%d %d", x, y);
    *y = *y +1;
}


void remplir(int *tab, int x, int y) {
    int i = 0;
    int j = 0;
    fseek(fichier, 9, SEEK_SET);
    for (; i < x; i++) {
        for (j=0; j < y; j++) {
            tab[i * y + j] = fgetc(fichier);
        }
    }
}


void center(int y, int b) {

    int a = (80 - y) / 2;
    gotoxy(b, a);
}


void affiche(int *tab, int x, int y) {
    int i = 0;
    int b = (25 - x) / 2;
    for (; i < x; i++) {
        center(y, b);
        b++;
        for (int j = 0; j < y-1; j++)
        {
            printf("%c",tab[i*y+j]);
        }
    }
}

void quit(char q) {
    initscr();
    cbreak();
    noecho();
    q = (char) getchar();
    if (q != '\0') {
        system("clear");
        echo();
        nocbreak();
        endwin();
    }
}

