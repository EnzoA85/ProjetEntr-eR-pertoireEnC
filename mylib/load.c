#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <libgen.h>

#define MAX_PATH_LEN 1024

// On créée une structure tree afin de créer un noeud de l'arborescence
struct tree {
    char path[MAX_PATH_LEN];
    struct tree* child; // Pointeur vers le premier enfant
    struct tree* sibling; // Pointeur vers le premier frère
};

struct tree* load(const char* path) {
    struct tree* root = NULL;
    struct tree* current = NULL;
    DIR* dir;
    struct dirent* entry;

    // On ouvre le répertoire à partir du chemon donné, ici "/"
    dir = opendir(path);

    // On vérifie que l'ouverture n'a pas échoué
    if (dir == NULL) {
        perror("opendir");
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // On créer un nouveau noeud avec un stockage dynamique en utilisant un malloc
        struct tree* newNode = (struct tree*)malloc(sizeof(struct tree));
        snprintf(newNode->path, sizeof(newNode->path), "%s/%s", path, entry->d_name);

        // On initialise deux nouveau champ, enfant et frère pour les fichiers
        newNode->child = NULL;
        newNode->sibling = NULL;

        // On vérifie si c'est le premier élément de l'arbre
        if (current == NULL) {
            // on initie le répertoire "par default" et l'actuel par celui qu'on vient de trouver 
            root = newNode;
            current = newNode;
        } else {
            // Sinon le fait pour le fichier frère
            current->sibling = newNode;
            current = newNode;
        }

        if (entry->d_type == DT_DIR) {
            // Récursivement charger les sous-répertoires
            newNode->child = load(newNode->path);
        }
    }

    closedir(dir);
    return root;
}