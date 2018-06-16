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

bool estNull(Noeud * noeud) {
    if(noeud) {
        return false;
    } else {
        return true;
    }
}

void insertNoeud(Noeud **arbre, int valeurToInsert) {

    Noeud *newNoeud = initNoeud(valeurToInsert); // Initialisation d'un nouveau noeud

    // Initialisation des variables temporaires
    Noeud *noeudTemp;
    Noeud *arbreTemp = *arbre;

    if (!estNull(arbreTemp)) { // Si arbre Temp est différent de null, donc qu'il y a au moins un noeud

        do {
            noeudTemp = arbreTemp;

            if (valeurToInsert > arbreTemp->valeur) { // Si la valeur à insérer est plus grande que celle de la racine
                arbreTemp = arbreTemp->droite; // Alors, on part à la droite de l'arbre
                newNoeud->niveau++;
                if (estNull(arbreTemp)) noeudTemp->droite = newNoeud; // Si le noeud est null, l'élément est placé à cet emplacement à droite
            } else { // Si la valeur est plus petite, pareil à gauche
                arbreTemp = arbreTemp->gauche;
                newNoeud->niveau++;
                if (estNull(arbreTemp)) noeudTemp->gauche = newNoeud;
            }
        } while (!estNull(arbreTemp)); // Parcourir les noeuds, tant qu'il n'y a pas d'emplacement libre

    } else {
        *arbre = newNoeud;
    }
}

int main() {

    /** EXERCICE 1 */

    // Génération de n nombres entiers aléatoires
    srand(time(0));
    const int n = 7;
    int tabNb[n];

    /** for (int i = 0; i < n; i++) {
        tabNb[i] = rand() % 100;
        // printf("Valeurs aléatoires : %d, ", tabNb[i]);
    } */

    tabNb[0] = 10;
    tabNb[1] = 20;
    tabNb[2] = 4;
    tabNb[3] = 8;
    tabNb[4] = 5;
    tabNb[5] = 15;
    tabNb[6] = 3;

    // Premier noeud -> début de l'arbre : racine
    Noeud *arbre = NULL;

    for (int i = 0; i < n; i++) {
        insertNoeud(&arbre, tabNb[i]);
    }

    printf("Première valeur arbre : %d \n", arbre->valeur);
}
