#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>
#include "logMessage.h"
#include "bdd.h"

int json() {
    FILE *file = fopen("/home/yannd/Documents/AUSY/Projet_final_YD/config.json", "r");  //ouvrir le fichier
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier config.json\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(fileSize + 1);
    if (!buffer) {
        fclose(file);
        printf("Erreur lors de l'allocation de mémoire\n");
        return 1;
    }

    fread(buffer, 1, fileSize, file);
    fclose(file);
    buffer[fileSize] = '\0';

    json_error_t error;
    json_t *root = json_loads(buffer, 0, &error);
    free(buffer);

    if (!root) {
        printf("Erreur lors de la lecture du fichier JSON : %s (ligne %d, colonne %d)\n", error.text, error.line, error.column);
        return 1;
    }

    logMessage("recherche dans config.json"); 
    
    // Récupérer les données du fichier JSON
    const char *BDD_nom = json_string_value(json_object_get(root, "BDD_nom"));
    const char *chemin = json_string_value(json_object_get(root,"chemin"));
    json_t *villes = json_object_get(root,"villes");
    if (!json_is_array(villes)) {
        printf("Le champ 'villes' n'est pas un tableau JSON\n");
        json_decref(root);
    return 1;
}

size_t index;
json_t *villeValue;
const char *villeName;

printf("Villes :\n");
json_array_foreach(villes, index, villeValue) {
    if (json_is_string(villeValue)) {
        villeName = json_string_value(villeValue);
        printf("%s\n", villeName);
    }
}
    
    printf("BDD_nom : %s\n", BDD_nom);
    printf("chemin : %s\n", chemin);

    json_decref(root);

    return 0;
}
