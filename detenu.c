#include <stdio.h>
#include <stdlib.h>
#include "detenu.h"
#include "cellule.h"

void ajouterDetenu() {
    FILE *f = fopen("detenus.txt", "a");
    if (!f) {
        printf("Erreur : impossible d'ouvrir detenus.txt\n");
        return;
    }

    Detenu d;

    printf("Numero d'ecrou : ");
    scanf("%d", &d.numeroEcrou);

    printf("Nom : ");
    scanf("%49s", d.nom);

    printf("Prenom : ");
    scanf("%49s", d.prenom);

    printf("Date naissance : ");
    scanf("%19s", d.dateNaissance);

    printf("Sexe : ");
    scanf("%9s", d.sexe);

    printf("Date entree : ");
    scanf("%19s", d.dateEntree);

    printf("Motif : ");
    scanf("%99s", d.motif);

    d.numeroCellule = -1;

    fprintf(f, "%d %s %s %s %s %s %s %d\n",
            d.numeroEcrou,
            d.nom,
            d.prenom,
            d.dateNaissance,
            d.sexe,
            d.dateEntree,
            d.motif,
            d.numeroCellule);

    fclose(f);

    printf("Detenu ajoute avec succes.\n");
}

void afficherDetenus() {
    FILE *f = fopen("detenus.txt", "r");
    if (!f) {
        printf("Aucun detenu enregistre.\n");
        return;
    }

    Detenu d;

    while (fscanf(f, "%d %49s %49s %19s %9s %19s %99s %d",
          &d.numeroEcrou,
          d.nom,
          d.prenom,
          d.dateNaissance,
          d.sexe,
          d.dateEntree,
          d.motif,
          &d.numeroCellule) != EOF) {

        printf("\n%d - %s %s - Cellule : %d",
               d.numeroEcrou,
               d.nom,
               d.prenom,
               d.numeroCellule);
    }

    fclose(f);
}

void affecterDetenuCellule() {
    FILE *f;
    Detenu detenus[MAX_DETENUS];
    Cellule cellules[MAX_CELLULES];
    int nbDetenus = 0, nbCellules = 0;
    int ecrou, celluleCible;
    int trouveDetenu = 0, trouveCellule = 0;
    int idxDetenu = -1, idxCellule = -1;

    printf("Numero d'ecrou du detenu : ");
    scanf("%d", &ecrou);
    printf("Numero de la cellule : ");
    scanf("%d", &celluleCible);

    f = fopen("detenus.txt", "r");
    if (f) {
        while (fscanf(f, "%d %49s %49s %19s %9s %19s %99s %d",
                      &detenus[nbDetenus].numeroEcrou,
                      detenus[nbDetenus].nom,
                      detenus[nbDetenus].prenom,
                      detenus[nbDetenus].dateNaissance,
                      detenus[nbDetenus].sexe,
                      detenus[nbDetenus].dateEntree,
                      detenus[nbDetenus].motif,
                      &detenus[nbDetenus].numeroCellule) != EOF) {
            if (detenus[nbDetenus].numeroEcrou == ecrou) {
                trouveDetenu = 1;
                idxDetenu = nbDetenus;
            }
            nbDetenus++;
        }
        fclose(f);
    }

    f = fopen("cellules.txt", "r");
    if (f) {
        while (fscanf(f, "%d %19s %d %d",
                      &cellules[nbCellules].numeroCellule,
                      cellules[nbCellules].type,
                      &cellules[nbCellules].capacite,
                      &cellules[nbCellules].occupants) != EOF) {
            if (cellules[nbCellules].numeroCellule == celluleCible) {
                trouveCellule = 1;
                idxCellule = nbCellules;
            }
            nbCellules++;
        }
        fclose(f);
    }

    if (!trouveDetenu) {
        printf("Erreur : detenu %d introuvable.\n", ecrou);
        return;
    }
    if (!trouveCellule) {
        printf("Erreur : cellule %d introuvable.\n", celluleCible);
        return;
    }
    if (cellules[idxCellule].occupants >= cellules[idxCellule].capacite) {
        printf("Erreur : la cellule %d est pleine (%d/%d).\n",
               celluleCible,
               cellules[idxCellule].occupants,
               cellules[idxCellule].capacite);
        return;
    }

    detenus[idxDetenu].numeroCellule = celluleCible;
    cellules[idxCellule].occupants++;

    f = fopen("detenus.txt", "w");
    if (!f) {
        printf("Erreur : impossible d'ecrire detenus.txt\n");
        return;
    }
    for (int k = 0; k < nbDetenus; k++) {
        fprintf(f, "%d %s %s %s %s %s %s %d\n",
                detenus[k].numeroEcrou,
                detenus[k].nom,
                detenus[k].prenom,
                detenus[k].dateNaissance,
                detenus[k].sexe,
                detenus[k].dateEntree,
                detenus[k].motif,
                detenus[k].numeroCellule);
    }
    fclose(f);

    f = fopen("cellules.txt", "w");
    if (!f) {
        printf("Erreur : impossible d'ecrire cellules.txt\n");
        return;
    }
    for (int k = 0; k < nbCellules; k++) {
        fprintf(f, "%d %s %d %d\n",
                cellules[k].numeroCellule,
                cellules[k].type,
                cellules[k].capacite,
                cellules[k].occupants);
    }
    fclose(f);

    printf("Detenu %d affecte a la cellule %d.\n", ecrou, celluleCible);
}
