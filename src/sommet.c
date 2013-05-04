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
