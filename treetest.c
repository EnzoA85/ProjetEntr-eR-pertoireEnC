#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <libgen.h>
#include "mylib/mylib.h"

int main(int argc, char* argv[]) {
    // Vérification qu'une entrée de répertoire soit bien demandée
    if (argc != 2) {
        fprintf(stderr, "ERREUR ! Veuillez entrer la commande de la façon suivante: %s <entrée_de_répertoire>\n", argv[0]);
        return 1;
    }

    // Charger la racine du répertoire à partir du fichier de configuration
    FILE* config_file = fopen("tree.conf", "r");

    if (config_file == NULL) {
        fprintf(stderr, "Erreur d'ouverture de tree.conf.\n");
        return 1;
    }

    char rootdir[1024];
    while (fgets(rootdir, sizeof(rootdir), config_file) != NULL) {
        if (rootdir[0] != '#' && strncmp(rootdir, "rootdir=", 8) == 0) {
            // Si la ligne n'est pas un commentaire et commence par "rootdir=", utilisez cette valeur.
            break;
        }
    }

    fclose(config_file);

    if (rootdir[0] == '\0') {
        fprintf(stderr, "Aucun chemin rootdir spécifié dans tree.conf.\n");
        return 1;
    }

    // Extrait la valeur de rootdir en supprimant "rootdir=" du début.
    char* rootdir_value = rootdir + 8;

    // Supprimer les caractères de saut de ligne du chemin si nécessaire
    size_t len = strlen(rootdir_value);
    if (len > 0 && rootdir_value[len - 1] == '\n') {
        rootdir_value[len - 1] = '\0';
    }

    // Charge le répertoire racine spécifié dans le fichier de configuration
    struct tree* root = load(rootdir_value);

    if (root == NULL) {
        fprintf(stderr, "Échec de chargement de l'arborescence du répertoire.\n");
        return 1;
    }

    search(root, argv[1]);

    return 0;
}
