#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <sqlite3.h>
#include "logMessage.h"
#include "bdd.h"
#include "json.h"

int main() {
    logMessage("Début du programme");
    bdd();
    json();
    logMessage("Fin du programme");

    return 0;
}