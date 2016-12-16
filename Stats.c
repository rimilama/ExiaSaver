#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "entree.h"
#include "Exia_Saver.h"


void PrintStats(Input input[]);



void ReadStats(Input input[]) { //fonction qui va lire le fichier stats.txt et remplir le tableau de la structure "input"
    FILE *fichier = NULL;
    fichier = fopen("stats.txt", "r");	//ouvre le ficher
    if (fichier != NULL) {
        char log[50] = "";
        int i = 0;
        while (fgets(log, 50, fichier) != NULL) { // copie tour a tour chaque ligne du fichier dans la chaine de caractere "log" jusqu'a arriver a la fin de celui ci
            strcpy(input[i].date, strtok(log, " ")); //copie la première partie de "log" jusqu'a caractere "  " (espace) dans le string date
            strcpy(input[i].heure, strtok(NULL, "  "));	//fait de meme pour l'heure, le type et le parametre
            strtok(NULL, "  ");				//on ne recupere pas la mot "type" du fichier car il ne nous servira pas
            strcpy(input[i].type, strtok(NULL, "  "));
            strcpy(input[i].parametre, strtok(NULL, "  "));
            i++;
        }
    }
    fclose(fichier);	//ferme le fichier
}

void triDate(Input input[]) { 	//tri a bulle optimise qui tri par date
    int i = 0, tri = 0;	//la variable tri permet d'optimiser le tri en observant si le tableau est deja trié
    while (tri == 0) {
        tri = 1;
        for (i = 0; i < 100; i++) {
            if (strcmp(input[i].date, input[i + 1].date) > 0) { //compare les string date
                char echangeDate[11];				//echange toutes les entres des tableaux date heure type et parametre
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
                tri = 0;	//si un echange est effectue, on considere que le tri n'est pas termine
            }
        }
    }
    PrintStats(input);	//appel de la fonction qui affiche le tableau input qui est trie
}

void triHeure(Input input[]) {	//meme fonction qu'au dessus mais par heure
    int k = 0, trie = 0;
    while (trie == 0) {
        trie = 1;
        for (k = 0; k < 100; k++) {
            if (strcmp(input[k].heure, input[k + 1].heure) > 0) {	//compare les heures
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

void PrintStats(Input input[]) {	//fonction qui affiche la structure input
    int i;
    for (i = 0; i < 100; i++) {		//simple boucle pour parcourir tout le tableau d'input

        printf("%s  ", input[i].date);
        printf("%s  ", input[i].heure);
        printf("%s  ", input[i].type);
        printf("%s  ", input[i].parametre);
        printf("\n  ");
    }
}

void FinalCounter(Input input[], int choice) {	//fonction qui parcourt tout le tableau et compte quel type est effectue a chaque fois et d'afficher soit le nombre de chaque type ou les presente sous forme de pourcentage
    int i, type1 = 0, type2 = 0, type3 = 0, total=0;
    for (i = 0; i < 100; i++) {
        switch ((int) input[i].type[0]) {	//switch qui permet de determiner quel type est utilisé
            case 49: //code ASCII pour 1
                type1++;
                break;
            case 50: //code ASCII pour 2
                type2++;
                break;
            case 51: //code ASCII pour 3
                type3++;
                break;
        }
    }
    switch (choice) { //en fonction du choix de l'utilisateur, affiche soit le nombre total d'utilisations de chaque type, soit les pourcentages d'utlisations
        case 1:
            printf("type 1: %d , type 2 : %d , type 3 : %d \n", type1, type2, type3);
            break;
        case 2:
            total = type1 + type2 + type3;
            printf("Sur un total de %d executions, il y a eu %d pourcent de type statique, %d de type dynamique et %d de type interactif\n",total, ((type1*100)/total),((type2*100)/total),((type3*100)/total));
            break;

    }
}


int stats() { //fonction lance si l'utilisateur a choisit d'afficher les stats avec la commande ./Exia_Saver -stats (voir dans Exia_Saver)
	    system("clear");

    int choice=0;
    Input newInput[100] = {0}; //crée le tableau qui va contenir toutes les entrees
    ReadStats(newInput); //rempli le tableau a partir du fichier stats.txt
    printf("Veuillez saisir l'option desiree:\n\n          -1 pour afficher les entrees triees par date\n\n          -2 pour afficher les entrees triees par heure\n\n          -3 pour afficher les nombres d'executions\n\n          -4 pour afficher les statistiques d'executions\n\nVotre choix (appuyer ensuite sur entrée) : ");
    scanf("%d",&choice); //permet a l'utilisateur de choisir quels stats il veut voir
    while(choice != 1 && choice != 2 && choice != 3 && choice != 4) //permet de controler que l'utilisateur donne un nombre entre 1 et 4
    {
    system("clear");
    printf("\nTu te calme et tu rentre ce qui est possible d'entrer et ne cherche pas il n'y a pas d'ester eggs et 42 ne marche pas alors rentre 1, 2, 3, ou 4 !!!!!\n\n");
    printf("Veuillez saisir l'option desiree:\n\n          -1 pour afficher les entrees triees par date\n\n          -2 pour afficher les entrees triees par heure\n\n          -3 pour afficher les nombres d'executions\n\n          -4 pour afficher les statistiques d'executions\n\nVotre choix (appuyer ensuite sur entrée) : ");
    scanf("%d",&choice);
    }
    switch(choice){	//permet de lancer l'affichage adapte a sa demande
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