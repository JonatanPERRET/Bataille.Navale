#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>

void creerUnCompte (){
    char Name[48];
    char Prenom[48];
    char MDP[48];

    printf("Creer un compte, Entrez vos identifiants :\n");
    printf("Nom :\n");
    scanf("%s", &Name);
    printf("Prenom :\n");
    scanf("%s", &Prenom);
    printf("Mot de passe :\n");
    scanf("%s", &MDP);

    FILE *User = NULL;
    User = fopen(Name, "w");
    fprintf(User, "%s\n%s\n%s", Name, Prenom, MDP);
    fclose(User);
}


int main() {

    int Choix = 0;
    system("cls");
    printf("Bonjour,\nBienvenue dans le jeu de la bataille navale.\nChoisissez une option :");
    printf("\n1 - Se connecter\n2 - Creer un compte\n");
    scanf("%d", &Choix);
    switch (Choix){
        case 1:
            printf("Entrez vos identifiants :");
            break;
        case 2:
            system("cls");
            creerUnCompte();
            main();
            break;
        default:
            printf("Choix invalide");
            system("cls");
    }

    return 0;
}
