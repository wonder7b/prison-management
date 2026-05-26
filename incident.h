#ifndef INCIDENT_H
#define INCIDENT_H

typedef struct {
    int numeroIncident;
    int numeroEcrou;
    char date[20];
    char description[100];
    char sanction[100];
} Incident;

void ajouterIncident();
void afficherIncidents();

#endif
