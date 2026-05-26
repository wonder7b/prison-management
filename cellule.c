#include <stdio.h>
#include "cellule.h"

void ajouterCellule() {
    FILE *f = fopen("cellules.txt", "a");
    if (!f) {
        printf("Erreur : impossible d'ouvrir cellules.txt\n");
        return;
    }

    Cellule c;

    printf("Numero cellule : ");
    scanf("%d", &c.numeroCellule);

    printf("Type : ");
    scanf("%19s", c.type);

    printf("Capacite : ");
    scanf("%d", &c.capacite);

    c.occupants = 0;

    fprintf(f, "%d %s %d %d\n",
            c.numeroCellule,
            c.type,
            c.capacite,
            c.occupants);

    fclose(f);

    printf("Cellule ajoutee.\n");
}

void afficherCellules() {
    FILE *f = fopen("cellules.txt", "r");
    if (!f) {
        printf("Aucune cellule enregistree.\n");
        return;
    }

    Cellule c;

    while (fscanf(f, "%d %19s %d %d",
          &c.numeroCellule,
          c.type,
          &c.capacite,
          &c.occupants) != EOF) {

        printf("\nCellule %d | %s | %d/%d",
               c.numeroCellule,
               c.type,
               c.occupants,
               c.capacite);
    }

    fclose(f);
}
