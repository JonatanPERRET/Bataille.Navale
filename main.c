#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>


void creerUnCompte (){
    char UserName[48];
    char Name[48];
    char Prenom[48];
    char MDP[48];

    printf("Creer un compte, Entrez vos identifiants :\n");
    printf("Nom d'utilisateur :\n");
    scanf("%s", UserName);
    printf("Nom :\n");
    scanf("%s", &Name);
    printf("Prenom :\n");
    scanf("%s", &Prenom);
    printf("Mot de passe :\n");
    scanf("%s", &MDP);

    FILE *User = NULL;
    User = fopen(UserName, "w");
    fprintf(User, "%s\n%s\n%s\n%s", UserName, Name, Prenom, MDP);
    fclose(User);
}
char seConnecter(){
    char UserName[48] = {0};
    char Name[48] = {0};
    char Prenom[48] = {0};
    char MDP[48] = {0};
    char MDPVal[48] = {0};

    printf("Nom d'utilisateur :\n");
    scanf("%s", &UserName);
    FILE *User = NULL;
    User = fopen(UserName, "r+");
    if (User != NULL) {
        fscanf(User, "%s", UserName);
        fscanf(User, "%s", Name);
        fscanf(User, "%s", Prenom);
        fscanf(User, "%s", MDP);
        fclose(User);
        printf("Mot de passe :\n");
        scanf("%s", MDPVal);
        if (MDPVal == MDP){
            printf("JUSTE");
        }
        else printf("MDP incorect\n");
        system("Pause");
    }
    else printf("Utilisateur non trouve\n");
    system("Pause");
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
            seConnecter();
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
