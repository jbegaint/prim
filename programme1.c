#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "utils.h"

#include "sommet.h"
#include "arc.h"
#include "liste.h"
#include "file.h"

File algo_fileACM(Sommet* tab_sommet, Arc* tab_arc, int len_tab_sommet, int len_tab_arc, int num_depart) {

	File fileACM = NULL;
	Liste C = NULL;

	float cout = 0;

	Liste liste_sommet_atteint = NULL;

	Sommet d = tab_sommet[num_depart];

	/*
		DEBUT ALGO
	*/

	Sommet* smt;
	for (smt=tab_sommet; smt < tab_sommet+len_tab_sommet; smt++) {
		(*smt).PPC = FLT_MAX;
		(*smt).arrive_par = NULL;
	}
	
	d.PPC = 0;
	d.arrive_par = NULL;

	C = ajouter_queue(&d, C, sizeof(Sommet));
	liste_sommet_atteint = ajouter_queue(&d, liste_sommet_atteint, sizeof(Sommet));

	/*int i=0; compteur étapes*/

	while( !est_vide_liste(C) ) {

		/* blabla itératif

		 printf("Étape: %d\n", i);
		 printf("C: "); afficher_liste(C);
		 printf("D: "); afficher_liste(liste_sommet_atteint);
		 printf("fileACM: "); afficher_file(fileACM);
		 printf("--------------\n");
		 getchar();
		 i++;*/

		/*sommet de C de plus petit PPC;*/
		Sommet sommet_ppc_min;

		/*on récupère le sommet de plus petit PPC et son coût*/
		sommet_ppc_min = trouver_min_liste_sommet(C);

		/*supprimer j de C*/
		Liste p;

		/*Grosse fonction dégeu qui semble fonctionner mais à changer*/
		if (len_liste(C) > 1) {
			/*cas premier élément de C = sommet_ppc_min*/
			if ( (*(Sommet*)C->val).numero == sommet_ppc_min.numero ) {
				C = C->suiv;
			}

			else {
				for (p=C; !est_vide_liste(p->suiv); p=p->suiv) {
					if ( (*(Sommet*) p->suiv->val).numero == sommet_ppc_min.numero ) {
						Liste tmp;
						tmp = p->suiv;

						if (est_vide_liste(p->suiv->suiv)) {
							p->suiv=NULL;
							break;
						} else {
							p->suiv = p->suiv->suiv; 
						}
						free(tmp);
					}
				}
			}
		}
		else {
			C = NULL;
		}

		/*si j n'est pas d*/
		if ( sommet_ppc_min.numero != d.numero ) {
			cout += sommet_ppc_min.PPC;
			fileACM = enfiler(fileACM, sommet_ppc_min.arrive_par, sizeof(Arc));
			liste_sommet_atteint = ajouter_queue(&sommet_ppc_min, liste_sommet_atteint, sizeof(Sommet));
		}

		/* il faut maintenant récupérer les adjacents à j*/

		Liste liste_sommet_adjacent = NULL;
		Arc* a;

		Liste liste_arc_sortant = NULL;
		Liste ll;

		for (a=tab_arc; a < tab_arc + len_tab_arc; a++) {
			/* A voir pour la comparaison */
			if ( (*a).sommet_depart == sommet_ppc_min.numero ) {
				liste_sommet_adjacent = ajouter_queue(&tab_sommet[(*a).sommet_arrive], liste_sommet_adjacent, sizeof(Sommet));
			
				liste_arc_sortant = ajouter_queue(a, liste_arc_sortant, sizeof(Arc));
			}
			if ( (*a).sommet_arrive == sommet_ppc_min.numero ) {
				liste_sommet_adjacent = ajouter_queue(&tab_sommet[(*a).sommet_depart], liste_sommet_adjacent, sizeof(Sommet));
				
				liste_arc_sortant = ajouter_queue(a, liste_arc_sortant, sizeof(Arc));
			}
		}
		/*sommet_ppc_min.voisins = liste_sommet_adjacent;*/
		sommet_ppc_min.voisins = liste_arc_sortant;

		for (ll=liste_arc_sortant; !est_vide_liste(ll); ll=ll->suiv) {

			a = (Arc *) ll->val;

			if ( (tab_sommet[(*a).sommet_arrive]).PPC > (*a).cout ) {

				tab_sommet[(*a).sommet_arrive].PPC = (*a).cout;
				tab_sommet[(*a).sommet_arrive].arrive_par = a;

				if (recherche_elt_liste(liste_sommet_atteint, &tab_sommet[(*a).sommet_arrive]) != 1) {
					if (recherche_elt_liste(C, &tab_sommet[(*a).sommet_arrive]) != 1) {
						C = ajouter_queue(&tab_sommet[(*a).sommet_arrive], C, sizeof(Sommet));
					}
					else {
					/* printf("nothing for the moment \n");*/
					}
				}	
			}

			if ( (tab_sommet[(*a).sommet_depart]).PPC > (*a).cout ) {

				tab_sommet[(*a).sommet_depart].PPC = (*a).cout;
				tab_sommet[(*a).sommet_depart].arrive_par = a;

				if (recherche_elt_liste(liste_sommet_atteint, &tab_sommet[(*a).sommet_depart]) != 1) {
					if (recherche_elt_liste(C, &tab_sommet[(*a).sommet_depart]) != 1) {
						C = ajouter_queue(&tab_sommet[(*a).sommet_depart], C, sizeof(Sommet));
					}
					else {
					/* printf("nothing for the moment \n");*/
					}
				}	
			}
		}

	}

	printf("Cout de l'acm: %f\n", cout);

	return fileACM;
	/*FIN ALGO*/
}

int main(int argc, char* argv[]) {

	if (argc < 2) {
		fprintf(stderr, "Usage: %s fichier\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	Sommet* tab_sommet;
	Arc* tab_arc;

	int len_tab_sommet, len_tab_arc;

	printf("Fichier: ");

	int k=0;
	for (k=0; k<len_tab_sommet; k++) {
		printf("%s", tab_sommet[k].nom);
	}

	lecture(argv[1], &tab_sommet, &tab_arc, &len_tab_sommet, &len_tab_arc);

	printf("----------------\n");
	printf("| Algo FileACM |\n");
	printf("----------------\n");


/*	penser à générer une erreur si num_depart pas dans le bon intervalle
*/	
	int num_depart;
	if (argc > 2)
		num_depart = atoi(argv[2]);
	else {
		printf("Entrez le numéro du sommet de départ: [0,%d]\n", len_tab_sommet);
		scanf("%d", &num_depart);
	}

	File fileACM;
	fileACM = algo_fileACM(tab_sommet, tab_arc, len_tab_sommet, len_tab_arc, num_depart);	

	printf("Résultat, fileACM: ");
	afficher_file(fileACM);

	return 0;
}

/*// A faire 
// relié les points
//Afficher nom sommet
//Afficher le cout*/
