#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void logMessage(const char* message) {
    FILE* file = fopen("logfile.txt", "a");
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier de log.\n");
        return;
    }

    time_t now = time(NULL);
    struct tm* timeinfo = localtime(&now);
    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", timeinfo);

    fprintf(file, "[%s] %s\n", timestamp, message);
    fclose(file);
}