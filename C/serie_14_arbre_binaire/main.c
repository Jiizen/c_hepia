/**
 * Created by Evlyn
 * TP : Exercice 14 - Arbres binaires
 */

#include <stdio.h>
#include <stdlib.h>
#include <tcl.h>
#include <time.h>
#include <stdbool.h>

/* STRUCTURES */

// Node
typedef struct Noeud Noeud;
struct Noeud {
    int valeur;
    int niveau;
    Noeud *gauche;
    Noeud *droite;
};

Noeud *initNoeud(int valeur) {
    Noeud *newNoeud = malloc(sizeof(Noeud));
    newNoeud->valeur = valeur;
    newNoeud->niveau = 0;
    newNoeud->gauche = NULL;
    newNoeud->droite = NULL;
    return newNoeud;
}

/* FONCTIONS */

bool estNull(Noeud *noeud) {
    if (noeud) {
        return false;
    } else {
        return true;
    }
}

void insertNoeud(Noeud **arbre, int valeur) {

    Noeud *noeudTemp = initNoeud(valeur);
    Noeud *courant;
    Noeud *parent;

    if (estNull(*arbre)) { // Si l'arbre est vide, on insère de suite le noeud
        *arbre = noeudTemp;
    } else {
        courant = *arbre; // l'arbre n'est pas vide, on lui crée une variable temporaire

        while (1) { // Boucle infinie jusqu'à un return
            parent = courant; // Parent = racine

            if (valeur < parent->valeur) { // Si valeur à insérer est + petite que la valeur du parent, on va à gauche
                courant = courant->gauche; // Redéfinition du noeud courant à celui de gauche
                noeudTemp->niveau++;

                if (courant == NULL) { // Si l'emplacement est libre, on met la valeur courante du noeud à cet endroit
                    parent->gauche = noeudTemp;
                    return;
                }
            } // Sinon, on part à droite
            else {
                courant = courant->droite;
                noeudTemp->niveau++;

                if (courant == NULL) { // Insertion à droite quand emplacement libre
                    parent->droite = noeudTemp;
                    return;
                }
            }
        }
    }
}

void parcoursInfixe(Noeud *arbre) {
    if(!estNull(arbre)) {
        parcoursInfixe(arbre->gauche); // On remonte toute la branche gauche
        printf("%d ", arbre->valeur); // On affiche la valeur
        parcoursInfixe(arbre->droite);
    }
}

int main() {

    /** EXERCICE 1 */

    // Génération de n nombres entiers aléatoires
    srand(time(0));
    const int n = 7;
    int tabNb[n];

    printf("Valeurs aléatoires : ");
    for (int i = 0; i < n; i++) {
        tabNb[i] = rand() % 100;
        printf("%d ", tabNb[i]);
    }

    // Premier noeud -> début de l'arbre : racine
    Noeud *arbre = NULL;

    for (int i = 0; i < n; i++) {
        insertNoeud(&arbre, tabNb[i]);
    }

    // Parcours symétrique de l'arbre
    printf("\nParcours infixé de notre arbre : ");
    parcoursInfixe(arbre);
}
