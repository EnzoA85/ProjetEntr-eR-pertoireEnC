#ifndef MYLIB_H
#define MYLIB_H

struct tree {
    char path[1024];
    struct tree* child;
    struct tree* sibling;
};

// Déclaration de la fonction pour rechercher une entrée donnée dans l'arborescence
void search(struct tree* root, const char* cible);
struct tree* load(const char*);

#endif