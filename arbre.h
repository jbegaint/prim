#ifndef ARBRE_H
#define ARBRE_H

#include "sommet.h"

/* arbre fils-frère, arbre n-aire */

typedef struct NoeudArbre {
	Sommet sommet;
	struct NoeudArbre *fils;
	struct NoeudArbre  *freres;
} *Arbre;


Arbre ajouter_arbre(Arc*);

#endif