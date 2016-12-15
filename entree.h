
typedef struct Input Input;
struct Input{
    char date[11];
    char heure[11];
    char type[6];
    char parametre[100]; //le nom de nos fichier ne depassera pas les 10 caractere et les dimensions non plus
};
