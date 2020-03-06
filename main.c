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
            printf("JUSTE");
        }
        else printf("Mot de passe incorect\n");
        system("Pause");
    }
    else {
        printf("Utilisateur non trouve\nVoulez vous creer un compte ?");
        scanf("%d", &Choix);
        if (Choix == 1) creerUnCompte();
        else printf("Choix incorect");
    }
    system("Pause");
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
            printf("%c", GlobalUser);
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
