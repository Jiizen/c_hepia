/**
 * Created by Evlyn on 15.05.18.
 * TP : Exercice 13A : Piles et listes
 * Structures et déclaration de fonctions concernant les piles
 */

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

Pile *initPile();
int profondeur(Pile *pile);
bool estVide(Pile *pile);
Nombre * sommet(Pile *pile);
void empiler(Pile *pile, int nb);
int depiler(Pile *pile);
