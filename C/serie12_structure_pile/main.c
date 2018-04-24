#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Entité "lettre"
typedef struct Lettre Lettre;
struct Lettre {
    char valeur;
    Lettre *suivante;
};

// Entité pile
typedef struct Pile Pile;
struct Pile {
    int profondeur;
    Lettre *premiere;
};

// Initialisation de la pile : on alloue la mémoire pour la taille d'une pile et on définit les valeurs de base pour profondeur et premier élément
Pile *initPile() {
    Pile *pile = malloc(sizeof(Pile));
    pile->profondeur = 0;
    pile->premiere = NULL;
    return pile;
}

// On récupère la profondeur de la pile
int profondeur(Pile *pile) {
    return pile->profondeur;
}

// On vérifie si la pile est vide. Profondeur = 0 ?
bool estVide(Pile *pile) {
    if (pile->profondeur == 0) {
        return true;
    } else {
        return false;
    }
}

// On récupère l'élément tout en haut de la pile
Lettre * sommet(Pile *pile) {
    return pile->premiere;
}

/* On ajoute une lettre en haut de la pile : allocation mémoire pour une lettre + définition valeurs lettre.
 * On définit que la lettre en haut de la pile devient la suivante et que la nouvelle est le premier élément
 * de la pile
 */
void empiler(Pile *pile, char ch) {
    Lettre *newLettre = malloc(sizeof(Lettre));
    newLettre->valeur = ch;
    if(sommet(pile) != NULL) {
        newLettre->suivante = sommet(pile);
    }
    pile->premiere = newLettre;
    pile->profondeur += 1;
}

/* On enlève la lettre qui est en haut de la pile
 * On sélectionne la pile au sommet et la pile n'est pas vide,
 * On définit que la première lettre de la pile devient celle d'après
 * et on supprime la lettre dépilée, qui est celle tout en haut
 * On baisse la profondeur de 1, car on a enlevé un élément
 */
char depiler(Pile *pile) {
    char charDepile = '/';
    Lettre *lettreDepilee = sommet(pile);

    if (!estVide(pile) && lettreDepilee != NULL) {
        charDepile = lettreDepilee->valeur;
        pile->premiere = lettreDepilee->suivante;
        free(lettreDepilee);
        pile->profondeur -= 1;
    }
    return charDepile;
}

int main() {

    // Entree de la chaine de caractères
    printf("Veuillez entrer une chaîne de caractères : ");
    char ch;

    // Initialisation de la pile
    Pile *chaine = initPile();

    // empiler les caractères
    while (1) {
        ch = getchar();
        if (ch == '\n')
           break;
        empiler(chaine, ch);
    }

    // Création d'une nouvelle pile pour mettre les lettres à l'endroit
    Pile *chaineEndroit = initPile();

    // Empiler la nouvelle chaîne à l'endroit et dépiler les caractères de l'autre
    while(profondeur(chaine) > 0) {
        empiler(chaineEndroit, chaine->premiere->valeur);
        depiler(chaine);
    }

    // Dépiler la chaîne à l'endroit
    while(profondeur(chaineEndroit) > 0) {
        char chDepile = depiler(chaineEndroit);
        printf("%c \n", chDepile);
    }
}