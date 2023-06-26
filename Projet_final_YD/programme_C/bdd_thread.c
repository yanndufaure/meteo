#include <jansson.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "json.h"
#include "logMessage.h"


int callback(void *data, int argc, char **argv, char **azColName) {
    // Fonction de rappel (callback) appelée pour chaque ligne de résultat
    FILE *file = (FILE *)data;

    for (int i = 0; i < argc; i++) {
        fprintf(file, "%s,", argv[i] ? argv[i] : "");
    }
    fprintf(file, "\n");

    return 0;
}

void *bdd_thread(void *arg) {
    // Votre boucle principale
    while (true) {
        // Charger les données du fichier config.json
        json_t *root = json_load_file("../config.json", 0, NULL);
        if (!root) {
            printf("Erreur lors du chargement du fichier config.json\n");
            return NULL;
        }

        // Récupérer les valeurs de "chemin" et "villes" du fichier JSON
        const char *chemin = json_string_value(json_object_get(root, "chemin"));
        json_t *villes_array = json_object_get(root, "villes");
        if (!json_is_array(villes_array)) {
            printf("Le champ 'villes' n'est pas un tableau JSON\n");
            json_decref(root);
            return NULL;
        }

        int numVilles = json_array_size(villes_array);
        char *villes[numVilles];
        for (int i = 0; i < numVilles; i++) {
            json_t *ville_value = json_array_get(villes_array, i);
            if (json_is_string(ville_value)) {
                const char *ville_name = json_string_value(ville_value);
                villes[i] = strdup(ville_name);
            }
        }

        // Ouvrir la base de données SQLite
        sqlite3 *db;
        int rc = sqlite3_open(chemin, &db);
        if (rc != SQLITE_OK) {
            printf("Erreur lors de l'ouverture de la base de données : %s\n", sqlite3_errmsg(db));
            json_decref(root);
            return NULL;
        }

        //chemin vers dossier de sauvegarde pour les fichiers historiques en csv
        const char *fichierHistorique = "../assets/fichiers_historiques";

        for (int i = 0; i < numVilles; i++) {
            const char *ville = villes[i];

            // Exécuter la requête SQL pour récupérer les données de la ville
            char sql[100];
            snprintf(sql, sizeof(sql), "SELECT * FROM meteo WHERE villes='%s'", ville);

            logMessage("Requête SQL envoyée");

            // Créer un fichier de sauvegarde CSV pour la ville
            char *filePath;
            filePath = malloc(strlen(fichierHistorique) + strlen(ville) + 6); // Allouer la mémoire suffisante pour le chemin complet
            snprintf(filePath, strlen(fichierHistorique) + strlen(ville) +6, "%s/%s.csv", fichierHistorique, ville);

            // Vérifier si le fichier existe
            if (access(filePath, F_OK) == -1) { 
                // Le fichier n'existe pas, créer le fichier et écrire les en-têtes des colonnes
                FILE *file = fopen(filePath, "w");
                if (!file) {
                    printf("Erreur lors de l'ouverture du fichier de sauvegarde pour la ville %s\n", ville);
                    continue;
                }
                // Écrire les en-têtes des colonnes dans le fichier CSV
                fprintf(file, "id, ville, pays, temperature, temperature_min, temperature_max, weather, date, date_txt\n");

                // Exécuter la requête SQL et écrire les résultats dans le fichier CSV
                rc = sqlite3_exec(db, sql, callback, file, NULL);
                if (rc != SQLITE_OK) {
                    printf("Erreur lors de l'exécution de la requête pour la ville %s\n", ville);
                    continue;
                }
                // Fermer le fichier de sauvegarde CSV
                fclose(file);
            } else {
                // Ouvrir le fichier de sauvegarde CSV en mode d'ajout
                FILE *file = fopen(filePath, "a");
                if (!file) {
                    printf("Erreur lors de l'ouverture du fichier de sauvegarde pour la ville %s\n", ville);
                    continue;
                }

                // Exécuter la requête SQL et écrire les résultats dans le fichier CSV
                rc = sqlite3_exec(db, sql, callback, file, NULL);
                if (rc != SQLITE_OK) {
                    printf("Erreur lors de l'exécution de la requête pour la ville %s\n", ville);
                    continue;
                }

                // Fermer le fichier de sauvegarde CSV et 
                fclose(file);
            }

            //libérer la mémoire allouée pour filePath
            free(filePath);
        }

        // Fermer la base de données SQLite
        sqlite3_close(db);

        // Pause de 20 minutes avant la prochaine exécution
        sleep(1200); // 1200 secondes = 20 minutes
    }

    return NULL;
}
