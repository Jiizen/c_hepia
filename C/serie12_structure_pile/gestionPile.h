/////////////////////////////////////////////////////////////////////

#define MAXPILE 5000  // pile statique 

struct T_Pile       // descripteur de pile
{
   char p[MAXPILE]; // pile contenant des caractères
   int  nbEl;       // nombre d'éléments dans la pile
};

typedef struct T_Pile Pile;

//////////////////////////////////////////////////////////////////////

Pile *nouvellePile();
void  initPile(Pile *);
int   profondeur(Pile *);
int   estVide(Pile *);
char  elSommet(Pile *);
void  empiler(Pile *, char);
void  depiler(Pile *);

//////////////////////////////////////////////////////////////////////
