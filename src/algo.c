#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "sommet.h"
#include "arc.h"
#include "arbre.h"

#include "liste.h"
#include "file.h"
#include "utils.h"

#include "algo.h"

Liste afficheRSB_iteratif(Arbre r)
{
	Arbre a;
	Liste l = NULL;
	Liste arbre = NULL;
	l = ajouter_queue(&r, l, sizeof(Arbre));

	while (!est_vide_liste(l)) {
		for (a = *(Arbre *) l->val; a; a = a->fils) {

			arbre = ajouter_queue(a->sommet, arbre, sizeof(Sommet));

			if (a->freres)
				l = ajouter_queue(&(a->freres), l, sizeof(Arbre));
		}
		l = supprimer_tete(l);
	}
	return arbre;
}

void afficheRSB(Arbre r)
{
	/*affiche Racine Fils Freres */
	if (r) {
		printf("%s ", (*(r->sommet)).nom);
		afficheRSB(r->fils);
		afficheRSB(r->freres);
	}
}

Arbre algo_arbreACM(File fileACM, Sommet * tab_sommet, int num_depart)
{

	Arbre arbreACM = NULL;
	Arc* ptr_arc;

	arbreACM = malloc(sizeof(*arbreACM));

	if (arbreACM == NULL)
		return NULL;

	arbreACM->sommet = &tab_sommet[num_depart];
	tab_sommet[num_depart].noeudArbreACM = arbreACM;


	while (!est_vide_file(fileACM)) {
		ptr_arc = (Arc *) defiler(&fileACM);
		ajouter_arbre(ptr_arc, tab_sommet);
	}

	return arbreACM;
}

File algo_fileACM(Sommet * tab_sommet, Arc * tab_arc,
		  int len_tab_sommet, int len_tab_arc,
		  int num_depart, float *cout)
{

	File fileACM = NULL;
	Liste C = NULL;

	Liste liste_sommet_atteint = NULL;

	Sommet d = tab_sommet[num_depart];

	/*
	   DEBUT ALGO PRIM
	 */

	Sommet *smt;
	for (smt = tab_sommet; smt < tab_sommet + len_tab_sommet; smt++) {
		smt->PPC = FLT_MAX;
		smt->arrive_par = NULL;
	}

	d.PPC = 0;
	d.arrive_par = NULL;

	C = ajout_tri(&d, C);
	liste_sommet_atteint = ajouter_queue(&d, liste_sommet_atteint, sizeof(Sommet));

	while (!est_vide_liste(C)) {

		Sommet sommet_ppc_min;
		Liste liste_sommet_adjacent = NULL;
		Liste liste_arc_sortant = NULL;
		Arc *a;
		Liste ll;

		/*on récupère le sommet de plus petit PPC et son coût */
		/*Comme la liste est triée, c'est le premier élément de C */
		sommet_ppc_min = *(Sommet *) C->val;

		/*supprimer j de C */
		C = supprimer_tete(C);

		/*si j n'est pas d */
		if (sommet_ppc_min.numero != d.numero) {
			*cout += sommet_ppc_min.PPC;
			fileACM = enfiler(fileACM, sommet_ppc_min.arrive_par, sizeof(Arc));
			liste_sommet_atteint = ajouter_queue(&sommet_ppc_min, liste_sommet_atteint, sizeof(Sommet));
		}

		/* on récupère les adjacents */
		for (a = tab_arc; a < tab_arc + len_tab_arc; a++) {
			if (a->sommet_depart == sommet_ppc_min.numero) {
				liste_sommet_adjacent = ajouter_queue(&tab_sommet[a->sommet_arrive], liste_sommet_adjacent, sizeof(Sommet));

				liste_arc_sortant = ajouter_queue(a, liste_arc_sortant, sizeof(Arc));
			}
		}

		sommet_ppc_min.voisins = liste_arc_sortant;

		for (ll = liste_arc_sortant; !est_vide_liste(ll); ll = ll->suiv) {

			a = (Arc *) ll->val;

			if ((tab_sommet[a->sommet_arrive]).PPC > a->cout) {

				tab_sommet[a->sommet_arrive].PPC = a->cout;
				tab_sommet[a->sommet_arrive].arrive_par = a;

				if (recherche_elt_liste(liste_sommet_atteint, &tab_sommet[a->sommet_arrive]) != 1) {
					if (recherche_elt_liste(C, &tab_sommet[a->sommet_arrive]) != 1) {
						C = ajout_tri(&tab_sommet[a->sommet_arrive], C);
					}
				}
			}
		}

	}

	printf("Cout de l'acm: %f\n", *cout);

	/* FIN ALGO PRIM */

	return fileACM;
}
