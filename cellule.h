#ifndef CELLULE_H
#define CELLULE_H

typedef struct {
    int numeroCellule;
    char type[20];
    int capacite;
    int occupants;
} Cellule;

void ajouterCellule();
void afficherCellules();

#endif
