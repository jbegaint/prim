#include <stdlib.h>

#include "arbre.h"
#include "sommet.h"

Arbre ajouter_arbre(Arc* arc, Arbre r) {

	Arbre p = (Arbre) malloc(sizeof(*p));
	/*
	// Sommet* sommet_depart;
	// Sommet* sommet_arrive;

	// sommet_depart = arc->sommet_depart;
	// sommet_arrive = arc->sommet_arrive;

	// Arbre noeudSommetDepart;
	// noeudSommetDepart = sommet_depart->noeudArbreACM;

	// p->sommet = sommet_arrive;
	// p->freres = noeudSommetDepart->fils;
	// noeudSommetDepart->fils = p;

	// sommet_arrive->noeudArbreACM = p;
	*/
	
	return p;
}
