/**
 * Created by Evlyn
 * TP : Exercice 13B : Liste dynamique circulaire
 * Problème de Joseph
 */

#include <stdio.h>
#include <stdlib.h>
#include <tcl.h>

// Entité "nombre"
typedef struct Nombre Nombre;
struct Nombre {
    int valeur;
    Nombre *suivant;
    Nombre *precedent;
};

// Structure de la liste dynamique circulaire
typedef struct ListeCirc ListeCirc;
struct ListeCirc {
    int nbElements;
    Nombre *premier;
};

ListeCirc *initList(int n) {
    ListeCirc *liste = malloc(sizeof(ListeCirc));
    liste->nbElements = n;
    liste->premier = NULL;
    return liste;
}

void fillList(ListeCirc *liste, int n) {
    Nombre *nb = malloc(sizeof(Nombre));
    for (int i = 1; i <= n; i++) {
        if (liste->premier != NULL) {
            Nombre *nbSuivant = malloc(sizeof(Nombre));
            nbSuivant->valeur = i;
            nb->suivant = nbSuivant;
            nbSuivant->precedent = nb;
            nb = nbSuivant;
            if (i ==
                n) { // Lorsqu'on arrive au dernier élément, on définit que le suivant est le premier de la liste (circulaire)
                nb->suivant = liste->premier;
                liste->premier->precedent = nb;
            }
        } else {
            nb->valeur = i;
            liste->premier = nb;
        }
    }
}

void deleteByJosephProblem(ListeCirc *liste, int k, int n) {

    Nombre *nbToDelete = malloc(sizeof(Nombre));
    // Définition du nombre duquel on part
    while (liste->nbElements > 0) {
        if (liste->nbElements == n) {
            nbToDelete = liste->premier;
            for (int l = 0; l < (k - 1); l++) {
                nbToDelete = nbToDelete->suivant;
            }
        }

        // Si la valeur à effacer est la premiere de la liste, définir que le premier élément de la liste est celui qui vient après le nombre à supprimer et que le précédent du premier de la liste est le précédent du nombre qui va être supprimé
        if (nbToDelete->valeur == liste->premier->valeur) {
            liste->premier = nbToDelete->suivant;
            liste->premier->precedent = nbToDelete->precedent;
        }

        // On rattache le chiffre d'avant et le chiffre d'après. Par exemple, si on supprime 3, on rattache 2 et 4, 4 étant l'élément venant après 2
        Nombre *nbToDeleteNow = malloc(sizeof(Nombre));
        nbToDeleteNow = nbToDelete; // Variable temporaire pour garder la structure du nombre en cours
        nbToDelete->precedent->suivant = nbToDelete->suivant;
        for (int m = 0; m < k; m++) {
            nbToDelete = nbToDelete->suivant; // Sélectionner le prochain nombre à supprimer
        }

        printf("Le nombre %d va être effacé ! \n", nbToDeleteNow->valeur);
        free(nbToDeleteNow);
        liste->nbElements -= 1; // On enlève un élément
    }
}

int main() {

    CONST int n = 8;
    CONST int k = 3;

    ListeCirc *liste = initList(n);

    // On remplit la liste de nombres jusqu'à n
    fillList(liste, n);

    // On supprime les nombres un à un, selon l'écart de k pour n tours
    deleteByJosephProblem(liste, k, n);
}
