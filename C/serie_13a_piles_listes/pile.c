/**
 * Created by Evlyn on 15.05.18.
 * TP : Exercice 13A : Piles et listes
 * Fonctions concernant les piles
 */

#include <stdio.h>
#include <stdlib.h>
#include <tcl.h>
#include <time.h>
#include "pile.h"

Pile *initPile() {
    Pile *pile = malloc(sizeof(Pile));
    pile->profondeur = 0;
    pile->premier = NULL;
    return pile;
}

int profondeur(Pile *pile) {
    return pile->profondeur;
}

bool estVide(Pile *pile) {
    if (pile->profondeur == 0) {
        return true;
    } else {
        return false;
    }
}

Nombre * sommet(Pile *pile) {
    return pile->premier;
}

void empiler(Pile *pile, int nb) {
    Nombre *newNombre = malloc(sizeof(Nombre));
    newNombre->valeur = nb;
    if(sommet(pile) != NULL) {
        newNombre->suivant = sommet(pile);
    }
    pile->premier = newNombre;
    pile->profondeur += 1;
}

int depiler(Pile *pile) {
    int valueDepilee;
    Nombre *nbDepile = sommet(pile);

    if (!estVide(pile) && nbDepile != NULL) {
        valueDepilee = nbDepile->valeur;
        pile->premier = nbDepile->suivant;
        free(nbDepile);
        pile->profondeur -= 1;
    }

    if(profondeur(pile) == 0) {
        pile->premier = NULL;
    }

    return valueDepilee;
}
