#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "sommet.h"
#include "arc.h"
#include "liste.h"

#include "utils.h"

int main(int argc, char *argv[])
{
	FILE *f;
	int i;
	int j;
	
	if (argc < 2) {
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	f = open_file(argv[1]);

	int num_sommet;
	int num_arrete;

	// Sommet tab_arc[num_arrete];

	if (fscanf(f, "%d %d", &num_sommet, &num_arrete) != 2) {
		fprintf(stderr, "Format de fichier invalide\n");
		exit(EXIT_FAILURE);
	}

	printf("%d sommets et %d arretes\n", num_sommet, num_arrete);

	Sommet* tab_sommet;
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
	// Liste liste_sommet;
	// liste_sommet = creer_liste();

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
		// liste_sommet = ajouter_queue(&sommet, liste_sommet, sizeof(Sommet));
		printf("%d/%d, %s \r",i+1, num_sommet,sommet.nom);
  		 fflush(stdout);
	} 
	printf("\n");


	// idem, on se positionne au niveau de la ligne de commentaire et on l'affiche
	fseek(f, 1, SEEK_CUR);
	fgets(s, 256, f);
	printf("%s", s);

	Arc arc;
	Arc* tab_arc;
	tab_arc = malloc(num_arrete*sizeof(Arc));

	int arrive, depart;
	for (j=0; j<num_arrete; j++) {
		// structure du fichier: depart, arrivee, coût
		if (fscanf(f, "%d %d %f", &arrive, &depart, &arc.cout) != 3) {
			if (fscanf(f, "%d %d %f", &arrive, &depart, &arc.cout) == EOF) {
				printf("\n");
				printf("EOF\n");
				break;
			}else {
			printf("%d\n", i+j);
			fprintf(stderr, "Format de fichier invalide\n");
			exit(EXIT_FAILURE);
		}
		}
		// printf("%d %d %f \n", arrivee, depart, arc.cout);

		tab_arc[j] = arc;

		// il faut encore récupérer les sommets à mettre dans arc

		printf("%d/%d %f\r", j+1, num_arrete, arc.cout);
        fflush(stdout);

	}
	printf("\n");

	fclose(f);

	return 0;
}
