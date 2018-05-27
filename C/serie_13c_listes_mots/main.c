/**
 * Created by Evlyn
 * TP : Exercice 13C - Liste dynamique de mots
 * Liste de mots triés et nettoyés
 */

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <ctype.h>
#include <stdbool.h>

// Entité mot
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

    return mot;
}

// Recherche un mot dans une liste triée, incrémente et retourne le nombre d'occurences de ce mot
int search(Mot *motToSearch, ListeMot *liste) {

    // Si le mot à chercher est le même que le premier mot de la liste, on incrémente son nombre d'occurences
    if (strcmp(motToSearch->mot, liste->premier->mot) == 0) {
        liste->premier->nbOccurence++;
        return liste->premier->nbOccurence; // et on retourne combien de fois le mot est présent dans la liste
    }

    Mot *motTeste = malloc(sizeof(Mot));
    motTeste = liste->premier;

    // On parcourt la liste de mots
    for (int i = 0; i <= liste->nbMot + 1; i++) {

        // Tant qu'on a un mot qui suit, on teste si notre mot apparaît dans la liste
        if (motTeste->suivant != NULL) {
            if (strcmp(motToSearch->mot, motTeste->suivant->mot) == 0) {
                motTeste->suivant->nbOccurence++;
                return motTeste->suivant->nbOccurence; // Si oui, on incrément nbOccurences et on le retourne
            }
            motTeste = motTeste->suivant;
        } else {
            return 0; // Si suivant est null, on retourne 0
        }
    }
    return 0; // Si on a rien trouvé, on retourne 0
}

Mot *initMot(Mot *motToInsert, char *mot, int MAX_CHAR) {
    motToInsert->mot = malloc(sizeof(char) * MAX_CHAR);
    memcpy(motToInsert->mot, mot, sizeof(char) * MAX_CHAR);
    motToInsert->precedent = NULL;
    motToInsert->suivant = NULL;
    return motToInsert;
}

// Insère un mot dans une liste triée lexicographiquement et incrémente le compteur si le mot est déjà présent
void insert(char *mot, int MAX_CHAR, ListeMot *liste) {

    // Initialisation d'un objet "mot"
    Mot *motToInsert = malloc(sizeof(Mot));
    motToInsert = initMot(motToInsert, mot, MAX_CHAR);

    // Si la liste est vide, on insère directement le mot
    if (liste->premier == NULL) {

        liste->premier = motToInsert;
        motToInsert->nbOccurence = 1;
        liste->nbMot = 1;

    } else { // Autrement, on va chercher le mot pour voir s'il existe ou pas dans la liste

        // Rechercher le mot dans la liste
        int nbOccurence = search(motToInsert, liste);

        // Si pas présent, on va chercher où le placer dans la liste
        if (nbOccurence == 0) {

            motToInsert->nbOccurence = 1; // Nombre d'occurences défini à 1

            // Si un seul mot dans la liste : avant ou après premier mot de la liste
            if (liste->premier->suivant == NULL) {
                if (strcmp(motToInsert->mot, liste->premier->mot) < 0) {
                    motToInsert->suivant = liste->premier;
                    liste->premier = motToInsert;
                } else {
                    motToInsert->precedent = liste->premier;
                    liste->premier->suivant = motToInsert;
                }
                liste->nbMot++;

            // Si plusieurs mots dans la liste
            } else {

                Mot *mot1 = liste->premier;
                Mot *mot2 = liste->premier->suivant;

                for (int j = 0; j <= liste->nbMot + 1; j++) {

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

                    // Savoir où placer notre mot si on est au dernier élément de la liste
                    bool lastMotLessserThanMotToInsert = strcmp(mot1->mot, motToInsert->mot) < 0;
                    bool nextMotToCompareIsNull = mot1->suivant == NULL;

                    // Si le dernier mot est plus petit que le nôtre, notre mot prend la dernière place
                    if (lastMotLessserThanMotToInsert && nextMotToCompareIsNull) {
                        mot1->suivant = motToInsert;
                        motToInsert->precedent = mot1;
                        motToInsert->suivant = NULL;
                    }

                    mot1 = mot2;
                    if (mot2->suivant != NULL) {
                        mot2 = mot2->suivant;
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

    // Initialisation de la liste de mots
    ListeMot *liste1 = initListe();
    ListeMot *liste2 = initListe();

    // Variables fichiers
    //const char NOM_FICHIER_1[] = "/Users/evlyn/SynologyDrive/Hepia/repo_hepia/C/serie_13c_listes_mots/languageSymbolismMusic.txt";
    const char NOM_FICHIER_1[] = "languageSymbolismMusic.txt";
    const char NOM_FICHIER_2[] = "onTheOriginOfMusic.txt";
    FILE *fid;

    // Variables mots
    const int MAX_CHAR = 30;
    char *mot = malloc(sizeof(char) * MAX_CHAR);
    char *motCleane;

    // CONSTRUCTION LISTE 1

    printf("Construction de la liste 1 ! \n");

    fid = fopen(NOM_FICHIER_1, "r"); // Ouverture du fichier

    if (fid != NULL) {
        while (!feof(fid)) { // Tant qu'on a pas atteint la fin du fichier
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
        printf("Le fichier %s n'a pas pu être ouvert !", NOM_FICHIER_1);
    }

    // CONSTRUCTION LISTE 2

    printf("\n Construction de la liste 2 ! \n");

    fid = fopen(NOM_FICHIER_2, "r"); // Ouverture du fichier

    if (fid != NULL) {
        while (!feof(fid)) { // Tant qu'on a pas atteint la fin du fichier
            fscanf(fid, "%s", mot);

            char *newMot = malloc(sizeof(char) * MAX_CHAR);

            // Nettoyage des caractères de ponctuation et mise en minuscules
            motCleane = clean(mot);
            memcpy(newMot, motCleane, sizeof(char) * MAX_CHAR);

            // Insérer le mot dans la liste
            insert(motCleane, MAX_CHAR, liste2);
            free(newMot);
        }
        fclose(fid); // fermeture du fichier
    } else {
        printf("Le fichier %s n'a pas pu être ouvert !", NOM_FICHIER_2);
    }

    // Affichage de la liste 1
    Mot *motALire1 = liste1->premier;
    for (int i = 0; i <= liste1->nbMot + 1; i++) {
        printf("Le mot '%s' a %d occurence(s) \n", motALire1->mot, motALire1->nbOccurence);
        motALire1 = motALire1->suivant;
    }

    // Affichage de la liste 2
    Mot *motALire2 = liste2->premier;
    for (int j = 0; j <= liste2->nbMot + 1; j++) {
        printf("Le mot '%s' a %d occurence(s) \n", motALire2->mot, motALire2->nbOccurence);
        motALire2 = motALire2->suivant;
    }
}


