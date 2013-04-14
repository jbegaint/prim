#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "sommet.h"
#include "arc.h"

FILE* open_file(char* filename) 
{
  FILE *f;

  f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "Ouverture impossible\n");
    exit(EXIT_FAILURE);
  }
  return f;
}

void lecture(char* filename, Sommet* tab_sommet, Arc* tab_arc, int* len_tab_sommet, int* len_tab_arc)
{
	FILE *f;
	int i, j; // compteurs

	f = open_file(filename);

	int num_sommet, num_arrete;

	if (fscanf(f, "%d %d", &num_sommet, &num_arrete) != 2) {
		fprintf(stderr, "Format de fichier invalide\n");
		exit(EXIT_FAILURE);
	}

	*len_tab_sommet = num_sommet;
	*len_tab_arc = num_arrete; // a voir si faut pas un fois 2

	printf("%d sommets et %d arretes\n", num_sommet, num_arrete);

	tab_sommet = malloc(num_sommet*sizeof(Sommet));
	if (tab_sommet==NULL) {
		fprintf(stderr, "Allocation impossible\n");
		exit(EXIT_FAILURE);
	}
	// on se positionne au niveau de la ligne de commentaire et on l'affiche
	fseek(f, 1, SEEK_CUR);
	char s[256];
	fgets(s, 256, f);
	printf("%s", s);

	Sommet sommet;
	for (i=0; i<num_sommet; i++) {

		// structure du fichier: numéro, x, y, nom
		// attention le nom peut être composé...

		// a voir: fgets + sscanf plutôt

		if (fscanf(f, "%d %f %f %[^\n]s", &sommet.numero, &sommet.coordonnee_x, &sommet.coordonnee_y, (sommet.nom)) != 4) {
			
			fprintf(stderr, "Format de fichier invalide\n");
			printf("ligne: %d\n", i);
			
			exit(EXIT_FAILURE);
		}
		// printf("%d %f %f \n", sommet.numero, sommet.coordonnee_x,
		       // sommet.coordonnee_y);

		tab_sommet[i] = sommet;
		printf("%d/%d, %s \r",i+1, num_sommet, sommet.nom);
  		 fflush(stdout);
	} 
	printf("\n");


	// idem, on se positionne au niveau de la ligne de commentaire et on l'affiche
	fseek(f, 1, SEEK_CUR);
	fgets(s, 256, f);
	printf("%s", s);

	Arc arc;
	tab_arc = malloc(num_arrete*sizeof(Arc));

	int arrive, depart;
	for (j=0; j<num_arrete; j++) {

		// structure du fichier: depart, arrive, coût
		if (fscanf(f, "%d %d %f", &depart, &arrive, &arc.cout) != 3) {
			printf("%d\n", i+j);
			fprintf(stderr, "Format de fichier invalide\n");
			exit(EXIT_FAILURE);
		}
		arc.sommet_depart = &tab_sommet[depart];
		arc.sommet_arrive = &tab_sommet[arrive];

		tab_arc[j] = arc;

		// il faut encore récupérer les sommets à mettre dans arc
		printf("%d/%d %f\r", j+1, num_arrete, arc.cout);

        fflush(stdout);
	}
	printf("\n");

	fclose(f);
}
