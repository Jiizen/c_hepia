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

/*
 * Affichage de la valeur d’un noeud après les valeurs figurant dans son sous-arbre gauche et avant les
 * valeurs figurant dans son sous-arbre droit
 */
void parcoursInfixe(Noeud *arbre) {
    if(!estNull(arbre)) {
        parcoursInfixe(arbre->gauche); // Parcours des fils de gauche
        printf("%d ", arbre->valeur); // On affiche la valeur du noeud courant
        parcoursInfixe(arbre->droite); // Parcours des fils de droit
    }
}

int main() {

    /** EXERCICE 1 */

    // Génération de n nombres entiers aléatoires
    srand(time(0));
    const int n = 7;
    int tabNb[n];

    printf("EXERCICE 1 \n");
    printf("Valeurs aléatoires : ");
    for (int i = 0; i < n; i++) {
        tabNb[i] = rand() % 100;
        printf("%d ", tabNb[i]);
    }

/*
    tabNb[0] = 10;
    tabNb[1] = 20;
    tabNb[2] = 4;
    tabNb[3] = 8;
    tabNb[4] = 5;
    tabNb[5] = 15;
    tabNb[6] = 3;
*/

    // Premier noeud -> début de l'arbre : racine
    Noeud *arbre = NULL;

    for (int i = 0; i < n; i++) {
        insertNoeud(&arbre, tabNb[i]);
    }

    // Parcours symétrique de l'arbre
    printf("\nParcours infixé de notre arbre : ");
    parcoursInfixe(arbre);
}
