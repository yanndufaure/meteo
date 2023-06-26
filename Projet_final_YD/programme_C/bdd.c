#include <jansson.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "bdd_thread.h"
#include "json.h"
#include "logMessage.h"


int bdd() {
    pthread_t thread;
    // Créer le thread et exécuter la fonction bdd_thread
    int rc = pthread_create(&thread, NULL, bdd_thread, NULL);
    if (rc != 0) {
        printf("Erreur lors de la création du thread\n");
        return 1;
    }

    // Attendre la fin du thread (ceci est facultatif)
    pthread_join(thread, NULL);

    return 0;
}
