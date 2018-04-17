#include <stdio.h>
#include <stdlib.h>

#include "gestionPile.h"

//////////////////////////////////////////////////////////////////////

Pile *nouvellePile()
{     
   return (Pile *) malloc(sizeof(Pile));
}

//////////////////////////////////////////////////////////////////////

void initPile(Pile *unePile)
{
   unePile->nbEl = 0;
}

//////////////////////////////////////////////////////////////////////
// nbre d'éléments de la pile

int profondeur(Pile *unePile)
{
   return unePile->nbEl;
}

//////////////////////////////////////////////////////////////////////

int estVide(Pile *unePile)
{
   return (profondeur(unePile) == 0);
}

//////////////////////////////////////////////////////////////////////
// retourne un caractère

char elSommet(Pile *unePile)     // la pile ne doit pas être vide
{
    return unePile->p[profondeur(unePile)-1];
	//return unePile->p[unePile->nbEl -1];
}

//////////////////////////////////////////////////////////////////////

void empiler(Pile *unePile, char unEl)
{
   if (profondeur(unePile) == MAXPILE)
   {
	   printf("Attention pile statique, il faut recompiler avec une plus grande taille.\n");
       exit(1);
   }
   
   unePile->p[profondeur(unePile)] = unEl;
   unePile->nbEl += 1;
}

//////////////////////////////////////////////////////////////////////
// ne pas dépiler si la pile est vide

void depiler(Pile *unePile)
{
   unePile->nbEl -= 1;
}

//////////////////////////////////////////////////////////////////////