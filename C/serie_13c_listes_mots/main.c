#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <ctype.h>
#include <stdbool.h>

// Entité "chaine"
typedef struct Mot Mot;
struct Mot {
    char *mot;
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
char *clean(char *mot) {

    // Nettoyage du fin du mot
    while (ispunct(mot[strlen(mot) - 1])) {
        mot[strlen(mot) - 1] = '\0';
    }

    // Nettoyage du début du mot
    while (ispunct(mot[0])) {
        // Parcourir la chaîne de caractère
        for (int i = 0; i < strlen(mot); i++) {
            mot[i] = mot[i + 1];
            if (i == strlen(mot)) {
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

// Recherche un mot dans une liste triée, incrémente et retourne le nombre d'occurences de ce mot
int search(Mot *motToSearch, ListeMot *liste) {

    if (strcmp(motToSearch->mot, liste->premier->mot) == 0) {
        liste->premier->nbOccurence++;
        return liste->premier->nbOccurence;
    }

    Mot *motTeste = malloc(sizeof(Mot));
    motTeste = liste->premier;

    for (int i = 0; i <= liste->nbMot; i++) {

        if (motTeste->suivant != NULL) {
            // if(strcmp("", motTeste->suivant->mot) == 0) {
            //    free(motTeste);
            // }else
            if (strcmp(motToSearch->mot, motTeste->suivant->mot) == 0) {
                motTeste->suivant->nbOccurence++;
                return motTeste->suivant->nbOccurence;
            }
            motTeste = motTeste->suivant;
        } else {
            return 0;
        }
    }
    return 0;
}


// Insère un mot dans une liste triée lexicographiquement et incrémente le compteur si le mot est déjà présent
void insert(char *mot, int MAX_CHAR, ListeMot *liste) {

    // Création d'un objet "mot"
    Mot *motToInsert = malloc(sizeof(Mot));
    motToInsert->mot = malloc(sizeof(char) * MAX_CHAR);
    memcpy(motToInsert->mot, mot, sizeof(char) * MAX_CHAR);
    motToInsert->precedent = NULL;
    motToInsert->suivant = NULL;

    // Si la liste est vide, on insère directement le mot
    if (liste->premier == NULL) {
        liste->premier = motToInsert;
        motToInsert->nbOccurence = 1;
        liste->nbMot = 1;
    } else {

        // Rechercher le mot dans la liste
        int nbOccurence = search(motToInsert, liste);

        if (nbOccurence == 0) {

            motToInsert->nbOccurence = 1;

            // Parcourir la liste pour voir où mettre notre chaine

            // Un seul mot dans la liste : mon mot à insérer est plus petit
            if (liste->premier->suivant == NULL) {
                if(strcmp(motToInsert->mot, liste->premier->mot) < 0) {
                    motToInsert->suivant = liste->premier;
                    liste->premier = motToInsert;
                } else {
                    motToInsert->precedent = liste->premier;
                    liste->premier->suivant = motToInsert;
                }
                liste->nbMot++;
            } else {

                Mot *mot1 = liste->premier;
                Mot *mot2 = liste->premier->suivant;

                for (int j = 0; j <= liste->nbMot; j++) {

                    // mot 1 < mot à insérer < mot 2

                    bool motToCompareLesserThanMotToInsert = strcmp(mot1->mot, motToInsert->mot) < 0;
                    bool nextMotToCompareGreaterThanMotToInsert = strcmp(mot2->mot, motToInsert->mot) > 0;

                    if (motToCompareLesserThanMotToInsert && nextMotToCompareGreaterThanMotToInsert) {

                        // Lien entre mot 1 et mot à insérer
                        motToInsert->precedent = mot1;
                        mot1->suivant = motToInsert;

                        // Lien entre mot à insérer et mot 2
                        motToInsert->suivant = mot2;
                        mot2->precedent = motToInsert;

                        motToInsert->nbOccurence = 1;
                        liste->nbMot++;
                    }

                    bool lastMotLessserThanMotToInsert = strcmp(mot1->mot, motToInsert->mot) < 0;
                    bool nextMotToCompareIsNull = mot1->suivant == NULL;

                    // Test du dernier mot
                    if (lastMotLessserThanMotToInsert && nextMotToCompareIsNull) {
                        mot1->suivant = motToInsert;
                        motToInsert->precedent = mot1;
                        motToInsert->suivant = NULL;
                    }

                    mot1 = mot2;
                    if(mot2->suivant != NULL) {
                        mot2 = mot2->suivant;
                    }
                }
            }
        }
    }
    // free(motToInsert);
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
    ListeMot *liste1 = initListe();
    const char NOM_FICHIER_1[] = "/Users/evlyn/SynologyDrive/Hepia/repo_hepia/C/serie_13c_listes_mots/languageSymbolismMusic.txt";
    const char NOM_FICHIER_2[] = "onTheOriginOfMusic.txt";
    const int MAX_CHAR = 30;
    FILE *fid;
    char *mot = malloc(sizeof(char) * MAX_CHAR);
    char *motCleane;

    fid = fopen(NOM_FICHIER_1, "r"); // Ouverture du fichier

    if (fid != NULL) {
        while (!feof(fid)) {
            fscanf(fid, "%s", mot);

            char *newMot = malloc(sizeof(char) * MAX_CHAR);

            // Nettoyage des caractères de ponctuation et mise en minuscules
            motCleane = clean(mot);
            memcpy(newMot, motCleane, sizeof(char) * MAX_CHAR);

            // Insérer le mot dans la liste
            insert(motCleane, MAX_CHAR, liste1);
            free(newMot);
        }
        fclose(fid); // fermeture du fichier
    } else {
        printf("Le fichier n'a pas pu être ouvert !");
    }

    Mot *motALire = liste1->premier;
    for (int i = 0; i < liste1->nbMot; i++) {

        printf("Mot : %s et Nb occurences : %d \n", motALire->mot, motALire->nbOccurence);
        motALire = motALire->suivant;
    }
}


