#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <jansson.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jansson.h>
#include "bdd.h"
#include "logMessage.h"

int json(void);

void test_json(void) {
    // Créer un fichier config.json de test avec des données spécifiques
    const char* config_data = "{\"BDD_nom\": \"test_db\", \"chemin\": \"/path/to/db\", \"villes\": [\"Paris\", \"New York\"]}";
    FILE* file = fopen("test_config.json", "w");
    if (!file) {
        CU_FAIL("Erreur lors de la création du fichier de test");
        return;
    }
    fwrite(config_data, 1, strlen
    (config_data), file);
    fclose(file);

    // Appeler la fonction à tester
    int result = json();

    // Vérifier les résultats
    CU_ASSERT_EQUAL(result, 0);

    // Nettoyer les fichiers de test
    remove("test_config.json");
}



int main() {
    logMessage("test_json");
    // Initialiser le registre des tests
    CU_initialize_registry();

    // Ajouter la suite de tests
    CU_pSuite suite = CU_add_suite("json_suite", NULL, NULL);
    CU_add_test(suite, "test_json", test_json);

    // Exécuter les tests avec l'interface de base
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

    // Nettoyer le registre des tests
    CU_cleanup_registry();

    return CU_get_error();
}
