#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct Monome_A {
    int deg;
    float coef;
};
typedef struct Monome_A Monome;

struct Polynome_A {
    int size;
    Monome *p;
};
typedef struct Polynome_A Polynome;

// Fonction qui retourne un tableau dynamique de monomes
Polynome lire_coef_poly() {
    int nbMonomes;
    Polynome polynome;

    printf("Donnez le nombre total de coefficients : ");
    scanf("%d", &nbMonomes);
    polynome.size = nbMonomes;

    polynome.p = (Monome *) malloc(sizeof(Monome) * nbMonomes);

    for (int i = 0; i < nbMonomes; i++) {
        printf("Donnez le monôme de degré %d: ", i);
        polynome.p[i].deg = i;
        scanf("%f", &polynome.p[i].coef);
    }
    return polynome;
}

// Fonction qui affiche un polynôme à l'écran
void ecrire_poly(Polynome *polynome) {

    for (int i = polynome->size - 1; i >= 0; i--) {
        if (i != 0) {
            printf("%f^%d + ", polynome->p[i].coef, polynome->p[i].deg);
        } else {
            printf("%f^%d \n", polynome->p[i].coef, polynome->p[i].deg);
        }
    }
}

// Addition de 2 polynômes
Polynome add_poly(Polynome polynomeAdditionne, Polynome *polynome1, Polynome *polynome2) {

    if (polynome1->size > polynome2->size) {
        polynomeAdditionne.size = polynome1->size;
        int difference = polynome1->size - polynome2->size;
        Monome *monomes = (Monome *) malloc(sizeof(Monome) * polynomeAdditionne.size);
        polynomeAdditionne.p = monomes;

        for (int i = 0; i <= difference; i++) {
            polynomeAdditionne.p[polynome2->size + i].deg = polynome1->p[polynome2->size + i].deg;
            polynomeAdditionne.p[polynome2->size + i].coef = polynome1->p[polynome2->size + i].coef;
        }
    } else if (polynome2->size > polynome1->size) {
        polynomeAdditionne.size = polynome2->size;
        int difference = polynome2->size - polynome1->size;

        Monome *monomes = (Monome *) malloc(sizeof(Monome) * polynomeAdditionne.size);
        polynomeAdditionne.p = monomes;

        for (int i = 0; i <= difference; i++) {
            polynomeAdditionne.p[polynome1->size + i].deg = polynome2->p[polynome1->size + i].deg;
            polynomeAdditionne.p[polynome1->size + i].coef = polynome2->p[polynome1->size + i].coef;
        }
        polynome1->p = (Monome *) malloc(sizeof(Monome) * polynome1->size);
    } else {
        polynomeAdditionne.size = polynome1->size;
    }

    for (int i = 0; i < polynome1->size; i++) {
        for (int j = 0; j < polynome2->size; j++) {
            if (polynome1->p[i].deg == polynome2->p[j].deg) {
                int degre = polynome1->p[i].deg;
                polynomeAdditionne.p[degre].coef = polynome1->p[i].coef + polynome2->p[j].coef;
                polynomeAdditionne.p[degre].deg = degre;
            }
        }
    }
    return polynomeAdditionne;
}

int main() {
    Polynome polynome;
    polynome = lire_coef_poly();
    ecrire_poly(&polynome);

    Polynome secondPolynome;

    Monome *monomes = (Monome *) malloc(sizeof(Monome) * polynome.size);
    monomes[0].coef = 5;
    monomes[0].deg = 0;
    monomes[1].coef = 8;
    monomes[1].deg = 1;
    monomes[2].coef = 1;
    monomes[2].deg = 2;

    secondPolynome.size = 3;
    secondPolynome.p = monomes;

    Polynome polynomeAdditione;
    polynomeAdditione = add_poly(polynomeAdditione, &polynome, &secondPolynome);
    ecrire_poly(&polynomeAdditione);
}