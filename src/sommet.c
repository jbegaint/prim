#include <stdlib.h>
#include <float.h>
#include <stdio.h>

#include "sommet.h"
#include "liste.h"

Sommet trouver_min_liste_sommet(Liste L)
{
	Liste p;
	Sommet sommet_ppc_min;
	float min = FLT_MAX;

	for (p = L; !est_vide_liste(p); p = p->suiv) {
		if ((*(Sommet *) p->val).PPC < min) {
			min = (*(Sommet *) p->val).PPC;
			sommet_ppc_min = (*(Sommet *) p->val);
		}
	}

	return sommet_ppc_min;
}

Liste ajout_tri(Sommet * s, Liste L)
{

	Liste p = NULL;
	Liste q;

	if (est_vide_liste(L) || (*s).PPC < (*(Sommet *) L->val).PPC) {
		return ajouter_tete(s, L, sizeof(Sommet));
	}

	for (q = L; !est_vide_liste(q->suiv); q = q->suiv) {

		if ((*s).PPC < (*(Sommet *) q->suiv->val).PPC) {
			break;
		}
	}

	p = malloc(sizeof(*p));

	p->val = s;
	p->suiv = q->suiv;
	q->suiv = p;

	return L;
}
