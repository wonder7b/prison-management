#include <stdio.h>
#include "detenu.h"
#include "cellule.h"
#include "incident.h"
#include "statistiques.h"

int main() {

    int choix;

    do {

        printf("\n===== GESTION PRISON =====\n");

        printf("1. Ajouter detenu\n");
        printf("2. Afficher detenus\n");
        printf("3. Affecter detenu a une cellule\n");
        printf("4. Ajouter cellule\n");
        printf("5. Afficher cellules\n");
        printf("6. Ajouter incident\n");
        printf("7. Afficher incidents\n");
        printf("8. Afficher statistiques\n");
        printf("0. Quitter\n");

        printf("Choix : ");
        scanf("%d", &choix);

        switch(choix) {

            case 1:
                ajouterDetenu();
                break;

            case 2:
                afficherDetenus();
                break;

            case 3:
                affecterDetenuCellule();
                break;

            case 4:
                ajouterCellule();
                break;

            case 5:
                afficherCellules();
                break;

            case 6:
                ajouterIncident();
                break;

            case 7:
                afficherIncidents();
                break;

            case 8:
                afficherStatistiques();
                break;

            case 0:
                printf("Fin du programme.\n");
                break;

            default:
                printf("Choix invalide.\n");
        }

    } while(choix != 0);

    return 0;
}
