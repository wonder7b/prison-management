#include <stdio.h>
#include "detenu.h"
#include "cellule.h"
#include "incident.h"

void afficherStatistiques() {
    FILE *f;
    Detenu d;
    Cellule c;
    Incident i;
    int nbDetenus = 0, nbCellules = 0, nbIncidents = 0;
    int totalOccupants = 0, totalCapacite = 0;

    f = fopen("detenus.txt", "r");
    if (f) {
        while (fscanf(f, "%d %49s %49s %19s %9s %19s %99s %d",
                      &d.numeroEcrou, d.nom, d.prenom,
                      d.dateNaissance, d.sexe, d.dateEntree,
                      d.motif, &d.numeroCellule) != EOF) {
            nbDetenus++;
        }
        fclose(f);
    }

    f = fopen("cellules.txt", "r");
    if (f) {
        while (fscanf(f, "%d %19s %d %d",
                      &c.numeroCellule, c.type,
                      &c.capacite, &c.occupants) != EOF) {
            nbCellules++;
            totalOccupants += c.occupants;
            totalCapacite += c.capacite;
        }
        fclose(f);
    }

    f = fopen("incidents.txt", "r");
    if (f) {
        while (fscanf(f, "%d %d %19s %99s %99s",
                      &i.numeroIncident, &i.numeroEcrou,
                      i.date, i.description, i.sanction) != EOF) {
            nbIncidents++;
        }
        fclose(f);
    }

    printf("\n===== STATISTIQUES =====\n");
    printf("Nombre de detenus   : %d\n", nbDetenus);
    printf("Nombre de cellules  : %d\n", nbCellules);
    printf("Nombre d'incidents  : %d\n", nbIncidents);
    printf("Occupation totale   : %d/%d\n", totalOccupants, totalCapacite);

    if (totalCapacite > 0) {
        printf("Taux d'occupation   : %.1f %%\n",
               100.0 * totalOccupants / totalCapacite);
    } else {
        printf("Taux d'occupation   : N/A (aucune cellule)\n");
    }

    if (nbDetenus > 0) {
        printf("Incidents/detenu    : %.2f\n",
               (float)nbIncidents / nbDetenus);
    }

    printf("========================\n");
}
