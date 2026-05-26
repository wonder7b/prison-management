#include <stdio.h>
#include "incident.h"

void ajouterIncident() {
    FILE *f = fopen("incidents.txt", "a");
    if (!f) {
        printf("Erreur : impossible d'ouvrir incidents.txt\n");
        return;
    }

    Incident i;

    printf("Numero incident : ");
    scanf("%d", &i.numeroIncident);

    printf("Numero ecrou : ");
    scanf("%d", &i.numeroEcrou);

    printf("Date : ");
    scanf("%19s", i.date);

    printf("Description : ");
    scanf("%99s", i.description);

    printf("Sanction : ");
    scanf("%99s", i.sanction);

    fprintf(f, "%d %d %s %s %s\n",
            i.numeroIncident,
            i.numeroEcrou,
            i.date,
            i.description,
            i.sanction);

    fclose(f);

    printf("Incident ajoute.\n");
}

void afficherIncidents() {
    FILE *f = fopen("incidents.txt", "r");
    if (!f) {
        printf("Aucun incident enregistre.\n");
        return;
    }

    Incident i;

    while (fscanf(f, "%d %d %19s %99s %99s",
          &i.numeroIncident,
          &i.numeroEcrou,
          i.date,
          i.description,
          i.sanction) != EOF) {

        printf("\nIncident %d | Detenu %d | %s",
               i.numeroIncident,
               i.numeroEcrou,
               i.description);
    }

    fclose(f);
}
