#ifndef DETENU_H
#define DETENU_H

#define MAX_DETENUS 500
#define MAX_CELLULES 200

typedef struct {
    int numeroEcrou;
    char nom[50];
    char prenom[50];
    char dateNaissance[20];
    char sexe[10];
    char dateEntree[20];
    char motif[100];
    int numeroCellule;
} Detenu;

void ajouterDetenu();
void afficherDetenus();
void affecterDetenuCellule();

#endif
