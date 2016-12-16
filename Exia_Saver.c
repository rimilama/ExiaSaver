#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "Exia_Saver.h"
#include "Statique.h"
#include <string.h>
#include "Dynamique.h"
#include "Stats.h"
#include "Interactif.h"

int main(int argc, char *argv[])
{

    char pd[]="-stats";
    int Stats_vf;

    if (argv[1]!=NULL)
    {
        Stats_vf=strcmp(argv[1],pd);
        if(Stats_vf == 0)
        {
        stats();
        }
    }
    else{
    int a = 1;
    int b = 3;
    system("clear");
    int c = randm(a, b);
    choice(c);
    }
}


int randm(int a, int b)
{
    int Nombrealea = 0;
    srand (time (NULL));
    Nombrealea = (a+(rand()%(b-a+1)));
    return Nombrealea;
}


void choice(int c)
{
    int e = 1;
    int f = 5;
    int d;
    char folder[10]="";
    switch (c)
    {
        case  1 :
            d = randm(e, f);
            statique(d);
            switch (d)
            {
            case 1:
                strcpy(folder,"OW.pbm");
                break;
            case 2:
                 strcpy(folder,"ghost.pbm");
                break;
            case 3:
                strcpy(folder,"genji.pbm");
                break;
            case 4:
                strcpy(folder,"isaac.pbm");
                break;
            case 5:
                strcpy(folder,"SW.pbm");
                break;
            default:
                strcpy(folder , "castle.pbm");
                break;
            }
            WriteStats(1,folder);

            break;
        case 2 :
            dynamique();
            WriteStats(2,"5x3");

            break;
        case 3:
            interactif();
            WriteStats(3, "meintenance");
        }
}

void WriteStats(int type, char tab[]) {
    FILE *fichier = NULL;
    fichier = fopen("stats.txt", "a");
    if (fichier != NULL) {
        time_t temps; //permet de recuperer l'heure
        struct tm date;
        char format[22];
        time(&temps);
        date = *localtime(&temps);
        strftime(format, 22, "%Y/%m/%d %X", &date); //affichage AAAA/MM/JJ/HH:MM:SS
        //printf("%s  type %c  %s\n", format, type, tab);
        fprintf(fichier, "%s  type %d  %s\n", format, type, tab);
        fclose(fichier);
    } else {
        printf("Un probleme est survenu avec le fonction stat");
    }

}
