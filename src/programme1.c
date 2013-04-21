#include <stdio.h>
#include <stdlib.h>
#include <float.h>

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

	printf("----------------\n");
	printf("| Algo FileACM |\n");
	printf("----------------\n");

	int num_depart;
	if (argc > 2)
		num_depart = atoi(argv[2]);
	else {
		printf("Entrez le numéro du sommet de départ: [0,%d]\n", len_tab_sommet);
		scanf("%d", &num_depart);
	}

	num_depart =  get_param_sommet(num_depart, len_tab_sommet);

	File fileACM;
	float cout;
	fileACM = algo_fileACM(tab_sommet, tab_arc, len_tab_sommet, len_tab_arc, num_depart, &cout);	

	printf("Résultat, fileACM: ");
	afficher_file(fileACM);

	return 0;
}

