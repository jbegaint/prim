#include <stdlib.h>
#include <stdio.h>

#include "arbre.h"
#include "sommet.h"
#include "arc.h"

#include "utils.h"

void ajouter_arbre(Arc* arc, Sommet* tab_sommet) {
	
	Arbre p = NULL;

	p = malloc(sizeof(*p));
	if ( p == NULL ) {
		die("Allocation impossible");
	}

	Sommet* sommet_depart = &tab_sommet[arc->sommet_depart];
	Sommet* sommet_arrive = &tab_sommet[arc->sommet_arrive];


	Arbre noeudSommetDepart = sommet_depart->noeudArbreACM;

	p->sommet = sommet_arrive;
	p->freres = noeudSommetDepart->fils;

	p->fils = NULL;

	noeudSommetDepart->fils = p;

	sommet_arrive->noeudArbreACM = p;
}
	