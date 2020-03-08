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
void seConnecter(){
    char UserName[48] = {0};
    char Name[48] = {0};
    char Prenom[48] = {0};
    char MDP[48] = {0};
    char MDPVal[48] = {0};
    int VerifMDP = 0;
    int Choix = 0;
    system("cls");
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
        system("cls");
        printf("Mot de passe :\n");
        scanf("%s", MDPVal);
        for (int i = 0; i < 48; i++) {
            if (MDPVal[i] == MDP[i]) {
                VerifMDP++;
            }
        }
        if (VerifMDP == 48){
            FILE *User = NULL;
            remove("ActualUser");
            User = fopen("ActualUser", "w");

            fprintf(User, "%s", UserName);
            fclose(User);

        }
        else printf("Mot de passe incorect\n");
    }
    else {
        printf("Utilisateur non trouve\nVoulez vous creer un compte ? (1/0)\n");
        scanf("%d", &Choix);
        if (Choix == 1) creerUnCompte();
        else {
            printf("\nVoulez vous fermer l'application ?\n(1/0)");
            scanf("%d", &Choix);
            if(Choix == 1){
                exit(0);
            }
            else {
                printf("Alors, retour au menu ");
                seConnecter();
            }
        }
    }
}

void menuPrincipal(){
    int Choix = 0;
    system("cls");
    printf("Bienvenu au menu principal,\nQue voulez vous faire ?\n");
    printf("1 - Jouer une partie\n2 - Afficher l'aide\n3 - \n");
    scanf ("%d", &Choix);
    switch (Choix){
        case 1: {
            system("cls");
            printf("Jouer une partie\n");
            break;
        }
        case 2:{
            system("cls");
            printf("La bataille navale oppose deux joueurs qui s'affrontent. \nChacun a une flotte composee de 5 bateaux, qui sont, en general, les suivants : \n1 porte-avion (5 cases), 1 croiseur (4 cases), 1 contre-torpilleur (3 cases), \n1 sous-marin (3 cases), 1 torpilleur (2 cases). \nLes bateaux ne doivent pas etre colles entre eux.\n Le but du jeux est d'abbatre tout les bateaux enemis");
            printf("\nAppuyer sur 1 pour revenir au menu principale\n");
            scanf("%d", &Choix);
            if (Choix == 1) menuPrincipal();
        }
    }

}

int main() {

    char GlobalUser[48] = {0};
    int Choix = 0;
    system("cls");
    printf("Bonjour,\nBienvenue dans le jeu de la bataille navale.\nChoisissez une option :");
    printf("\n1 - Se connecter\n2 - Creer un compte\n");
    scanf("%d", &Choix);
    switch (Choix){
        case 1:
            printf("Entrez vos identifiants :");
            seConnecter();
            menuPrincipal();
            break;
        case 2:
            system("cls");
            creerUnCompte();
            main();
            break;
        default:
            printf("Choix invalide");
            system("cls");
            break;
    }

    return 0;
}
