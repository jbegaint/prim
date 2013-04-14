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
	fileACM = creer_file();

	Sommet d = tab_sommet[0]; // Sommet de départ
	// a changer en paramètre
	d.PPC = 0;
	d.arrive_par = NULL;

	// DEBUT ALGO

	int s;
	for (s=0; s<len_tab_sommet; s++) {
		tab_sommet[s].PPC = FLT_MAX;
		tab_sommet[s].arrive_par = NULL;
	}

	Liste C;
	C = creer_liste();
	C = ajouter_queue(&d, C, sizeof(Sommet));

	int i=0;

	while( !est_vide_liste(C) ) {

		printf("C: "); afficher_liste(C);
		printf("fileACM: "); afficher_file(fileACM);

		getchar();

		// printf("Compteur algo: %d\n", i);
		i++;

		/* POUR TOUTES LES FONCTIONS QUI SUIVENT FAUDRA LES ECRIRE DANS UN FICHIER
		 POUR UN CODE PLUS EXPLICITE */

		// sommet j de C de plus petit PPC;
		Sommet sommet_ppc_min;
		sommet_ppc_min = trouver_min_liste_sommet(C);
		float min = sommet_ppc_min.PPC;
		// printf("%f\n", min);

		// on récupère le sommet de plus petit PPC et son coût

		// supprimer j de C;
		if ( (*(Sommet*) C->val).PPC == min) {
			// cas si j premier élément de C
			C = C->suiv;
		} 
		else {
			Liste p;
			for (p=C; !est_vide_liste(p); p=p->suiv) {
				if ( (*(Sommet*) p->suiv->val).PPC == min ) {
					// on a trouvé j
					// il faut maintenant le supprimer de la liste

					// cas général
					// a voir si bug dans cas particuliers
					Liste tmp;
					tmp = p->suiv->suiv;
					free_liste(p->suiv);
					p->suiv = tmp;
				}
			}
		}

		// si j n'est pas d;
		if ( sommet_ppc_min.numero != d.numero ) {
			printf("Infos arc arrive par: %d %d %f \n", 
				(*(sommet_ppc_min.arrive_par)).sommet_depart,
				(*(sommet_ppc_min.arrive_par)).sommet_arrive,
				(*(sommet_ppc_min.arrive_par)).cout);

			// fileACM = enfiler(fileACM, &(sommet_ppc_min.arrive_par), sizeof(Arc));
			fileACM = enfiler(fileACM, sommet_ppc_min.arrive_par, sizeof(Arc));
		}

		// il faut maintenant récupérer les adjacents à j

		Liste liste_sommet_adjacent;
		Liste p;
		Arc* a;

		liste_sommet_adjacent = creer_liste();

		for (a=tab_arc; a < tab_arc + len_tab_arc; a++) {
			// A voir pour la comparaison
			if ( (*a).sommet_depart == sommet_ppc_min.numero ) {
				liste_sommet_adjacent = ajouter_queue(&tab_sommet[(*a).sommet_arrive], liste_sommet_adjacent, sizeof(Sommet));
			}
			else if ( (*a).sommet_arrive == sommet_ppc_min.numero ) {
				liste_sommet_adjacent = ajouter_queue(&tab_sommet[(*a).sommet_depart], liste_sommet_adjacent, sizeof(Sommet));
			}
		}


		sommet_ppc_min.voisins = liste_sommet_adjacent;

		for (p=liste_sommet_adjacent; !est_vide_liste(p); p=p->suiv) {
			// printf("%d\n", (*(Sommet*)p->val).numero);
			if ( (*(Sommet*) p->val).PPC > min ) {

				(*(Sommet*) p->val).PPC = min;

				/* il faut maintenant mettre l'arc j=>k dans arrive_par */

				Arc arc;
				arc.cout = (*(Sommet*) p->val).PPC;
				printf("COUTCOUT %f %f\n", arc.cout, min);
				arc.sommet_depart = sommet_ppc_min.numero;
				arc.sommet_arrive = (*(Sommet*) p->val).numero;

				(*(Sommet*) p->val).arrive_par = &arc;

				if (recherche_elt_liste(C, (Sommet*) p->val) != 1) {
					// printf("C ajout\n");
					C = ajouter_queue((Sommet*) p->val, C, sizeof(Sommet));
				}
				else {
					// printf("nothing for the moment \n");
					// printf("");
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

	tab_sommet = malloc(6*sizeof(Sommet));
	tab_arc = malloc(7*sizeof(Arc));

	int len_tab_sommet, len_tab_arc;

	lecture(argv[1], &tab_sommet, &tab_arc, &len_tab_sommet, &len_tab_arc);

	printf("-------------\n");
	printf("Algo File\n");
	printf("-------------\n");

	File fileACM;
	fileACM = algo_fileACM(tab_sommet, tab_arc, len_tab_sommet, len_tab_arc);	

	printf("fileACM: \n");
	afficher_file(fileACM);

	return 0;
}