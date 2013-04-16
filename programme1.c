#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "utils.h"

#include "sommet.h"
#include "arc.h"
#include "liste.h"
#include "file.h"

File algo_fileACM(Sommet* tab_sommet, Arc* tab_arc, int len_tab_sommet, int len_tab_arc, int num_depart) {

	File fileACM;
	Liste C;

	float cout = 0;

	Liste liste_sommet_atteint;
	liste_sommet_atteint = creer_liste();

	// Sommet d = tab_sommet[num_depart]; // Sommet de départ, à changer en paramètre

	/*
		DEBUT ALGO
	*/

	int s;
	for (s=0; s<len_tab_sommet; s++) {
		tab_sommet[s].PPC = FLT_MAX;
		tab_sommet[s].arrive_par = NULL;
	}
	
	tab_sommet[num_depart].PPC = 0;
	tab_sommet[num_depart].arrive_par = NULL;

	fileACM = creer_file();
	C = creer_liste();
	C = ajouter_queue(&tab_sommet[num_depart], C, sizeof(Sommet));

	liste_sommet_atteint = ajouter_queue(&tab_sommet[num_depart], liste_sommet_atteint, sizeof(Sommet));

	int i=0; //compteur étapes

	while( !est_vide_liste(C) ) {

		// blabla itératif
		// très moche

		// printf("Étape: %d\n", i);
		// printf("C: "); afficher_liste(C);
		// printf("D: "); afficher_liste(liste_sommet_atteint);
		// printf("fileACM: "); afficher_file(fileACM);
		// printf("--------------\n");
		// getchar();

		i++;

		/* POUR TOUTES LES FONCTIONS QUI SUIVENT FAUDRA LES ECRIRE DANS UN FICHIER
		 POUR UN CODE PLUS EXPLICITE */

		// sommet j de C de plus petit PPC;
		Sommet sommet_ppc_min;

		// on récupère le sommet de plus petit PPC et son coût
		sommet_ppc_min = trouver_min_liste_sommet(C);

		float min = sommet_ppc_min.PPC;


		// supprimer j de C;
		Liste p;

		// Grosse fonction dégeu qui semble fonctionner mais à changer
		if (len_liste(C) > 1) {
			// cas premier élément de C = sommet_ppc_min
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
			C = creer_liste();
		}

		int l;

		// si j n'est pas d;
		if ( sommet_ppc_min.numero != tab_sommet[num_depart].numero ) {
			cout += sommet_ppc_min.PPC;
			fileACM = enfiler(fileACM, sommet_ppc_min.arrive_par, sizeof(Arc));
			liste_sommet_atteint = ajouter_queue(&sommet_ppc_min, liste_sommet_atteint, sizeof(Sommet));
		}

		// il faut maintenant récupérer les adjacents à j

		Liste liste_sommet_adjacent;
		Arc* a;

		liste_sommet_adjacent = creer_liste();

		for (a=tab_arc; a < tab_arc + len_tab_arc; a++) {
			// A voir pour la comparaison
			if ( (*a).sommet_depart == sommet_ppc_min.numero ) {
				liste_sommet_adjacent = ajouter_queue(&tab_sommet[(*a).sommet_arrive], liste_sommet_adjacent, sizeof(Sommet));
			}
			if ( (*a).sommet_arrive == sommet_ppc_min.numero ) {
				liste_sommet_adjacent = ajouter_queue(&tab_sommet[(*a).sommet_depart], liste_sommet_adjacent, sizeof(Sommet));
			}
		}

		// Arc arc;

		sommet_ppc_min.voisins = liste_sommet_adjacent;
		// printf("Adjacents: "); afficher_liste(liste_sommet_adjacent);

		for (p=liste_sommet_adjacent; !est_vide_liste(p); p=p->suiv) {

			for (l=0; l<len_tab_arc; l++) {
				if (tab_arc[l].sommet_depart == sommet_ppc_min.numero) {
					if (tab_arc[l].sommet_arrive == (*(Sommet*) p->val).numero) {
						break;
					}
				}
				if (tab_arc[l].sommet_arrive == sommet_ppc_min.numero) {
					if (tab_arc[l].sommet_depart == (*(Sommet*) p->val).numero) {
						break;
					}
				}
			}

			// min = c(j,k) <=> cout de l'arc j,k
			if ( (*(Sommet*) p->val).PPC > tab_arc[l].cout ) {

				(*(Sommet*) p->val).PPC = tab_arc[l].cout;

				/* il faut maintenant mettre l'arc j=>k dans arrive_par */

				(*(Sommet*) p->val).arrive_par = &tab_arc[l];
				
				if (recherche_elt_liste(liste_sommet_atteint, (Sommet*) p->val) != 1) {
					if (recherche_elt_liste(C, (Sommet*) p->val) != 1) {
						C = ajouter_queue((Sommet*) p->val, C, sizeof(Sommet));
					}
					else {
					// printf("nothing for the moment \n");
					}
				}			

			}
		}
	}

	printf("Cout de l'acm: %f\n", cout);

	return fileACM;
	// FIN ALGO
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

	lecture(argv[1], &tab_sommet, &tab_arc, &len_tab_sommet, &len_tab_arc);

	printf("##############\n");
	printf(" Algo FileACM \n");
	printf("##############\n");


	// penser à générer une erreur si num_depart pas dans le bon intervalle
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