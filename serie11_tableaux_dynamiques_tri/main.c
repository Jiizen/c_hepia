/**
 * Série 11 : Tableaux dynamiques et tri
 * Dezegher Evlyn
 * Le 20 mars 2018
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Chaine_char {
    char *caracteres;
};
typedef struct Chaine_char Chaine;

struct TableauString {
    int size;
    Chaine *chaine;
};
typedef struct TableauString TabString;

TabString * creerTab(int maxChar, int nbLignes) {
    // Initialisation du tableau dynamique
    TabString * tableau;
    tableau = (TabString *) malloc(sizeof(TabString));
    tableau->size = nbLignes;
    tableau->chaine = (Chaine *) malloc(sizeof(maxChar) * nbLignes);
    return tableau;
}

void afficherTab(TabString * tableau) {
    int i;
    for (i = 0; i < tableau->size; i++) {
        printf("%s \n", tableau->chaine[i].caracteres);
    }
}

/*
void copierTab() {

}

void concatTab() {

}
*/

TabString * trierTab(TabString * tableau) {

    int i, j;
    Chaine temp;

    for(i = 0; i < tableau->size;i++) {
        for(j = 1; j < tableau->size; j++) {
            if(strcmp(tableau->chaine[i].caracteres, tableau->chaine[j].caracteres) < 0) {
                temp = tableau->chaine[i];
                tableau->chaine[i] = tableau->chaine[j];
                tableau->chaine[j] = temp;
            }
        }
    }
    return tableau;
}
/*
void detruireTab() {

}*/

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

    // Création entité premier tableau
    TabString * tableau1 = creerTab(MAX_CHAR, TAILLE_FICHIER_1);

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
    afficherTab(tableau1);

    // Trier le tableau par sélection
    TabString * tableau1Trie = trierTab(tableau1);

    // Afficher le tableau trié
    afficherTab(tableau1Trie);



    // Lire le fichier etudiants3.txt contenant 148 chaînes de caractères
}