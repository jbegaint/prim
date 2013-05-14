#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <time.h>

#include "utils.h"

#include "sommet.h"
#include "arc.h"
#include "liste.h"
#include "file.h"

#include "algo.h"

int main(int argc, char** argv) {

	if (argc < 2) {
		fprintf(stderr, "Usage: %s fichier\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	Sommet* tab_sommet;
	Arc* tab_arc;

	int len_tab_sommet, len_tab_arc;

	lecture(argv[1], &tab_sommet, &tab_arc, &len_tab_sommet, &len_tab_arc);

	int num_depart;
	if (argc > 2)
		num_depart = atoi(argv[2]);
	else {
		printf("Entrez le numéro du sommet de départ: [0,%d]\n", len_tab_sommet);
		scanf("%d", &num_depart);
	}

	num_depart = get_param_sommet(num_depart, len_tab_sommet);
	printf("Départ: %s\n", tab_sommet[num_depart].nom);


	printf("----------------\n");
	printf("| Algo FileACM |\n");
	printf("----------------\n");
	File fileACM;
	float cout = 0;
	fileACM = algo_fileACM(tab_sommet, tab_arc, len_tab_sommet, len_tab_arc, num_depart, &cout);	
	printf("FileACM: ");
	afficher_file(fileACM);

	Arbre arbreACM;
	arbreACM = algo_arbreACM(fileACM, tab_sommet, num_depart);


	printf("----------------\n");
	printf("| Algo ArbreACM |\n");
	printf("----------------\n");
	printf("arbreACM (recursif): ");
	printf("[ ");
	afficheRSB(arbreACM);
	printf("]\n");

	printf("arbreACM (iteratif): ");

	Liste liste_sommets_arbre;
	liste_sommets_arbre = afficheRSB_iteratif(arbreACM);
	afficher_liste(liste_sommets_arbre);

	/* Faux pour le moment */
	Liste l;
	Sommet s1, s2;
	Arc* ptr_arc;
	float cc = 0;

	for (l=liste_sommets_arbre; !est_vide_liste(l) && !est_vide_liste(l->suiv); l=l->suiv) {
		s1 = *(Sommet *) l->val;
		s2 = *(Sommet *) l->suiv->val;
		for (ptr_arc = tab_arc; ptr_arc < tab_arc + len_tab_arc; ptr_arc++) {
			if ( (ptr_arc->sommet_depart == s1.numero) && (ptr_arc->sommet_arrive == s2.numero) ) {
				cc += ptr_arc->cout;
				continue;
			}
		}
	}
	printf("Coût chemin arbre : %f\n", cc);

	return 0;
}
