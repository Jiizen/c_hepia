#include <stdio.h>
#include <stdlib.h>
#include <tcl.h>

// Entité "chaine"
typedef struct Chaine Mot;
struct Mot {
    char* mot;
    int nbOccurence;
    Mot *suivant;
    Mot *precedent;
};

// Structure de la liste de mots
typedef struct ListeMot ListeMot;
struct ListeMot {
    int nbMot;
    Mot *premier;
};

// Initialise une nouvelle liste de mots
ListeMot *initListe() {
    ListeMot *liste = malloc(sizeof(ListeMot));
    liste->nbMot = 0;
    liste->premier = NULL;
    return liste;
}

// Insère un mot dans une liste triée lexicographiquement et incrémente le compteur si le mot est déjà présent
void insert() {

}

// Recherche un mot dans une liste triée et retourne le nombre d'occurences de ce mot
void search() {

}

// Supprime un mot dans une liste triée
void delete() {

}

// Retourne une liste triée avec tous les mots communs à 2 listes triées (met aussi leur nombre d'occurences)
void intersect() {

}

// Retourne une liste triée avec tous les mots d'une 1ère liste triée n'apparaissant pas dans une seconde
void difference() {

}

// Concatène 2 listes triées. Nombre d'occurences des mots communs sommé.
void concat() {

}

int main() {

    // Initialisation de la liste de mots
    ListeMot *liste = initListe();



    // On remplit la liste de nombres jusqu'à n
    //fillList(liste, n);
}
