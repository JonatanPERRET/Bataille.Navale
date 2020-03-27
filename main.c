/*
 * Projet : Bataille Navale
 * Auteur : Jonatan PERRET
 * Version : 0.5
 * Date : 16.03.20
 */
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>

void creerUnCompte (){
    //déclaration des variables
    char UserName[48];
    char Name[48];
    char Prenom[48];
    char MDP[48];
    //Demande les valeurs pour créer le compte
    printf("Creer un compte, Entrez vos identifiants : (sans espaces)\n");
    printf("Nom d'utilisateur :\n");
    scanf("%s", UserName);
    printf("Nom :\n");
    scanf("%s", Name);
    printf("Prenom :\n");
    scanf("%s", Prenom);
    printf("Mot de passe :\n");
    scanf("%s", MDP);
    //création du fichier d'utilisateur
    FILE *User = NULL;
    User = fopen(UserName, "w");
    fprintf(User, "%s\n%s\n%s\n%s", UserName, Name, Prenom, MDP);
    fclose(User);
    //Logage de la création du compte
    FILE *Loger;
    Loger = fopen("LOG", "a");
    fprintf(Loger, "\nL'utilisateur : %s a creer son compte", UserName);
    fclose(Loger);
}
void seConnecter(){
    //déclaration des variables
    char UserName[48] = {0};
    char Name[48] = {0};
    char Prenom[48] = {0};
    char MDP[48] = {0};
    char MDPVal[48] = {0};
    int VerifMDP = 0;
    int Choix = 0;
    system("cls"); //efface l'intérface
    //Demande à l'utilisateur le nom d'utilisateur pour se connecter
    printf("Nom d'utilisateur :\n");
    scanf("%s", UserName);
    //ouvre le fichier d'utilisateur et met les valeurs dans des variables
    FILE *User = NULL;
    User = fopen(UserName, "r+");
    if (User != NULL) {// verification si l'utilisateur existe
        fscanf(User, "%s", UserName);
        fscanf(User, "%s", Name);
        fscanf(User, "%s", Prenom);
        fscanf(User, "%s", MDP);
        fclose(User);
        system("cls");
        printf("Mot de passe :\n");//demande le mot de passe
        scanf("%s", MDPVal);
        for (int i = 0; i < 48; i++) {//Verification si le mot de passe est juste
            if (MDPVal[i] == MDP[i]) {
                VerifMDP++;
            }
        }
        if (VerifMDP == 48){
            FILE *User2 = NULL;
            remove("ActualUser");//écrit das le fichier l'utilisateur actuel
            User2 = fopen("ActualUser", "w");
            fprintf(User2, "%s", UserName);
            fclose(User2);

        }
        else {
            printf("Mot de passe incorect\n"); //si mot de passe incorect
            printf("Appuyer pour vous reconnecter\n");
            system("Pause");
            seConnecter();
        }
        }
    else {//si l'utilisateur n'existe pas
        printf("Utilisateur non trouve\nVoulez vous creer un compte ? (1/0)\n");//demande si l'utilisateur veut créer un compte
        scanf("%d", &Choix);
        if (Choix == 1) creerUnCompte();//renvoi à la fonction pour créer un compte
        else {
            printf("\nVoulez vous fermer l'application ?\n(1/0)");//Demande si on veut quitter l'application
            scanf("%d", &Choix);
            if(Choix == 1){
                exit(0);
            }
            else {
                printf("Alors, retour au menu ");//retour au menu
                seConnecter();
            }
        }
    }
    FILE *connecter;//Logage de la connexion
    connecter = fopen("LOG", "a");
    fprintf(connecter, "\nL'utilisateur : %s s'est connecté à son compte", UserName);
    fclose(connecter);
}
void jouerPartie (){
    //declaration des variables
    char ActualUser[48] = {0};
    char UserName[48] = {0};
    int Choix = 0;
    int Compteur = 0;
    int compteurJoueur = 0;
    int Scores = 0;
    int Vertical = 0;
    int Horizontal = 0;
    int ChoixTableau = 0;
    int TableauJeu1 [10][10] = {0, 0, 0, 0, 0, 0, 1, 0, 0, 0,//création du tableau de jeu
                                1, 1, 1, 1, 0, 0, 1, 0, 1, 0,
                                0, 0, 0, 0, 0, 0, 1, 0, 1, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 1, 1, 1,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 1, 1, 1, 1, 1, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int TableauJeu2 [10][10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 1, 0, 0, 0, 0, 0, 1, 1,
                                0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
                                0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
                                0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
                                0, 0, 1, 0, 0, 0, 0, 1, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 1, 1, 1, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int TableauJeu3 [10][10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 1, 1, 1, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 1, 1, 1, 1, 1, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                0, 0, 1, 1, 0, 0, 0, 0, 0, 1,
                                0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
                                0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
                                0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
                                0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    FILE *Actualuser;//Logage de la partie
    Actualuser = fopen("ActualUser", "r+");
    fscanf(Actualuser, "%s", ActualUser);
    fclose(Actualuser);
    for (int i = 0; i < 48; i++){
        UserName[i] = ActualUser[i];
    }
    FILE *JouerPartie;//Logage de Jouer partie
    JouerPartie = fopen("LOG", "a");
    fprintf(JouerPartie, "\nL'utilisateur : %s a lance une partie de bataille navale", UserName);
    fclose(JouerPartie);
    srand((unsigned)time(NULL));
    ChoixTableau = 1 + rand() % 3;
    printf("%d", ChoixTableau);
    system("Pause");
    switch(ChoixTableau) {
        case 1:

            do {
                system("cls");//efface l'interface
                printf("Voici le plateau :\n");
                printf("   1 2 3 4 5 6 7 8 9 10\n");
                //Affichage du tableau de jeu à l'utilisateur

                for (int i = 0; i < 10; i++) {
                    printf("%2d ", i + 1);
                    for (int j = 0; j < 10; j++) {
                        if ((TableauJeu1[4][7] == 3) && (TableauJeu1[4][8] == 3) &&
                            (TableauJeu1[4][9] == 3)) {//verification si le bateau est coulé
                            TableauJeu1[4][7] = 5;
                            TableauJeu1[4][8] = 5;
                            TableauJeu1[4][9] = 5;
                            Compteur++;
                        }
                        if ((TableauJeu1[1][0] == 3) && (TableauJeu1[1][1] == 3) && (TableauJeu1[1][2] == 3) &&
                            (TableauJeu1[1][3] == 3)) {//verification si le bateau est coulé
                            TableauJeu1[1][0] = 5;
                            TableauJeu1[1][1] = 5;
                            TableauJeu1[1][2] = 5;
                            TableauJeu1[1][3] = 5;
                            Compteur++;
                        }
                        if ((TableauJeu1[0][6] == 3) && (TableauJeu1[1][6] == 3) &&
                            (TableauJeu1[2][6] == 3)) {//verification si le bateau est coulé
                            TableauJeu1[0][6] = 5;
                            TableauJeu1[1][6] = 5;
                            TableauJeu1[2][6] = 5;
                            Compteur++;
                        }
                        if ((TableauJeu1[8][4] == 3) && (TableauJeu1[8][5] == 3) && (TableauJeu1[8][6] == 3) &&
                            (TableauJeu1[8][7] == 3) && (TableauJeu1[8][8] == 3)) {//verification si le bateau est coulé
                            TableauJeu1[8][4] = 5;
                            TableauJeu1[8][5] = 5;
                            TableauJeu1[8][6] = 5;
                            TableauJeu1[8][7] = 5;
                            TableauJeu1[8][8] = 5;
                            Compteur++;
                        }
                        if ((TableauJeu1[1][8] == 3) && (TableauJeu1[2][8] == 3)) {//verification si le bateau est coulé
                            TableauJeu1[1][8] = 5;
                            TableauJeu1[2][8] = 5;
                            Compteur++;
                        }
                        //affichage du tableau en fonction de la valeur des cases
                        if (TableauJeu1[i][j] == 0) printf("%c ", 255);
                        if (TableauJeu1[i][j] == 1) printf("%c ", 255);
                        if (TableauJeu1[i][j] == 2) printf("\033[34m%c \033[0m", 219);
                        if (TableauJeu1[i][j] == 3) printf("\033[31m%c \033[0m", 219);
                        if (TableauJeu1[i][j] == 5) printf("\033[32m%c \033[0m", 219);
                    }
                    printf("\n");//affichage du retour à la ligne
                }
                if (Compteur < 5) {
                    printf("Ou voulez vous tirer ?\nVertical : (11 pour l'aide, 12 pour quitter)\n");//demande à l'utilisateur où il veut tirer
                    scanf("%d", &Vertical);
                    if (Vertical < 11) {//Si l'utilisateur entre une valeur pour afficher l'aide ou quitter
                        printf("Horizontal :\n");
                        scanf("%d", &Horizontal);
                        compteurJoueur += 1;
                        Scores++;
                        if (TableauJeu1[Vertical - 1][Horizontal - 1] == 1)
                            TableauJeu1[Vertical - 1][Horizontal - 1] = 3;
                        if (TableauJeu1[Vertical - 1][Horizontal - 1] == 0)
                            TableauJeu1[Vertical - 1][Horizontal - 1] = 2;
                        FILE *JouerPartie;//Logage de Jouer partie
                        JouerPartie = fopen("LOG", "a");
                        fprintf(JouerPartie,
                                "\nL'utilisateur : %s a tiré au coordonnée : Vertical : %d, Horizontal : %d",
                                UserName, Vertical, Horizontal);
                        fclose(JouerPartie);
                    }
                    if (Vertical == 11) {//affichage de l'aide en jeu
                        FILE *Afficherlaide;//Logage de affichage de l'aide
                        Afficherlaide = fopen("LOG", "a");
                        fprintf(Afficherlaide, "\nL'utilisateur : %s a affiché l'aide en jeu", UserName);
                        fclose(Afficherlaide);
                        system("cls");
                        printf("La bataille navale oppose deux joueurs qui s'affrontent. \nChacun a une flotte composee de 5 bateaux, qui sont les suivants : \n1 porte-avion (5 cases), 1 croiseur (4 cases), 1 contre-torpilleur (3 cases), \n1 sous-marin (3 cases), 1 torpilleur (2 cases). \nLes bateaux ne doivent pas etre colles entre eux.\n Le but du jeux est d'abbatre tout les bateaux enemis\n");
                        system("Pause");
                    }
                } else { //affichage de l'écran quand on gagne
                    FILE *Gagner;//Logage de Jouer partie
                    Gagner = fopen("LOG", "a");
                    fprintf(Gagner, "\nL'utilisateur : %s a gagné une partie", UserName);
                    fclose(Gagner);
                    FILE *Score;
                    Score = fopen("SCORES", "a");
                    fprintf(Score, "\n%s : %d", UserName, Scores);
                    fclose(Score);
                    system("cls");
                    printf(" _    _ _____ _   _  _   _  ___________ \n"
                           "| |  | |_   _| \\ | || \\ | ||  ___| ___ \\\n"
                           "| |  | | | | |  \\| ||  \\| || |__ | |_/ /\n"
                           "| |/\\| | | | | . ` || . ` ||  __||    / \n"
                           "\\  /\\  /_| |_| |\\  || |\\  || |___| |\\ \\ \n"
                           " \\/  \\/ \\___/\\_| \\_/\\_| \\_/\\____/\\_| \\_|\n"
                           "                                        \n");
                    printf("Vous avez gagne\n1 - Rejouer\n2 - Renvenir au menu principal\n3 - Quitter\n");//demande à l'utilisateur si il veut rejouer, revenir au menu principal ou quitter
                    scanf("%d", &Choix);
                    switch (Choix) {
                        case 1:
                            jouerPartie();//rejouer
                            break;
                        case 2:
                            break;//revient au menu principale
                        case 3:
                            exit(EXIT_SUCCESS);//quitte le programme
                    }
                }
            } while ((Vertical < 12) && (Compteur < 5));//boucle pour jouer tant que l'on a pas gagné ou demandé de quitter
                     break;
        case 2:
            do {
                system("cls");//efface l'interface
                printf("Voici le plateau :\n");
                printf("   1 2 3 4 5 6 7 8 9 10\n");
                //Affichage du tableau de jeu à l'utilisateur

                for (int i = 0; i < 10; i++) {
                    printf("%2d ", i + 1);
                    for (int j = 0; j < 10; j++) {
                        if ((TableauJeu2[7][0] == 3) && (TableauJeu2[7][1] == 3) &&
                            (TableauJeu2[7][2] == 3)) {//verification si le bateau est coulé
                            TableauJeu2[7][0] = 5;
                            TableauJeu2[7][1] = 5;
                            TableauJeu2[7][2] = 5;
                            Compteur++;
                        }
                        if ((TableauJeu2[2][7] == 3) && (TableauJeu2[3][7] == 3) && (TableauJeu2[4][7] == 3) &&
                            (TableauJeu2[5][7] == 3)) {//verification si le bateau est coulé
                            TableauJeu2[2][7] = 5;
                            TableauJeu2[3][7] = 5;
                            TableauJeu2[4][7] = 5;
                            TableauJeu2[5][7] = 5;
                            Compteur++;
                        }
                        if ((TableauJeu2[8][6] == 3) && (TableauJeu2[8][7] == 3) &&
                            (TableauJeu2[8][8] == 3)) {//verification si le bateau est coulé
                            TableauJeu2[8][6] = 5;
                            TableauJeu2[8][7] = 5;
                            TableauJeu2[8][8] = 5;
                            Compteur++;
                        }
                        if ((TableauJeu2[1][2] == 3) && (TableauJeu2[2][2] == 3) && (TableauJeu2[3][2] == 3) &&
                            (TableauJeu2[4][2] == 3) && (TableauJeu2[5][2] == 3)) {//verification si le bateau est coulé
                            TableauJeu2[1][2] = 5;
                            TableauJeu2[2][2] = 5;
                            TableauJeu2[3][2] = 5;
                            TableauJeu2[4][2] = 5;
                            TableauJeu2[5][2] = 5;
                            Compteur++;
                        }
                        if ((TableauJeu2[1][8] == 3) && (TableauJeu2[1][9] == 3)) {//verification si le bateau est coulé
                            TableauJeu2[1][9] = 5;
                            TableauJeu2[1][8] = 5;
                            Compteur++;
                        }
                        //affichage du tableau en fonction de la valeur des cases
                        if (TableauJeu2[i][j] == 0) printf("%c ", 255);
                        if (TableauJeu2[i][j] == 1) printf("%c ", 255);
                        if (TableauJeu2[i][j] == 2) printf("\033[34m%c \033[0m", 219);
                        if (TableauJeu2[i][j] == 3) printf("\033[31m%c \033[0m", 219);
                        if (TableauJeu2[i][j] == 5) printf("\033[32m%c \033[0m", 219);
                    }
                    printf("\n");//affichage du retour à la ligne
                }
                if (Compteur < 5) {
                    printf("Ou voulez vous tirer ?\nVertical : (11 pour l'aide, 12 pour quitter)\n");//demande à l'utilisateur où il veut tirer
                    scanf("%d", &Vertical);
                    if (Vertical < 11) {//Si l'utilisateur entre une valeur pour afficher l'aide ou quitter
                        printf("Horizontal :\n");
                        scanf("%d", &Horizontal);
                        compteurJoueur += 1;
                        Scores++;
                        if (TableauJeu2[Vertical - 1][Horizontal - 1] == 1)
                            TableauJeu2[Vertical - 1][Horizontal - 1] = 3;
                        if (TableauJeu2[Vertical - 1][Horizontal - 1] == 0)
                            TableauJeu2[Vertical - 1][Horizontal - 1] = 2;
                        FILE *JouerPartie;//Logage de Jouer partie
                        JouerPartie = fopen("LOG", "a");
                        fprintf(JouerPartie,
                                "\nL'utilisateur : %s a tiré au coordonnée : Vertical : %d, Horizontal : %d",
                                UserName, Vertical, Horizontal);
                        fclose(JouerPartie);
                    }
                    if (Vertical == 11) {//affichage de l'aide en jeu
                        FILE *Afficherlaide;//Logage de affichage de l'aide
                        Afficherlaide = fopen("LOG", "a");
                        fprintf(Afficherlaide, "\nL'utilisateur : %s a affiché l'aide en jeu", UserName);
                        fclose(Afficherlaide);
                        system("cls");
                        printf("La bataille navale oppose deux joueurs qui s'affrontent. \nChacun a une flotte composee de 5 bateaux, qui sont les suivants : \n1 porte-avion (5 cases), 1 croiseur (4 cases), 1 contre-torpilleur (3 cases), \n1 sous-marin (3 cases), 1 torpilleur (2 cases). \nLes bateaux ne doivent pas etre colles entre eux.\n Le but du jeux est d'abbatre tout les bateaux enemis\n");
                        system("Pause");
                    }
                } else { //affichage de l'écran quand on gagne
                    FILE *Gagner;//Logage de Jouer partie
                    Gagner = fopen("LOG", "a");
                    fprintf(Gagner, "\nL'utilisateur : %s a gagné une partie", UserName);
                    fclose(Gagner);
                    FILE *Score;
                    Score = fopen("SCORES", "a");
                    fprintf(Score, "\n%s : %d", UserName, Scores);
                    fclose(Score);
                    system("cls");
                    printf(" _    _ _____ _   _  _   _  ___________ \n"
                           "| |  | |_   _| \\ | || \\ | ||  ___| ___ \\\n"
                           "| |  | | | | |  \\| ||  \\| || |__ | |_/ /\n"
                           "| |/\\| | | | | . ` || . ` ||  __||    / \n"
                           "\\  /\\  /_| |_| |\\  || |\\  || |___| |\\ \\ \n"
                           " \\/  \\/ \\___/\\_| \\_/\\_| \\_/\\____/\\_| \\_|\n"
                           "                                        \n");
                    printf("Vous avez gagne\n1 - Rejouer\n2 - Renvenir au menu principal\n3 - Quitter\n");//demande à l'utilisateur si il veut rejouer, revenir au menu principal ou quitter
                    scanf("%d", &Choix);
                    switch (Choix) {
                        case 1:
                            jouerPartie();//rejouer
                            break;
                        case 2:
                            break;//revient au menu principale
                        case 3:
                            exit(EXIT_SUCCESS);//quitte le programme
                    }
                }
            } while ((Vertical < 12) && (Compteur < 5));//boucle pour jouer tant que l'on a pas gagné ou demandé de quitter
            break;
        case 3:
            do {
                system("cls");//efface l'interface
                printf("Voici le plateau :\n");
                printf("   1 2 3 4 5 6 7 8 9 10\n");
                //Affichage du tableau de jeu à l'utilisateur

                for (int i = 0; i < 10; i++) {
                    printf("%2d ", i + 1);
                    for (int j = 0; j < 10; j++) {
                        if ((TableauJeu3[1][1] == 3) && (TableauJeu3[1][2] == 3) &&
                            (TableauJeu3[1][3] == 3)) {//verification si le bateau est coulé
                            TableauJeu3[1][1] = 5;
                            TableauJeu3[1][2] = 5;
                            TableauJeu3[1][3] = 5;
                            Compteur++;
                        }
                        if ((TableauJeu3[5][9] == 3) && (TableauJeu3[6][9] == 3) && (TableauJeu3[7][9] == 3) &&
                            (TableauJeu3[8][9] == 3)) {//verification si le bateau est coulé
                            TableauJeu3[5][9] = 5;
                            TableauJeu3[6][9] = 5;
                            TableauJeu3[7][9] = 5;
                            TableauJeu3[8][9] = 5;
                            Compteur++;
                        }
                        if ((TableauJeu3[6][5] == 3) && (TableauJeu3[7][5] == 3) &&
                            (TableauJeu3[8][5] == 3)) {//verification si le bateau est coulé
                            TableauJeu3[6][5] = 5;
                            TableauJeu3[7][5] = 5;
                            TableauJeu3[8][5] = 5;
                            Compteur++;
                        }
                        if ((TableauJeu3[2][4] == 3) && (TableauJeu3[2][5] == 3) && (TableauJeu3[2][6] == 3) &&
                            (TableauJeu3[2][7] == 3) && (TableauJeu3[52][8] == 3)) {//verification si le bateau est coulé
                            TableauJeu3[2][4] = 5;
                            TableauJeu3[8][5] = 5;
                            TableauJeu3[8][6] = 5;
                            TableauJeu3[8][7] = 5;
                            TableauJeu3[8][8] = 5;
                            Compteur++;
                        }
                        if ((TableauJeu3[5][2] == 3) && (TableauJeu3[5][3] == 3)) {//verification si le bateau est coulé
                            TableauJeu3[5][2] = 5;
                            TableauJeu3[5][3] = 5;
                            Compteur++;
                        }
                        //affichage du tableau en fonction de la valeur des cases
                        if (TableauJeu3[i][j] == 0) printf("%c ", 255);
                        if (TableauJeu3[i][j] == 1) printf("%c ", 255);
                        if (TableauJeu3[i][j] == 2) printf("\033[34m%c \033[0m", 219);
                        if (TableauJeu3[i][j] == 3) printf("\033[31m%c \033[0m", 219);
                        if (TableauJeu3[i][j] == 5) printf("\033[32m%c \033[0m", 219);
                    }
                    printf("\n");//affichage du retour à la ligne
                }
                if (Compteur < 5) {
                    printf("Ou voulez vous tirer ?\nVertical : (11 pour l'aide, 12 pour quitter)\n");//demande à l'utilisateur où il veut tirer
                    scanf("%d", &Vertical);
                    if (Vertical < 11) {//Si l'utilisateur entre une valeur pour afficher l'aide ou quitter
                        printf("Horizontal :\n");
                        scanf("%d", &Horizontal);
                        compteurJoueur += 1;
                        Scores++;
                        if (TableauJeu3[Vertical - 1][Horizontal - 1] == 1)
                            TableauJeu3[Vertical - 1][Horizontal - 1] = 3;
                        if (TableauJeu3[Vertical - 1][Horizontal - 1] == 0)
                            TableauJeu3[Vertical - 1][Horizontal - 1] = 2;
                        FILE *JouerPartie;//Logage de Jouer partie
                        JouerPartie = fopen("LOG", "a");
                        fprintf(JouerPartie,
                                "\nL'utilisateur : %s a tiré au coordonnée : Vertical : %d, Horizontal : %d",
                                UserName, Vertical, Horizontal);
                        fclose(JouerPartie);
                    }
                    if (Vertical == 11) {//affichage de l'aide en jeu
                        FILE *Afficherlaide;//Logage de affichage de l'aide
                        Afficherlaide = fopen("LOG", "a");
                        fprintf(Afficherlaide, "\nL'utilisateur : %s a affiché l'aide en jeu", UserName);
                        fclose(Afficherlaide);
                        system("cls");
                        printf("La bataille navale oppose deux joueurs qui s'affrontent. \nChacun a une flotte composee de 5 bateaux, qui sont les suivants : \n1 porte-avion (5 cases), 1 croiseur (4 cases), 1 contre-torpilleur (3 cases), \n1 sous-marin (3 cases), 1 torpilleur (2 cases). \nLes bateaux ne doivent pas etre colles entre eux.\n Le but du jeux est d'abbatre tout les bateaux enemis\n");
                        system("Pause");
                    }
                } else { //affichage de l'écran quand on gagne
                    FILE *Gagner;//Logage de Jouer partie
                    Gagner = fopen("LOG", "a");
                    fprintf(Gagner, "\nL'utilisateur : %s a gagné une partie", UserName);
                    fclose(Gagner);
                    FILE *Score;
                    Score = fopen("SCORES", "a");
                    fprintf(Score, "\n%s : %d", UserName, Scores);
                    fclose(Score);
                    system("cls");
                    printf(" _    _ _____ _   _  _   _  ___________ \n"
                           "| |  | |_   _| \\ | || \\ | ||  ___| ___ \\\n"
                           "| |  | | | | |  \\| ||  \\| || |__ | |_/ /\n"
                           "| |/\\| | | | | . ` || . ` ||  __||    / \n"
                           "\\  /\\  /_| |_| |\\  || |\\  || |___| |\\ \\ \n"
                           " \\/  \\/ \\___/\\_| \\_/\\_| \\_/\\____/\\_| \\_|\n"
                           "                                        \n");
                    printf("Vous avez gagne\n1 - Rejouer\n2 - Renvenir au menu principal\n3 - Quitter\n");//demande à l'utilisateur si il veut rejouer, revenir au menu principal ou quitter
                    scanf("%d", &Choix);
                    switch (Choix) {
                        case 1:
                            jouerPartie();//rejouer
                            break;
                        case 2:
                            break;//revient au menu principale
                        case 3:
                            exit(EXIT_SUCCESS);//quitte le programme
                    }
                }
            } while ((Vertical < 12) && (Compteur < 5));//boucle pour jouer tant que l'on a pas gagné ou demandé de quitter
            break;
    }

        FILE *Quitter;//Logage de Jouer partie
        Quitter = fopen("LOG", "a");
        fprintf(Quitter, "\nL'utilisateur : %s a quitter l'ecran de jeu", UserName);
        fclose(Quitter);
}

void menuPrincipal(){
    int Choix = 0;//déclaration des variables
    int Choix2 = 0;
    char ActualUser[48] = {0};
    char UserName[48] = {0};
    char Name[48] = {0};
    char Prenom[48] = {0};
    char MDP[48] = {0};
    char Scores = 0;
    FILE *Actualuser;//Logage du menu principal
    Actualuser = fopen("ActualUser", "r+");
    fscanf(Actualuser, "%s", ActualUser);
    fscanf(Actualuser, "%s", &Name);
    fscanf(Actualuser, "%s", &Prenom);
    fscanf(Actualuser, "%s", &MDP);
    fclose(Actualuser);
    for (int i = 0; i < 48; i++){
        UserName[i] = ActualUser[i];
    }
    system("cls");
    FILE *MenuPrincipal;//Logage de Jouer partie
    MenuPrincipal = fopen("LOG", "a");
    fprintf(MenuPrincipal, "\nL'utilisateur : %s a affiché le menu principal", UserName);
    fclose(MenuPrincipal);
    printf("Bienvenu au menu principal,\nQue voulez vous faire ?\n");//demande à l'utilisateur ce qu'il veut faire
    printf("1 - Jouer une partie\n2 - Afficher l'aide\n3 - Afficher les scores\n4 - Parametres\n5 - Quitter\n");
    scanf ("%d", &Choix);
    switch (Choix){
        case 1: {
            system("cls");//efface l'interface
            jouerPartie();//Jouer
            menuPrincipal();//Menu principal
            break;
        }
        case 2:{
            do {
                system("cls");//efface l'interface
                //affichage de l'aide
                FILE *Afficherlaide;//Logage de afficher l'aide
                Afficherlaide = fopen("LOG", "a");
                fprintf(Afficherlaide, "\nL'utilisateur : %s a affiché l'aide", UserName);
                fclose(Afficherlaide);
                printf("Le jeu de la bataille navale est très simple, \nIl suffit de détruire tout les bateaux en touchant chaque partie du bateaux,\nil y a différents types de bateaux : \n1 porte- avions (5 cases), \nun croiseur (4 cases), \nun sous-marin (3 cases), \nun contre-torpilleur (3 cases) et \nun torpilleur (2 cases), \nles règles sont simple : \ncouler tout les bateaux. \nLe premier nombre à mettre est celui de gauche ensuite celui du haut.");
                printf("\n\nAppuyer sur 1 pour revenir au menu principale\n");
                scanf("%d", &Choix);
                if (Choix == 1) menuPrincipal();//reour au menu principal
            }
            while (Choix != 1);
            break;
        }
        case 3:
            system("cls");
            FILE *scores = NULL;
            scores = fopen("SCORES", "r");
            do {
                Scores = fgetc(scores);
                printf("%c", Scores);
            }while (Scores != EOF);
            fclose(scores);
            printf("\n\n");
            system("Pause");
            menuPrincipal();
            break;


        case 4:
            system("cls");//efface l'interface
            printf("1 - Couleure de l'interface\n2 - Parametres du compte\n");
            scanf("%d", &Choix);
            switch (Choix){
                case 1:
                    system("cls");
                    printf("1 - Rouge\n2 - Vert\n3 - Bleu\n4 - Jaune\n5 - Default\nChoix :\n");
                    scanf("%d", &Choix);
                    switch (Choix){
                        case 1:
                            system("Color 4");
                            break;
                        case 2:
                            system("Color 2");
                            break;
                        case 3 :
                            system("Color 1");
                            break;
                        case 4 :
                            system("Color 6");
                            break;
                            case 5:
                            system("Color F");
                            break;
                    }
                    break;
                case 2:
                    system("cls");
                    printf("Que voulez vous changer ?\n1 - Nom d'utilisateur\n2 - Nom\n3 - Prénom\n4 - Mot de passe\n5 - Confirmer\n");
                    scanf("%d", &Choix2);
                    system("cls");
                    switch (Choix2){
                        case 1:
                            printf("Nom d'utilisateur :\n");
                            scanf("%s", UserName);
                            break;
                        case 2:
                            printf("Nom :\n");
                            scanf("%s", Name);
                            break;
                        case 3:
                            printf("prénom :\n");
                            scanf("%s", Prenom);
                            break;
                        case 4:
                            printf("Mot de passe :\n");
                            scanf("%s", MDP);
                            break;
                        case 5:;
                            FILE *confirmer = NULL;
                            confirmer = fopen(UserName, "w");
                            fclose(confirmer);
                            break;
                        default:

                        break;
                    }

                    break;
                default:
                    break;
            }
            break;
        case 5:
            exit(EXIT_SUCCESS);//quitte programme
        default:
        {
            system("cls");//efface l'interface
            menuPrincipal();//si le nombre n'est corect, réaffiche le menu principale
        }
    }
    menuPrincipal();

}


int main() {
    int Choix = 0;
    system("cls");//efface l'interface
    printf(" _             _           _  _  _                                        _       \n"
           "| |           | |         (_)| || |                                      | |      \n"
           "| |__    __ _ | |_   __ _  _ | || |  ___      _ __    __ _ __   __  __ _ | |  ___ \n"
           "| '_ \\  / _` || __| / _` || || || | / _ \\    | '_ \\  / _` |\\ \\ / / / _` || | / _ \\\n"
           "| |_) || (_| || |_ | (_| || || || ||  __/    | | | || (_| | \\ V / | (_| || ||  __/\n"
           "|_.__/  \\__,_| \\__| \\__,_||_||_||_| \\___|    |_| |_| \\__,_|  \\_/   \\__,_||_| \\___|\n");
    printf("Bonjour,\nBienvenue dans le jeu de la bataille navale.\nChoisissez une option :");
    printf("\n1 - Se connecter\n2 - Creer un compte\n3 - Quitter\n");
    scanf("%d", &Choix);
    switch (Choix){
        case 1:
            printf("Entrez vos identifiants :");//Pour se connecter
            seConnecter();
            menuPrincipal();
            break;
        case 2:
            system("cls");//efface l'interface
            creerUnCompte();//pour créer un comte
            main();
            break;
        case 3:
            exit(EXIT_SUCCESS);

            break;
        default:
            printf("Choix invalide");

            system("Pause");
            system("cls");//efface l'interface
            break;
    }

    return 0;
}
