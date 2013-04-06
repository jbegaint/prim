#include <stdlib.h>

#include "arbre.h"
#include "sommet.h"

Arbre ajouter_arbre(Arc* arc) {

	if (s == NULL)
		return NULL;

	if( !a || )

	// CAS SI ARBRE NUL

	if(!)

	Sommet* sommetDepart = noeudArbreACM -> sommet;
	Sommet* sommetArrive;

	if (*sommetDepart == Arc->sommet_depart)
		sommetArrive = Arc->sommet_arrive;
	else
		sommetArrive = Arc->sommet_depart;

	Arbre noeudSommetDepart = sommetDepart -> noeudArbreACM;

	Arbre p = (Arbre) malloc(sizeof(*p));

	p->sommet = sommetArrive;
	p->freres = noeudSommetDepart->fils;

	noeudSommetDepart->fils = p;

	sommetArrive->noeudArbreACM = p;

	return p;
}
