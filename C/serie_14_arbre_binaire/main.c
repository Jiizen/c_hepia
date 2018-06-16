/**
 * Created by Evlyn
 * TP : Exercice 14 - Arbres binaires
 */

#include <stdio.h>
#include <stdlib.h>
#include <tcl.h>
#include <time.h>
#include <stdbool.h>
#include <memory.h>
#include <ctype.h>

/* STRUCTURES */

// Node
typedef struct Noeud Noeud;
struct Noeud {
    char valeur;
    int niveau;
    Noeud *gauche;
    Noeud *droite;
};

Noeud *initNoeud(char valeur) {
    Noeud *newNoeud = malloc(sizeof(Noeud));
    newNoeud->valeur = valeur; // Pour que ce soit compatible avec le morse
    newNoeud->niveau = 0;
    newNoeud->gauche = NULL;
    newNoeud->droite = NULL;
    return newNoeud;
}

/* FONCTIONS */

bool estNull(Noeud *noeud) {
    if (noeud) {
        return false;
    } else {
        return true;
    }
}

void insertNoeud(Noeud **arbre, int valeur) {

    Noeud *noeudTemp = initNoeud((char) valeur); // Cast char pour que ce soit compatible avec le morse
    Noeud *courant;
    Noeud *parent;

    if (estNull(*arbre)) { // Si l'arbre est vide, on insère de suite le noeud
        *arbre = noeudTemp;
    } else {
        courant = *arbre; // l'arbre n'est pas vide, on lui crée une variable temporaire

        while (1) { // Boucle infinie jusqu'à un return
            parent = courant; // Parent = racine

            if (valeur < parent->valeur) { // Si valeur à insérer est + petite que la valeur du parent, on va à gauche
                courant = courant->gauche; // Redéfinition du noeud courant à celui de gauche
                noeudTemp->niveau++;

                if (courant == NULL) { // Si l'emplacement est libre, on met la valeur courante du noeud à cet endroit
                    parent->gauche = noeudTemp;
                    return;
                }
            } // Sinon, on part à droite
            else {
                courant = courant->droite;
                noeudTemp->niveau++;

                if (courant == NULL) { // Insertion à droite quand emplacement libre
                    parent->droite = noeudTemp;
                    return;
                }
            }
        }
    }
}

void insertNoeudMorse(Noeud **arbre, char valeur, char *valeurMorse) {

    const char POINT = '.';
    const char TIRET = '-';

    Noeud *noeudTemp = initNoeud(valeur);
    Noeud *courant;
    Noeud *parent;

    if (estNull(*arbre)) {
        noeudTemp->valeur = '*';
        *arbre = noeudTemp;
    } else {

        courant = *arbre; // l'arbre n'est pas vide, on lui crée une variable temporaire

        while (1) { // Boucle infinie jusqu'à un return
            parent = courant; // Parent = racine

            for (int i = 0; i < strlen(valeurMorse); i++) {
                if (valeurMorse[i] == POINT) { // Si code morse == '.'
                    courant = courant->gauche; // Redéfinition du noeud courant à celui de gauche
                    noeudTemp->niveau++;
                    if(courant == NULL && i != strlen(valeurMorse) - 1) {
                        parent->gauche = initNoeud(' ');
                    }
                }
                if (valeurMorse[i] == TIRET) {
                    courant = courant->droite;
                    noeudTemp->niveau++;
                    if(courant == NULL && i != strlen(valeurMorse) - 1) {
                        parent->droite = initNoeud(' ');
                    }
                }
            }

            // Si emplacement libre et dernière valeur == point
            if(courant == NULL && valeurMorse[strlen(valeurMorse) - 1] == TIRET) {
                parent->gauche = noeudTemp;
                return;
            } else if(courant == NULL && valeurMorse[strlen(valeurMorse) - 1] == POINT) {
                parent->droite = noeudTemp;
                return;
            }
        }
    }
}

/*
 * Affichage de la valeur d’un noeud après les valeurs figurant dans son sous-arbre gauche et avant les
 * valeurs figurant dans son sous-arbre droit
 */
void parcoursInfixe(Noeud *arbre) {
    if (!estNull(arbre)) {
        parcoursInfixe(arbre->gauche); // Parcours des fils de gauche
        printf("%d ", arbre->valeur); // On affiche la valeur du noeud courant
        parcoursInfixe(arbre->droite); // Parcours des fils de droit
    }
}

char *clean(char *codeMorse) { // Nettoie code morse : enlève première lettre et les \r\n

    // Supprimer premier caractère : lettre latine et tout décaler
    if (codeMorse[0] >= 'A' && codeMorse[0] <= 'Z') {
        for (int i = 0; i < strlen(codeMorse); i++) {
            codeMorse[i] = codeMorse[i + 1];
            if (i == strlen(codeMorse)) {
                codeMorse[i] = '\0';
            }
        }
    }

    // Nettoyage du fin du codeMorse
    while (codeMorse[strlen(codeMorse) - 1] == '\r' || codeMorse[strlen(codeMorse) - 1] == '\n') {
        codeMorse[strlen(codeMorse) - 1] = '\0';
    }
    return codeMorse;
}

int main() {

    /** EXERCICE 1 */
    printf("EXERCICE 1 \n");

    // Génération de n nombres entiers aléatoires
    srand(time(0));
    const int n = 7;
    int tabNb[n];

    printf("Valeurs aléatoires : ");
    for (int i = 0; i < n; i++) {
        tabNb[i] = rand() % 100;
        printf("%d ", tabNb[i]);
    }
    // tabNb[0] = 10; tabNb[1] = 20; tabNb[2] = 4; tabNb[3] = 8; tabNb[4] = 5; tabNb[5] = 15; tabNb[6] = 3;

    // Premier noeud -> début de l'arbre : racine
    Noeud *arbre = NULL;

    for (int i = 0; i < n; i++) {
        insertNoeud(&arbre, tabNb[i]);
    }

    // Parcours symétrique de l'arbre
    printf("\nParcours infixé de notre arbre : ");
    parcoursInfixe(arbre);

    /** EXERCICE 2 */
    printf("\n\nEXERCICE 2 \n");

    /* Création de  l'arbre du code Morse (profondeur 4) */
    const char CODE_MORSE[] = "/Users/evlyn/SynologyDrive/Hepia/repo_hepia/C/serie_14_arbre_binaire/code-morse.txt";
    FILE *fid;
    char ligne[10];
    Noeud *arbreMorse = NULL;

    fid = fopen(CODE_MORSE, "r"); // Ouverture du fichier

    if (fid != NULL) {
        while (!feof(fid)) { // Tant qu'on a pas atteint la fin du fichier
            fgets(ligne, sizeof(ligne), fid);

            char lettreLatine = ligne[0]; // Récupération première lettre (latine)
            char *lettreMorse = clean(ligne); // Récupération propre du code morse

            if (lettreLatine != ' ') {
                Noeud *newNoeud = initNoeud(lettreLatine);
                insertNoeudMorse(&arbreMorse, lettreLatine, lettreMorse);
                // printf("Valeur : %c \n", newNoeud->valeur);
            }
        }
        fclose(fid); // fermeture du fichier
    } else {
        printf("Le fichier %s n'a pas pu être ouvert !", CODE_MORSE);
    }

    // Parcours symétrique de l'arbre du code Morse
    printf("\nParcours infixé de notre arbre Morse : ");
    //parcoursInfixe(arbreMorse);
}
