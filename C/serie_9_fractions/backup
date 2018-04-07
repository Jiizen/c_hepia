#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct Fraction_S {
    int num; // Numérateur
    int den; // Dénominateur
};

// Lire : lit une fraction au clavier
struct Fraction_S lire() {

    struct Fraction_S fraction;

    printf("Numérateur : ");
    scanf("%d", &fraction.num);

    printf("Dénominateur : ");
    scanf("%d", &fraction.den);

    return fraction;
}

// Ecrire : affiche une fraction à l'écran
void ecrire(struct Fraction_S fraction) {
    printf("%d/%d \n", fraction.num, fraction.den);
}

// PGCD : calcule le PGCD de 2 nombres entiers positifs (appelée par réduire)
int calculePgcd(int nb1, int nb2) {

    // Si 2 nombres négatifs : les rendre positif
    nb1 = abs(nb1);
    nb2 = abs(nb2);

    while ((nb1 % nb2) != 0 && nb2 != 0) {
        int newNumerateur = nb2;
        int newDenominateur = nb1 % nb2;

        nb1 = newNumerateur;
        nb2 = newDenominateur;
    }
    return nb2; // Correspond au PGCD
}

int calculePpcm(struct Fraction_S fraction1, struct Fraction_S fraction2) {
    return (abs(fraction1.den) * abs(fraction2.den)) / calculePgcd(abs(fraction1.den), abs(fraction2.den));
}

// Reduire : met une fraction sous forme irréductible
struct Fraction_S reduire(struct Fraction_S fraction) {

    int pgcd = calculePgcd(fraction.num, fraction.den); // Mettre la fraction sous forme irréductible

    fraction.num = fraction.num / pgcd;
    fraction.den = fraction.den / pgcd;

    return fraction;
}

// Add : additionne 2 fractions (résultat : irréductible)
struct Fraction_S add(struct Fraction_S fraction1, struct Fraction_S fraction2) {

    // Calculer le plus petit commun multiple pour avoir un dénominateur commun afin de faire l'addition
    int ppcm = calculePpcm(fraction1, fraction2);

    int multipleNumFraction1 = ppcm / fraction1.den;
    int multipleNumFraction2 = ppcm / fraction2.den;

    // On calcule les nouveaux numérateurs, sur leur nouveau dénominateur commun (PPCM)
    int newNumerateur1 = fraction1.num * multipleNumFraction1;
    int newNumerateur2 = fraction2.num * multipleNumFraction2;

    // Addition des numérateurs
    int additionNums = newNumerateur1 + newNumerateur2;

    struct Fraction_S fractionAdded;
    fractionAdded.num = additionNums;
    fractionAdded.den = ppcm;

    return reduire(fractionAdded);
}

// Soust : soustrait 2 fractions (résultat : irréductible)
struct Fraction_S soust(struct Fraction_S fraction1, struct Fraction_S fraction2) {

    // Calculer le plus petit commun multiple pour avoir un dénominateur commun afin de faire l'addition
    int ppcm = calculePpcm(fraction1, fraction2);

    int multipleNumFraction1 = ppcm / fraction1.den;
    int multipleNumFraction2 = ppcm / fraction2.den;

    // On calcule les nouveaux numérateurs, sur leur nouveau dénominateur commun (PPCM)
    int newNumerateur1 = fraction1.num * multipleNumFraction1;
    int newNumerateur2 = fraction2.num * multipleNumFraction2;

    // Addition des numérateurs
    int soustractionNums = newNumerateur1 - newNumerateur2;

    struct Fraction_S fractionSubstracted;
    fractionSubstracted.num = soustractionNums;
    fractionSubstracted.den = ppcm;

    return reduire(fractionSubstracted);
}

// Fonction pour inverser le numérateur et le dénominateur
struct Fraction_S inv(struct Fraction_S fraction) {
    int tmp;
    tmp = fraction.num;
    fraction.num = fraction.den;
    fraction.den = tmp;
    return fraction;
}

// Mult : mutiplication de 2 fractions / 1 entier et 1 fraction (résultat : irréductible)
struct Fraction_S mult(struct Fraction_S fraction1, struct Fraction_S fraction2) {
    struct Fraction_S fractionMultipliee;
    fractionMultipliee.num = fraction1.num * fraction2.num;
    fractionMultipliee.den = fraction1.den * fraction2.den;
    return reduire(fractionMultipliee);
}

// Multiplication entier x fraction
struct Fraction_S multEntierXFraction(int entier, struct Fraction_S fraction) {
    struct Fraction_S entierFractionne;
    entierFractionne.num = entier;
    entierFractionne.den = 1;
    return mult(entierFractionne, fraction);
}

// Multiplication fraction x entier
struct Fraction_S multFractionXEntier(struct Fraction_S fraction, int entier) {
    struct Fraction_S entierFractionne;
    entierFractionne.num = entier;
    entierFractionne.den = 1;
    return mult(fraction, entierFractionne);
}

/* Div : division de 2 fractions / 1 entier et 1 fraction (résultat : irréductible)
 * (a/b)/(c/d) = a/b X d/c
 */
struct Fraction_S divide(struct Fraction_S fraction1, struct Fraction_S fraction2) {
    struct Fraction_S fractionX;
    fractionX.num = 0;
    fractionX.den = 0;
    if(fraction1.den != 0 && fraction2.num != 0) {
        return mult(fraction1, inv(fraction2));
    }
    return fractionX;
}

// Division entier x fraction
struct Fraction_S divEntierXFraction(int entier, struct Fraction_S fraction) {
    struct Fraction_S entierFractionne;
    entierFractionne.num = entier;
    entierFractionne.den = 1;
    return divide(entierFractionne, fraction);
}

// Division fraction x entier
struct Fraction_S divFractionXEntier(struct Fraction_S fraction, int entier) {
    struct Fraction_S entierFractionne;
    entierFractionne.num = entier;
    entierFractionne.den = 1;
    return divide(fraction, entierFractionne);
}

// Puissance : met une fraction à une puissance entière (résultat : irréductible)
struct Fraction_S puissance(struct Fraction_S fraction, int entier) {
    struct Fraction_S fractionEleveePuissance;
    fractionEleveePuissance.num = pow(fraction.num, entier);
    fractionEleveePuissance.den = pow(fraction.den, entier);
    return reduire(fractionEleveePuissance);
}

int main() {

    typedef struct Fraction_S Fraction;
    Fraction fraction;
    int pgcd;

    fraction = lire(); // Entrer une fonction
    ecrire(fraction); // Afficher la fonction

    if (fraction.den == 0) {
        printf("Dénominateur à 0, division impossible");
    } else {
        fraction = reduire(fraction); // Mettre la fraction sous forme irréductible
    }
    printf("Fraction réduite : ");
    ecrire(fraction);

    Fraction secondeFraction;
    secondeFraction.num = 8;
    secondeFraction.den = 5;

    // Addition de 2 fractions : fraction irréductible
    Fraction fractionAfterAddition = add(fraction, secondeFraction);
    printf("Addition : %d/%d + %d/%d = ", fraction.num, fraction.den, secondeFraction.num, secondeFraction.den);
    ecrire(fractionAfterAddition);

    // Soustraction de 2 fractions : fraction irréductible
    Fraction fractionAfterSubstraction = soust(fraction, secondeFraction);
    printf("Soustraction : %d/%d - %d/%d = ", fraction.num, fraction.den, secondeFraction.num, secondeFraction.den);
    ecrire(fractionAfterSubstraction);

    // Multiplication de 2 fractions
    Fraction fractionAfterMultiplication = mult(fraction, secondeFraction);
    printf("Multiplication de 2 fractions : %d/%d * %d/%d = ", fraction.num, fraction.den, secondeFraction.num, secondeFraction.den);
    ecrire(fractionAfterMultiplication);

    // Multiplication entier X fraction
    int entierFirstMult = 4;
    Fraction fractionAfterMultiplicationWithIntFirst = multEntierXFraction(entierFirstMult, fraction);
    printf("Multiplication d'une fraction et d'un entier : %d/%d * %d = ", fraction.num, fraction.den, entierFirstMult);
    ecrire(fractionAfterMultiplicationWithIntFirst);

    // Multiplication fraction X entier
    int entierSecondMult = 18;
    Fraction fractionAfterMultiplicationWithIntSecond = multFractionXEntier(fraction, entierSecondMult);
    printf("Multiplication d'un entier et d'une fraction : %d/%d * %d = ", fraction.num, fraction.den, entierSecondMult);
    ecrire(fractionAfterMultiplicationWithIntSecond);

    // Division de 2 fractions
    Fraction fractionAfterDivision = divide(fraction, secondeFraction);
    if(fraction.num == 0 || secondeFraction.den == 0) {
        printf("Division de 2 fractions : (%d/%d) / (%d/%d) = Division par zéro impossible \n", fraction.num, fraction.den, secondeFraction.num, secondeFraction.den);
    } else {
        printf("Division de 2 fractions : (%d/%d) / (%d/%d) = ", fraction.num, fraction.den, secondeFraction.num, secondeFraction.den);
        ecrire(fractionAfterDivision);
    }

    // Division entier X fraction
    int entierFirstDiv = 0;
    Fraction fractionAfterDivisionWithIntFirst = divEntierXFraction(entierFirstDiv, fraction);
    if(fraction.num == 0 || entierFirstDiv == 0) {
        printf("Division d'une fraction et d'un entier : %d/%d * %d = Division par zéro impossible \n", fraction.num, fraction.den, entierFirstDiv);
    } else {
        printf("Division d'une fraction et d'un entier : %d/%d * %d = ", fraction.num, fraction.den, entierFirstDiv);
        ecrire(fractionAfterDivisionWithIntFirst);
    }

    // Division fraction X entier
    int entierSecondDiv = 18;
    Fraction fractionAfterDivisionWithIntSecond = divFractionXEntier(fraction, entierSecondDiv);
    if(fraction.num == 0 || entierSecondDiv == 0) {
        printf("Division d'un entier et d'une fraction : %d/%d * %d = Division par zéro impossible \n", fraction.num, fraction.den, entierSecondDiv);
    } else {
        printf("Division d'un entier et d'une fraction : %d/%d * %d = ", fraction.num, fraction.den, entierSecondDiv);
        ecrire(fractionAfterDivisionWithIntSecond);
    }

    // Puissance : fraction à une puissance entière
    int entierPuissance = 7;
    Fraction fractionAfterSup = puissance(fraction, entierPuissance);
    printf("Puissance : (%d/%d)^%d = ", fraction.num, fraction.den, entierPuissance);
    ecrire(fractionAfterSup);
}