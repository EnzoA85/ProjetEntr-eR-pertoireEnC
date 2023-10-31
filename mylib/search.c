#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <libgen.h> 

#define MAX_PATH_LEN 1024
struct tree {
    char path[MAX_PATH_LEN];
    struct tree* child;
    struct tree* sibling;
};

// Fonction pour rechercher une entrée donnée dans l'arborescence
void search(struct tree* root, const char* cible) {

    // Vérification qu'il y a bien un arbre à explorer
    if (root == NULL) {
        return;
    }

    // On stock dans base le nom du fichier trouvé
    char* base = basename(root->path);

    // On verifie qu'on a bien trouvé un fichier et que celui-ci est identique à l'entrée saisie et si c'est le cas on affiche son chemin
    if (base != NULL && strcmp(base, cible) == 0) {
        printf("%s\n", root->path);
    }

    // Rechercher de manière récursif dans les enfants et les frères
    search(root->child, cible);
    search(root->sibling, cible);
}