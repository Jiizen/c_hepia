#include <stdio.h>
#include <stdlib.h>
#include <tcl.h>
#include <memory.h>
#include <ctype.h>

// Entité "chaine"
typedef struct Mot Mot;
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

// Nettoie un mot
char * clean(char * mot) {

    // Nettoyage du fin du mot
    while(ispunct(mot[strlen(mot) - 1])) {
        mot[strlen(mot) - 1] = '\0';
    }

    // Nettoyage du début du mot
    while(ispunct(mot[0])) {
        // Parcourir la chaîne de caractère
        for(int i = 0; i < strlen(mot); i++) {
            mot[i] = mot[i + 1];
            if(i == strlen(mot)) {
                mot[i] = '\0';
            }
        }
    }

    // Mettre tout en minuscule
    for (int i = 0; i < strlen(mot); i++) {
        mot[i] = tolower(mot[i]);
    }
    // printf("%s \n", mot);
    return mot;
}

//// Recherche un mot dans une liste triée et retourne le nombre d'occurences de ce mot
//void search() {
//
//}
//

// Insère un mot dans une liste triée lexicographiquement et incrémente le compteur si le mot est déjà présent
void insert(char * mot, ListeMot * liste) {

    // Création d'un objet "mot"
    Mot *motToInsert = malloc(sizeof(Mot));
    motToInsert->mot = mot;

    // Si la chaîne est vide, on insère directement le mot
    if(liste->premier == NULL) {
        liste->premier = motToInsert;
        motToInsert->nbOccurence = 0;
        liste->nbMot = 1;
    } else {

        // Rechercher le mot dans la liste. S'il y est : le trouver et augmenter son nb d'occurences de 1 ; sinon, trouver où le positionner
        int * nbOccurence = search(motToInsert);
        if(nbOccurence != NULL) {
            nbOccurence++;
        } else {

            motToInsert->nbOccurence = 0;

            // Parcourir la liste pour voir où mettre notre chaine

            Mot *motToCompare = malloc(sizeof(Mot));
            motToCompare = liste->premier;

            if(strcmp(motToCompare->mot, motToInsert->mot) < 0 && strcmp(motToInsert->mot, motToCompare->suivant->mot) < 0) {
                liste->premier = motToInsert;
                motToCompare->precedent = motToInsert;
            } else {

                for(int j = 0; j < liste->nbMot; j++) {
                    if(strcmp(motToCompare->mot, motToInsert->mot) < 0 && strcmp(motToInsert->mot, motToCompare->suivant->mot) < 0) {
                        // motToInsert

                        

                    }
                }

            }
        }
    }
}

//// Supprime un mot dans une liste triée
//void delete() {
//
//}
//
//// Retourne une liste triée avec tous les mots communs à 2 listes triées (met aussi leur nombre d'occurences)
//void intersect() {
//
//}
//
//// Retourne une liste triée avec tous les mots d'une 1ère liste triée n'apparaissant pas dans une seconde
//void difference() {
//
//}
//
//// Concatène 2 listes triées. Nombre d'occurences des mots communs sommé.
//void concat() {
//
//}

int main() {

    //if (strcmp(tableau->chaine[i].caracteres, tableau->chaine[j].caracteres) < 0) {

    // Initialisation de la liste de mots
    ListeMot *liste = initListe();
    const char NOM_FICHIER_1[] = "languageSymbolismMusic.txt";
    const char NOM_FICHIER_2[] = "onTheOriginOfMusic.txt";
    const int MAX_CHAR = 30;
    FILE *fid;
    char mot[MAX_CHAR];
    char * motCleane;

    fid = fopen(NOM_FICHIER_1, "r"); // Ouverture du fichier

    if(fid != NULL) {
        while (!feof(fid)) {
            fscanf(fid, "%s", mot);

            // Nettoyage des caractères de ponctuation et mise en minuscules
            motCleane = clean(mot);

            // Insérer le mot dans la liste
            insert(motCleane, liste);
        }
        fclose(fid); // fermeture du fichier
    } else {
        printf("Le fichier n'a pas pu être ouvert !");
    }
}


