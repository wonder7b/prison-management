#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char numero_ecrou[20];
    char nom[50];
    char post_nom[50];
    char prenom[50];
    char date_naissance[11];
    char sexe;
    char date_entree[11];
    char motif_incarceration[100];
    int duree_peine;
    char cellule_attribuee[20];
} Detenu;

void ajouterDetenu();
void afficherDetenus();
void reinitialiserDetenus();

int main() {
    int choix;
    do {
        printf("\n--- MENU GESTION DES DETENUS ---\n");
        printf("1. Ajouter un detenu\n");
        printf("2. Afficher tous les detenus\n");
        printf("3. Reinitialiser la liste (supprimer tout)\n");
        printf("0. Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);
        getchar();

        switch(choix) {
            case 1: ajouterDetenu(); break;
            case 2: afficherDetenus(); break;
            case 3: reinitialiserDetenus(); break;
            case 0: printf("Fin du programme.\n"); break;
            default: printf("Choix invalide.\n");
        }
    } while(choix != 0);
    return 0;
}

void ajouterDetenu() {
    Detenu d;
    FILE *fichier = fopen("detenus.txt", "a");
    if (fichier == NULL) return;

    printf("\n--- AJOUT D'UN NOUVEAU DETENU ---\n");
    printf("Numero d'ecrou : "); scanf("%s", d.numero_ecrou);
    printf("Nom : "); scanf("%s", d.nom);
    printf("Post-nom : "); scanf("%s", d.post_nom);
    printf("Prenom : "); scanf("%s", d.prenom);
    printf("Date de naissance (JJ/MM/AAAA) : "); scanf("%s", d.date_naissance);
    printf("Sexe (M/F) : "); scanf(" %c", &d.sexe);
    printf("Date d'entree (JJ/MM/AAAA) : "); scanf("%s", d.date_entree);

    getchar();
    printf("Motif d'incarceration : ");
    fgets(d.motif_incarceration, 100, stdin);
    d.motif_incarceration[strcspn(d.motif_incarceration, "\n")] = 0;

    for(int i = 0; d.motif_incarceration[i] != '\0'; i++) {
        if(d.motif_incarceration[i] == ' ') d.motif_incarceration[i] = '_';
    }

    printf("Duree de la peine (en mois) : "); scanf("%d", &d.duree_peine);
    printf("Cellule attribuee : "); scanf("%s", d.cellule_attribuee);

    fprintf(fichier, "%s %s %s %s %s %c %s %s %d %s\n",
            d.numero_ecrou, d.nom, d.post_nom, d.prenom, d.date_naissance,
            d.sexe, d.date_entree, d.motif_incarceration,
            d.duree_peine, d.cellule_attribuee);

    fclose(fichier);
    printf("\n=> Detenu ajoute avec succes !\n");
}

void afficherDetenus() {
    Detenu d;
    FILE *fichier = fopen("detenus.txt", "r");
    if (fichier == NULL) {
        printf("Aucun detenu enregistre.\n");
        return;
    }

    printf("\n--- LISTE DES DETENUS ---\n");
    while (fscanf(fichier, "%s %s %s %s %s %c %s %s %d %s",
           d.numero_ecrou, d.nom, d.post_nom, d.prenom, d.date_naissance,
           &d.sexe, d.date_entree, d.motif_incarceration,
           &d.duree_peine, d.cellule_attribuee) != EOF) {

        for(int i = 0; d.motif_incarceration[i] != '\0'; i++) {
            if(d.motif_incarceration[i] == '_') d.motif_incarceration[i] = ' ';
        }

        printf("Ecrou: %s | Nom: %s %s %s | Cellule: %s | Peine: %d mois | Motif: %s\n",
               d.numero_ecrou, d.nom, d.post_nom, d.prenom, d.cellule_attribuee, d.duree_peine, d.motif_incarceration);
    }
    fclose(fichier);
}

void reinitialiserDetenus() {
    FILE *fichier = fopen("detenus.txt", "w");
    if (fichier != NULL) {
        fclose(fichier);
        printf("\n=> Fichier reinitialise.\n");
    }
}
