#include <stdio.h>
#include <stdlib.h>
#include <tcl.h>
#include <time.h>
#include "pile.h"

int main() {

    CONST int nbElementsTab = 5;
    int tabNb[nbElementsTab];
    srand(time(0));

    // Générer un tableau de 5 nombres aléatoires
    for (int i = 0; i < nbElementsTab; i++) {
        tabNb[i] = rand() % 100;
    }

    Pile *pileDeGauche = initPile();
    Pile *pileDeDroite = initPile();

    // Quand les 2 piles sont vides, on met par défaut le premier nombre dans la pile de gauche
    empiler(pileDeGauche, tabNb[0]);

    for (int i = 1; i < nbElementsTab; i++) {

        // Si on a au moins un élément dans la pile de gauche et rien dans celle de droite
        if (pileDeGauche->premier != NULL && pileDeDroite->premier == NULL) {

            if (tabNb[i] > sommet(pileDeGauche)->valeur) { // Si le nb de la pile de gauche est inférieur au suivant
                int nbDepile;
                nbDepile = depiler(pileDeGauche); // On enlève le nb plus petit de pile de gauche
                empiler(pileDeDroite, nbDepile); // On l'empile à droite
                empiler(pileDeGauche, tabNb[i]); // On empile le nb plus grand à gauche, du coup
            } else {
                empiler(pileDeDroite, tabNb[i]); // Autrement, on empile simplement le nb à droite
            }

        // Si on a au moins un élément dans la pile de droite et rien dans celle de gauche
        } else if (pileDeGauche->premier == NULL && pileDeDroite->premier != NULL) { // Si pile de gauche vide et

            if (tabNb[i] < sommet(pileDeDroite)->valeur) { // Si la valeur est plus petite que dans la pile de droite
                int nbDepile;
                nbDepile = depiler(pileDeDroite); // On dépile la valeur de la pile de droite
                empiler(pileDeGauche, nbDepile); // On
                empiler(pileDeDroite, tabNb[i]); // On empile le nb plus petit à droite, du coup
            } else {
                empiler(pileDeGauche, tabNb[i]); // Autrement, on empile simplement le nb à gauche
            }

        } else {

            // Si la valeur du nombre est plus petite que celle de la pile de gauche et plus grande que celle de la pile de droite
            if ((tabNb[i] < sommet(pileDeGauche)->valeur) && (tabNb[i] > sommet(pileDeDroite)->valeur)) {
                empiler(pileDeGauche, tabNb[i]); // On empile le nombre à gauche
            // Si la valeur du nombre est plus grande que celle de la pile de gauche et plus petite que celle de la pile de droite
            } else if ((tabNb[i] > sommet(pileDeGauche)->valeur) && (tabNb[i] < sommet(pileDeDroite)->valeur)) {
                empiler(pileDeDroite, tabNb[i]); // On empile à droite

            // Autrement, si la valeur est à la fois plus grande que celle de la pile de gauche et celle de la pile de droite
            } else if ((tabNb[i] > sommet(pileDeGauche)->valeur) && (tabNb[i] > sommet(pileDeDroite)->valeur)) {

                // Tant que la pile de gauche n'est pas nulle et que la valeur de la pile reste plus petite que la nôtre
                while((sommet(pileDeGauche) != NULL) && (sommet(pileDeGauche)->valeur < tabNb[i])) {
                    int nbDepile = depiler(pileDeGauche); // On dépile la pile de gauche
                    empiler(pileDeDroite, nbDepile); // et on empile le tout à droite
                }
                empiler(pileDeGauche, tabNb[i]); // Enfin, on empile notre valeur sur la pile de gauche

            } else {

                // Dans le dernier cas (valeur plus petite que tout), tant que la pile de droite n'est pas vide et a une valeur plus grande que celle de notre nb
                while(sommet(pileDeDroite) != NULL && sommet(pileDeDroite)->valeur > tabNb[i]) {
                    int nbDepile = depiler(pileDeDroite); // On dépile à droite
                    empiler(pileDeGauche, nbDepile); // et on empile le tout à gauche
                }
                empiler(pileDeDroite, tabNb[i]); // On empile notre nombre sur la pile de droite pour terminer
            }
        }
    }

    // Quand traitement fini, on déplace tout ce qui reste dans la pile de droite dans la pile de gauche
    while (profondeur(pileDeDroite) > 0) {
        int nbDepile = depiler(pileDeDroite);
        empiler(pileDeGauche, nbDepile);
    }

    // Afficher tableau final trié : du plus petit au plus grand
    while (profondeur(pileDeGauche) > 0) {
        int nbDepile = depiler(pileDeGauche);
        printf("%d \n", nbDepile);
    }
}