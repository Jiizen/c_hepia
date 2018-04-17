#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Lettre Lettre;
struct Lettre {
    char valeur;
    Lettre *suivante;
};

typedef struct Pile Pile;
struct Pile {
    int profondeur;
    Lettre *premiere;
};

Pile *initPile() {
    Pile *pile = malloc(sizeof(Pile));
    pile->profondeur = 0;
    pile->premiere = NULL;
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

Lettre * sommet(Pile *pile) {
    return pile->premiere;
}

void empiler(Pile *pile, char ch) {
    Lettre *newLettre = malloc(sizeof(Lettre));
    newLettre->valeur = ch;
    if(sommet(pile) != NULL) {
        newLettre->suivante = sommet(pile);
    }
    pile->premiere = newLettre;
    pile->profondeur += 1;
}

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