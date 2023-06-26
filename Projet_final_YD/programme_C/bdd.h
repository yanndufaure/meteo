#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int callback(void *data, int argc, char **argv, char **azColName);
int bdd();