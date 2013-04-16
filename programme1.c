#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "utils.h"

#include "sommet.h"
#include "arc.h"
#include "liste.h"
#include "file.h"

File algo_fileACM(Sommet* tab_sommet, Arc* tab_arc, int len_tab_sommet, int len_tab_arc) {

	File fileACM;
	Liste C;

	Sommet d = tab_sommet[0]; // Sommet de départ, à changer en paramètre

	/*
		DEBUT ALGO
	*/
	int s;
	for (s=0; s<len_tab_sommet; s++) {
		tab_sommet[s].PPC = FLT_MAX;
		tab_sommet[s].arrive_par = NULL;
	}

	d.PPC = 0;
	d.arrive_par = NULL;

	fileACM = creer_file();
	C = creer_liste();
	C = ajouter_queue(&d, C, sizeof(Sommet));

	int i=0; //compteur étapes

	while( !est_vide_liste(C) ) {

		// blabla itératif
		printf("--------------\n");
		printf("Étape: %d\n", i);
		printf("C: "); afficher_liste(C);
		printf("fileACM: "); afficher_file(fileACM);
		printf("--------------\n");
		getchar();
		i++;

		/* POUR TOUTES LES FONCTIONS QUI SUIVENT FAUDRA LES ECRIRE DANS UN FICHIER
		 POUR UN CODE PLUS EXPLICITE */

		// sommet j de C de plus petit PPC;
		Sommet sommet_ppc_min;
		// printf("Liste C: "); afficher_liste(C);

		Liste ss;
		// for (ss=C; !est_vide_liste(ss); ss=ss->suiv) {
		// 	printf("%d %f\n", (*(Sommet*)ss->val).numero, (*(Sommet*)ss->val).PPC);

		// 	if(len_liste(C) > 1) {
		// 				printf("Infos ARRIE : %s %d %d %f \n", 
		// 			(*(Sommet *) ss->val).nom,
		// 		(*((*(Sommet*) ss->val).arrive_par)).sommet_depart,
		// 		(*((*(Sommet*) ss->val).arrive_par)).sommet_arrive,
		// 		(*((*(Sommet*) ss->val).arrive_par)).cout);
		// 	}

		
		// }

		// on récupère le sommet de plus petit PPC et son coût
		sommet_ppc_min = trouver_min_liste_sommet(C);
		printf("Sommet le moins cher: %s %d\n", sommet_ppc_min.nom, sommet_ppc_min.numero);
		float min = sommet_ppc_min.PPC;


		// supprimer j de C;
		Liste p;

		// Grosse fonction dégeu qui semble fonctionner mais à changer
		if (len_liste(C) > 1) {
			printf("Liste C: "); afficher_liste(C);
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
			printf("Liste C: "); afficher_liste(C);
		}
		else {
			free(C);
		}

		int l;

		// si j n'est pas d;
		if ( sommet_ppc_min.numero != d.numero ) {
				// printf("Infos arc arrive par: %d %d %f \n", 
				// (*(sommet_ppc_min.arrive_par)).sommet_depart,
				// (*(sommet_ppc_min.arrive_par)).sommet_arrive,
				// (*(sommet_ppc_min.arrive_par)).cout);

			// printf("%f %d\n", (*(sommet_ppc_min.arrive_par)).cout, sommet_ppc_min.numero);
			fileACM = enfiler(fileACM, sommet_ppc_min.arrive_par, sizeof(Arc));
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
		printf("Adjacents: ");afficher_liste(liste_sommet_adjacent);

		for (p=liste_sommet_adjacent; !est_vide_liste(p); p=p->suiv) {
			// on récupère l'arc qui correspond
			for (l=0; l<len_tab_arc; l++) {
				if (tab_arc[l].sommet_depart == sommet_ppc_min.numero) {
					if (tab_arc[l].sommet_arrive == (*(Sommet*) p->val).numero) {
						// arc = tab_arc[l];
						break;
					}
				}
			}

			// min = c(j,k) <=> cout de l'arc j,k

			if ( (*(Sommet*) p->val).PPC > tab_arc[l].cout ) {
				(*(Sommet*) p->val).PPC = tab_arc[l].cout;

				/* il faut maintenant mettre l'arc j=>k dans arrive_par */

				(*(Sommet*) p->val).arrive_par = &tab_arc[l];

				if (recherche_elt_liste(C, (Sommet*) p->val) != 1) {
					C = ajouter_queue((Sommet*) p->val, C, sizeof(Sommet));
				}
				else {
					// printf("nothing for the moment \n");
				}

			}
		}
	}

	printf("C est vide, fin de l'algo\n");
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

	File fileACM;
	fileACM = algo_fileACM(tab_sommet, tab_arc, len_tab_sommet, len_tab_arc);	

	printf("fileACM: \n");
	afficher_file(fileACM);

	return 0;
}