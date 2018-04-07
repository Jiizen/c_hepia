/**
 * Série 11 : Tableaux dynamiques et tri
 * Dezegher Evlyn
 * Le 20 mars 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Chaine_char {
    char *caracteres;
};
typedef struct Chaine_char Chaine;

struct TableauString {
    int size;
    Chaine *chaine;
};
typedef struct TableauString TabString;

TabString *creerTab(int maxChar, int nbLignes) {
    // Initialisation du tableau dynamique
    TabString *tableau;
    tableau = (TabString *) malloc(sizeof(TabString));
    tableau->size = nbLignes;
    tableau->chaine = (Chaine *) malloc(sizeof(maxChar) * (nbLignes + 1));
    return tableau;
}

void afficherTab(TabString *tableau) {
    int i;
    for (i = 0; i < tableau->size; i++) {
        printf("%s \n", tableau->chaine[i].caracteres);
    }
}

TabString *concatTab(TabString *tableau1, TabString *tableau2, TabString *tableauFinal) {
    int m = 0;
    for (int l = tableau1->size + 1; l < tableauFinal->size + 1; l++) {
        tableauFinal->chaine[l] = tableau2->chaine[m];
        m++;
    }
    return tableauFinal;
}

TabString *trierTab(TabString *tableau) {

    int i, j;
    Chaine temp;

    for (i = 0; i < tableau->size; i++) {
        for (j = 0; j < tableau->size; j++) {
            if (strcmp(tableau->chaine[i].caracteres, tableau->chaine[j].caracteres) < 0) {
                temp = tableau->chaine[i];
                tableau->chaine[i] = tableau->chaine[j];
                tableau->chaine[j] = temp;
            }
        }
    }
    return tableau;
}

void detruireTab(TabString *tableau) {
    free(tableau);
}

int main() {

    // Lecture du fichier
    const int TAILLE_FICHIER_1 = 300;
    const int TAILLE_FICHIER_2 = 148;
    const int MAX_CHAR = 80;
    const char NOM_FICHIER_1[] = "etudiants2.txt";
    const char NOM_FICHIER_2[] = "etudiants3.txt";

    FILE *fid;
    char unStr[MAX_CHAR];
    int i;

    /****** TABLEAU 1 ******/

    // Création entité premier tableau
    TabString *tableau1 = creerTab(MAX_CHAR, TAILLE_FICHIER_1);

    fid = fopen(NOM_FICHIER_1, "r"); // ouverture fichier

    // Lecture du fichier etudiants2.txr contenant 300 chaînes de caractères
    for (i = 0; i < TAILLE_FICHIER_1; i++) {
        fscanf(fid, "%s", unStr);

        // Malloc pour chaque chaine du tableau
        tableau1->chaine[i].caracteres = malloc(sizeof(unStr));

        // Construction du tableau de chaînes de caractères non trié
        strcpy(tableau1->chaine[i].caracteres, unStr);
    }
    fclose(fid); // fermeture du fichier

    // Afficher tableau1 non trié
    //afficherTab(tableau1);

    // Trier le tableau par sélection
    TabString *tableau1Trie = trierTab(tableau1);

    // Afficher le tableau trié
    //afficherTab(tableau1Trie);

    /****** TABLEAU 2 ******/

    // Création entité deuxième tableau
    TabString *tableau2 = creerTab(MAX_CHAR, TAILLE_FICHIER_2);

    fid = fopen(NOM_FICHIER_2, "r"); // ouverture fichier

    // Lire le fichier etudiants3.txt contenant 148 chaînes de caractères
    for (i = 0; i < TAILLE_FICHIER_2; i++) {
        fscanf(fid, "%s", unStr);

        // Malloc pour chaque chaine du tableau
        tableau2->chaine[i].caracteres = malloc(sizeof(unStr));

        // Construction du tableau de chaînes de caractères non trié
        if (((unStr[1] >= 'a' && unStr[1] <= 'z') || (unStr[0] >= 'A' && unStr[0] <= 'Z'))) {
            // Je ne parviens pas à enlever les caractères spéciaux (mauvais encodage... ?)
            strcpy(tableau2->chaine[i].caracteres, unStr);
        }
    }
    fclose(fid); // fermeture du fichier

    // Afficher tableau2 non trié
    //afficherTab(tableau2);

    // Trier le tableau par sélection
    TabString *tableau2Trie = trierTab(tableau2);

    // Afficher le tableau trié
    //afficherTab(tableau2Trie);

    /****** TABLEAU CONCAT ******/

    // Concaténer les 2 tableaux en 1 seul

    TabString *tableauConcat;
    tableauConcat->chaine = malloc(sizeof(MAX_CHAR) * (tableau1->size + 1));

    memcpy(tableauConcat, tableau1, sizeof(TabString));

    tableauConcat->size = tableau1->size + tableau2->size;
    tableauConcat = concatTab(tableau1, tableau2, tableauConcat);

    // Afficher tableau concaténé
    afficherTab(tableauConcat);

    // Trier le tableau par sélection
    TabString * tableauConcatTrie = trierTab(tableauConcat);

    // Afficher le tableau trié
    afficherTab(tableauConcatTrie);

    // Destruction des 2 autres tableaux
    detruireTab(tableau1);
    detruireTab(tableau2);
}
