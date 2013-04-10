#pragma once

// #include "sommet.h"
/* arbre fils-frère, arbre n-aire */

#include "sommet.h"
#include "arc.h"

typedef struct NoeudArbre {
	Sommet* sommet;
	struct NoeudArbre *fils;
	struct NoeudArbre  *freres;
} *Arbre;


Arbre ajouter_arbre(Arc*, Arbre);
	