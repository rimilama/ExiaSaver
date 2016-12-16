#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

#include "Exia_Saver.h"
#include "Statique.h"
#include "Dynamique.h"
#include "Stats.h"
#include "Interactif.h"

int main(int argc, char *argv[])
{

    char lol[]="-stats";  // définiton de l'argument -stats
    int Stats_vf;       //création de la variable pour tester  l'argument

    if (argv[1]!=NULL)
    {
        Stats_vf=strcmp(argv[1],lol);   // test l'argument , si celui-ci vaut -stats , il rentre dans la boucle sinon il lance le screen saver
        if(Stats_vf == 0)
        {
        stats();
        }
    }
    else{
    int a = 1;    //a sert de borne inférieur au randm
    int b = 3;    //b sert de borne supérieur au randm
    system("clear");
    int c = randm(a, b);    //varaible pour contenir le résultat du randm
    choice(c);
    }
}


int randm(int a, int b)   // début de la fonction randm
{
    int Nombrealea = 0;   // initiallisation de la variable
    srand (time (NULL));  //initillisation de la fonction sur le temps actuel
    Nombrealea = (a+(rand()%(b-a+1)));    //Utilisation de rand pour générer un nombre entre 1 et 3
    return Nombrealea;
}


void choice(int c) // début de la fonction permettant de choisir le screen saver
{
    int e = 1;
    int f = 5;
    int d;
    char folder[10]=""; // on défini en dehors du switch le tableau utile pour stocker le nom des fichiers pour les stats
    switch (c)    //le switch test la valeur c (1, 2 ,3)
    {
        case  1 :   //le cas 1 constitue le lançement du screen saver 1
            d = randm(e, f);  //on relance un randm pour récupérer un nombre entre 1 et 5
            statique(d);  //Appel au programme statique
            switch (d)    //ce switch est un test untile au stats , il test la valeur de d pour récupérer le nom de l'image
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
            WriteStats(1,folder); // Appel de la fonction pour écrire les stats dans un  fichier txt ( créée si il n'existe pas)

            break;    //le cas 2 constitue le lançement du screen saver 2
        case 2 :
            WriteStats(2,"5x3"); // Appel de la fonction pour écrire les stats dans un  fichier txt ( créée si il n'existe pas)
            dynamique();    //Appel de la fonction  Dynamique
            break;
        case 3:
            interactif();   // Appel de la fonction interactif
            WriteStats(3, "maintenance");   // Appel de la fonction pour écrire les stats dans un  fichier txt ( créée si il n'existe pas)
        }
}

void WriteStats(int type, char tab[]) {
    FILE *fichier = NULL;  // initiallisation du pointeur
    fichier = fopen("stats.txt", "a");//ouverture du fichier txt , sinon l'ajoute
    if (fichier != NULL) {
        time_t temps; //permet de recuperer l'heure
        struct tm date;
        char format[22];
        time(&temps);
        date = *localtime(&temps);    // écrit l'heure dans le fichier
        strftime(format, 22, "%Y/%m/%d %X", &date);   //écrit la date dans le fichier
        fprintf(fichier, "%s  type %d  %s\n", format, type, tab);   //écrit le type de fichier ainsi que le nom du fichier utilisé
        fclose(fichier);
    } else {
        printf("Un probleme est survenu avec le fonction stat");
    }

}
