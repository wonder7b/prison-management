#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAILLE 256

// Définition de la structure Incident
typedef struct {
    int numero_incident;
    int numero_ecrou;
    char date[15]; // Format attendu: JJ/MM/AAAA
    char description[MAX_TAILLE];
    char sanction[MAX_TAILLE];
}Incident;void enregistrer_incident() {
    Incident inc;
    FILE *fichier = fopen("incidents.txt","a");

    if (fichier == NULL) {
        printf("Erreur : Impossible d'ouvrir le fichier incidents.txt\n");
        return;
    }

    printf("--- Enregistrement d'un nouvel incident ---\n");

    printf("Numéro d'incident : ");
    scanf("%d", &inc.numero_incident);

    printf("Numéro d'écrou du détenu : ");
    scanf("%d", &inc.numero_ecrou);

    printf("Date (JJ/MM/AAAA) : ");
    scanf("%14s", inc.date);

    // Vider le buffer avant d'utiliser fgets
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Description de l'incident : ");
    fgets(inc.description, MAX_TAILLE, stdin);
    inc.description[strcspn(inc.description, "\n")] = 0; // Retirer le saut de ligne

    printf("Sanction éventuelle (laisser vide si aucune) : ");
    fgets(inc.sanction, MAX_TAILLE, stdin);
    inc.sanction[strcspn(inc.sanction, "\n")] = 0; // Retirer le saut de ligne

    // Si la sanction est vide, on met une valeur par défaut pour le fichier
    if (strlen(inc.sanction) == 0) {
        strcpy(inc.sanction, "Aucune");
    }

    // Sauvegarde dans le fichier avec un séparateur ';'
    fprintf(fichier, "%d;%d;%s;%s;%s\n",
            inc.numero_incident,
            inc.numero_ecrou,
            inc.date,
            inc.description,
            inc.sanction);

    fclose(fichier);
    printf("\nSuccès : L'incident a été enregistré dans incidents.txt.\n");
}
void afficher_incidents_detenu(int num_ecrou_recherche) {
    FILE *fichier = fopen("incidents.txt", "r");

    if (fichier == NULL) {
        printf("Aucun incident enregistré ou fichier introuvable.\n");
        return;
    }

    char ligne[1024];
    int trouve = 0;

    printf("\n--- Historique des incidents pour le détenu N°%d ---\n", num_ecrou_recherche);

    // Lecture du fichier ligne par ligne
    while (fgets(ligne, sizeof(ligne), fichier) != NULL) {
        Incident inc;

        // Découpage de la ligne avec strtok
        char *token = strtok(ligne, ";");
        if (token) inc.numero_incident = atoi(token);

        token = strtok(NULL, ";");
        if (token) inc.numero_ecrou = atoi(token);

        // Si c'recherche le bon numéro d'écrou, on extrait le reste et on affiche
        if (inc.numero_ecrou == num_ecrou_recherche) {
            token = strtok(NULL, ";");
            if (token) strcpy(inc.date, token);

            token = strtok(NULL, ";");
            if (token) strcpy(inc.description, token);

            token = strtok(NULL, "\n"); // Récupérer la fin de la ligne pour la sanction
            if (token) strcpy(inc.sanction, token);

            printf("\n> Incident N°%d (%s)\n", inc.numero_incident, inc.date);
            printf("  Description : %s\n", inc.description);
            printf("  Sanction    : %s\n", inc.sanction);
            trouve = 1;
        }
    }

    if (!trouve) {
        printf("\nAucun incident répertorié pour ce détenu.\n");
    }

    fclose(fichier);
}
