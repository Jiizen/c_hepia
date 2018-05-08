#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Entité "nombre"
typedef struct Nombre Nombre;
struct Nombre {
    int valeur;
    Nombre *suivant;
};

// Entité pile
typedef struct Pile Pile;
struct Pile {
    int profondeur;
    Nombre *premier;
};

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
