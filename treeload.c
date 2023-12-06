#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include "mylib/mylib.h"

void handleSIGHUP(int signum) {
    // Lire le nom du fichier depuis datafile
    FILE *datafile = fopen("tree.conf", "r");
    char filename[1024];
    fgets(filename, sizeof(filename), datafile);
    fclose(datafile);

    // Charger l'arborescence
    struct tree *root = load("/");

    if (root == NULL) {
        fprintf(stderr, "Échec de chargement de l'arborescence du répertoire.\n");
        exit(1);
    }

    // Rechercher le fichier dans l'arborescence
    search(root, filename);

    // Libérer la mémoire allouée pour l'arborescence
    // (ajoutez une fonction "libérer" dans mylib.c si elle n'existe pas)
    // libérer(root);
}

int main() {
    // Sauvegarder le PID dans le fichier pidfile
    FILE *pidfile = fopen("tree.conf", "w");
    fprintf(pidfile, "%d\n", getpid());
    fclose(pidfile);

    // Gérer le signal SIGHUP
    signal(SIGHUP, handleSIGHUP);

    // Restez indéfiniment en attente de signaux
    while (1) {
        sleep(1);
    }

    return 0;
}
