#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "entree.h"
#include "Exia_Saver.h"


void PrintStats(Input input[]);



void ReadStats(Input input[]) {
    FILE *fichier = NULL;
    fichier = fopen("stats.txt", "r");
    if (fichier != NULL) {
        char log[50] = "";
        int i = 0;
        while (fgets(log, 50, fichier) != NULL) {
            strcpy(input[i].date, strtok(log, " "));
            strcpy(input[i].heure, strtok(NULL, "  "));
            strtok(NULL, "  ");
            strcpy(input[i].type, strtok(NULL, "  "));
            strcpy(input[i].parametre, strtok(NULL, "  "));
            i++;
        }
    }
    fclose(fichier);
}

void triDate(Input input[]) {
    int i = 0, tri = 0;
    while (tri == 0) {
        tri = 1;
        for (i = 0; i < 100; i++) {
            if (strcmp(input[i].date, input[i + 1].date) > 0) {
                char echangeDate[11];
                strcpy(echangeDate, input[i].date);
                strcpy(input[i].date, input[i + 1].date);
                strcpy(input[i + 1].date, echangeDate);

                char echangeHeure[11];
                strcpy(echangeHeure, input[i].heure);
                strcpy(input[i].heure, input[i + 1].heure);
                strcpy(input[i + 1].heure, echangeHeure);

                char echangeType[6];
                strcpy(echangeType, input[i].type);
                strcpy(input[i].type, input[i + 1].type);
                strcpy(input[i + 1].type, echangeType);

                char echangeParametre[100];
                strcpy(echangeParametre, input[i].parametre);
                strcpy(input[i].parametre, input[i + 1].parametre);
                strcpy(input[i + 1].parametre, echangeParametre);
                tri = 0;
            }
        }
    }
    PrintStats(input);
}

void triHeure(Input input[]) {
    int k = 0, trie = 0;
    while (trie == 0) {
        trie = 1;
        for (k = 0; k < 100; k++) {
            if (strcmp(input[k].heure, input[k + 1].heure) > 0) {
                char echangeDate[11];
                strcpy(echangeDate, input[k].date);
                strcpy(input[k].date, input[k + 1].date);
                strcpy(input[k + 1].date, echangeDate);

                char echangeHeure[11];
                strcpy(echangeHeure, input[k].heure);
                strcpy(input[k].heure, input[k + 1].heure);
                strcpy(input[k + 1].heure, echangeHeure);

                char echangeType[6];
                strcpy(echangeType, input[k].type);
                strcpy(input[k].type, input[k + 1].type);
                strcpy(input[k + 1].type, echangeType);

                char echangeParametre[100];
                strcpy(echangeParametre, input[k].parametre);
                strcpy(input[k].parametre, input[k + 1].parametre);
                strcpy(input[k + 1].parametre, echangeParametre);
                trie = 0;
            }
        }
    }
    PrintStats(input);
}

void PrintStats(Input input[]) {
    int i;
    for (i = 0; i < 100; i++) {

        printf("%s  ", input[i].date);
        printf("%s  ", input[i].heure);
        printf("%s  ", input[i].type);
        printf("%s  ", input[i].parametre);
        printf("\n  ");
    }
}

void FinalCounter(Input input[], int choice) {
    int i, type1 = 0, type2 = 0, type3 = 0, total=0;
    for (i = 0; i < 100; i++) {
        switch ((int) input[i].type[0]) {
            case 49: //code ASCII pour 1
                type1++;
                break;
            case 50:
                type2++;
                break;
            case 51:
                type3++;
                break;
        }
    }
    switch (choice) {
        case 1:
            printf("type 1: %d , type 2 : %d , type 3 : %d \n", type1, type2, type3);
            break;
        case 2:
            total = type1 + type2 + type3;
            printf("Sur un total de %d executions, il y a eu %d pourcent de type statique, %d de type dynamique et %d de type interactif\n",total, ((type1*100)/total),((type2*100)/total),((type3*100)/total));
            break;

    }
}


int stats() {
	    system("clear");

    int choice=0;
    //char typeWrite = '3';
    //char parametreWrite[10] = "ex1.pbm";
    Input newInput[100] = {0};
    //WriteStats(typeWrite, parametreWrite);
    ReadStats(newInput);
    printf("Veuillez saisir l'option desiree:\n\n          -1 pour afficher les entrees triees par date\n\n          -2 pour afficher les entrees triees par heure\n\n          -3 pour afficher les nombres d'executions\n\n          -4 pour afficher les statistiques d'executions\n\nVotre choix (appuyer ensuite sur entrée) : ");
    scanf("%d",&choice);
    while(choice != 1 && choice != 2 && choice != 3 && choice != 4)
    {
    system("clear");
    printf("\nTu te calme et tu rentre ce qui est possible d'entrer et ne cherche pas il n'y a pas d'ester eggs et 42 ne marche pas alors rentre 1, 2, 3, ou 4 !!!!!\n\n");
    printf("Veuillez saisir l'option desiree:\n\n          -1 pour afficher les entrees triees par date\n\n          -2 pour afficher les entrees triees par heure\n\n          -3 pour afficher les nombres d'executions\n\n          -4 pour afficher les statistiques d'executions\n\nVotre choix (appuyer ensuite sur entrée) : ");
    scanf("%d",&choice);
    }
    switch(choice){
        case 1:
            triDate(newInput);
            break;
        case 2:
            triHeure(newInput);
            break;
        case 3:
            FinalCounter(newInput,1);
            break;
        case 4:
            FinalCounter(newInput,2);
            break;
    }
    return 0;
}
