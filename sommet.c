#include <stdlib.h>
#include <float.h>

#include "sommet.h"
#include "liste.h"

Sommet trouver_min_liste_sommet(ListeSommet L) 
{
	ListeSommet p;
	Sommet sommet_ppc_min;
	float min = FLT_MAX;

	for(p=L; !est_vide_liste((Liste) p); p=p->suiv) {
		if ( (p->sommet).PPC < min ) {
			min = (p->sommet).PPC;
			sommet_ppc_min = p->sommet;
		}
	}
	
	return sommet_ppc_min;
}	