#include <stdio.h>
#include <stdlib.h>
#include <tcl.h>
#include "pile.h"

int main() {

    CONST int nbElementsTab = 5;
    int tabNb[nbElementsTab];

    // Générer un tableau de 5 nombres aléatoires
    for(int i = 0 ; i < nbElementsTab ; i++) {
        tabNb[i] = rand() % 100;
    }

    Pile *pileDeGauche = initPile();
    Pile *pileDeDroite = initPile();

    empiler(pileDeGauche, tabNb[0]);
    pileDeGauche->profondeur = 1;
    for(int i = 1 ; i < nbElementsTab ; i++) {

        // Condition juste le premier tour
        if(pileDeGauche->profondeur == 0 && pileDeDroite->profondeur == 0) {
            if(tabNb[i] > sommet(pileDeGauche)->valeur) { // Si le nb de la pile de gauche est inférieur au suivant
                Nombre * nbDepile;
                nbDepile->valeur = depiler(pileDeGauche); // On enlève le nb plus petit de pile de gauche
                empiler(pileDeDroite, nbDepile->valeur); // On l'empile à droite
                empiler(pileDeGauche, tabNb[i]); // On empile le nombre plus grand à gauche
            } else {
                empiler(pileDeDroite, tabNb[i]);
            }
        }






    }
}