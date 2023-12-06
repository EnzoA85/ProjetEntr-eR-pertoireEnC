#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "mylib/mylib.h"

void sendSignalToTreeload(const char *filename) {
    // Lire le PID du fichier pidfile
    FILE *pidfile = fopen("tree.conf", "r");
    char pidBuffer[1024];
    fgets(pidBuffer, sizeof(pidBuffer), pidfile);
    fclose(pidfile);

    // Envoyer un signal SIGHUP au treeload
    int pid = atoi(pidBuffer);
    if (pid > 0) {
        kill(pid, SIGHUP);
        printf("Signal SIGHUP envoyé à treeload.\n");
    } else {
        fprintf(stderr, "Erreur : PID invalide.\n");
    }

    // Écrire le nom du fichier dans le fichier datafile
    FILE *datafile = fopen("tree.conf", "w");
    fprintf(datafile, "%s", filename);
    fclose(datafile);
}

int main(int argc, char *argv[]) {
    // Vérification qu'un nom de fichier soit bien fourni en argument
    if (argc != 2) {
        fprintf(stderr, "ERREUR ! Veuillez fournir le nom du fichier en argument.\n");
        return 1;
    }

    // Écrire le nom du fichier dans le fichier datafile et envoyer le signal SIGHUP
    sendSignalToTreeload(argv[1]);

    return 0;
}
