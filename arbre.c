#include <stdlib.h>

#include "arbre.h"
#include "sommet.h"

Arbre ajouter_arbre(Arc* arc, Sommet* tab_sommet) {

	Arbre p = malloc(sizeof(*p));
	
	Sommet* sommet_depart = NULL;
	Sommet* sommet_arrive = NULL;

	sommet_depart = &tab_sommet[arc->sommet_depart];
	sommet_arrive = &tab_sommet[arc->sommet_arrive];

	Arbre noeudSommetDepart = malloc(sizeof(*noeudSommetDepart));

	p->sommet = sommet_arrive;
	p->freres = noeudSommetDepart->fils;
	noeudSommetDepart = sommet_depart->noeudArbreACM;
	noeudSommetDepart->fils = p;

	sommet_arrive->noeudArbreACM = p;

	return p;
}
