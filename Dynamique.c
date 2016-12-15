#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "Dynamique.h"
#include "pbm.h"
#define gotoxy(x, y) printf("\033[%d;%dH", (x), (y))


FILE* fichier_d = NULL;

void dynamique()
{
    int RefreshT = 2;
    int ctrlc = 0;
    int tab[8] = {0};
    int a = 20,b = 20,c = 7,d = 13;
    int x, y;
    system("clear");
    while (ctrlc != 1)
    {
        int e = 20, f = 67;
        c = 7;
        d = 13;
        take_time((int *) tab);
        for (int z=0; z<=7; z++)
        {
            choix(tab[z]);
            if (fichier_d != NULL)
            {
                taille_d(&x, &y);
                int img[x][y];
                remplir_d((int *) img, x, y);
                pbm((int *) img, x, y);
                affiche_d((int *) img, x, y, c, d);
                c = 7;
                d = d + 7;
                fclose(fichier_d);
                fichier_d = NULL;
            }
            else
            {
                printf("Les fichiers .pbm ne peuvent s'ouvrir\n");
                exit(1);
            }
        }
        gotoxy(a,b);
        printf("Cet écran sera actualisé dans quelques secondes \n");

        for (int i=0; i<RefreshT; i++)
        {
            sleep(1);
            gotoxy(e,f);
            printf(".\n");
            f++;
        }
        f=f-RefreshT;
        gotoxy(e, f);
        printf("                            ");
        system("clear");
    }
}

void take_time(int * tab) {
    time_t secondes;
    struct tm instant;
    time(&secondes);
    instant = *localtime(&secondes);
    int S1 = (instant.tm_sec) / 10;
    int S2 = (instant.tm_sec) - (S1 * 10);
    int M1 = (instant.tm_min) / 10;
    int M2 = (instant.tm_min) - (M1 * 10);
    int H1 = (instant.tm_hour) / 10;
    int H2 = (instant.tm_hour) - (H1 * 10);
    tab[0] = H1;
    tab[1] = H2;
    tab[2] = 15;
    tab[3] = M1;
    tab[4] = M2;
    tab[5] = 15;
    tab[6] = S1;
    tab[7] = S2;
}


void choix(int a) {
    switch (a) {
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
    }
}


void taille_d(int *x, int *y) {
    if (fichier_d != NULL)
    {
        fseek(fichier_d, 3, SEEK_SET);
        fscanf(fichier_d, "%d %d", y, x);
    }
}

void remplir_d(int *img, int x, int y) {
    int i = 0;
    int j = 0;
    char test[20];
    fseek(fichier_d, 7, SEEK_SET);
    for (; i <x; i++) {
        fgets(test, 20, fichier_d);
        for (j=0; j <y; j++) {
            img[i * y + j] = test[j];

        }
    }
}


void affiche_d(int *img, int x, int y, int c, int d) {
    int i = 0;
    for (; i < x; i++) {
        gotoxy(c,d);

        for (int j = 0; j < y; j++)
        {
            int l = img[i*y+j];
            if(l == 48 || l == 32 || l == 10)
            {
                printf("%c",l);
            }
        }
        c++;
    }
}






