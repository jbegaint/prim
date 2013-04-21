#include <stdlib.h>
#include <stdio.h>

#include "arbre.h"
#include "sommet.h"
#include "arc.h"

#include "utils.h"

Arbre ajouter_arbre(Arc* arc, Sommet* tab_sommet) {
	
	printf("%f %d %d\n", ((Arc*) arc)->cout, ((Arc*) arc)->sommet_depart, ((Arc*) arc)->sommet_arrive);

	Arbre p = NULL;

	p = malloc(sizeof(*p));
	if ( p == NULL ) {
		/*die("Allocation impossible");*/
		exit(EXIT_FAILURE);
	}

	Sommet* sommet_depart = &tab_sommet[arc->sommet_depart];;
	Sommet* sommet_arrive = &tab_sommet[arc->sommet_arrive];;

	Arbre noeudSommetDepart = sommet_depart->noeudArbreACM;

	printf("%s\n", (*(noeudSommetDepart->sommet)).nom);

	p->sommet = sommet_arrive;
	p->freres = noeudSommetDepart->fils;
	noeudSommetDepart->fils = p;

	sommet_arrive->noeudArbreACM = p;

	return p;
}
	