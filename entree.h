
typedef struct Input Input; //permet d'ecrire juste Input et non struct Input dans le .c
struct Input{	//structure qui contient les 4 tableau suivant
    char date[11];
    char heure[11];
    char type[6];
    char parametre[100]; 
};
