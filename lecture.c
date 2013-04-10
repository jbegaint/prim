#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

	if (fscanf(f, "%d %d", &num_sommet, &num_arrete) != 2) {
		fprintf(stderr, "Format de fichier invalide\n");
		exit(EXIT_FAILURE);
	}

	printf("%d sommets et %d arretes\n", num_sommet, num_arrete);

	// on se positionne au niveau de la ligne de commentaire et on l'affiche
	fseek(f, 1, SEEK_CUR);
	char s[256];
	fgets(s, 256, f);
	printf("%s", s);

	Sommet sommet;
	Liste liste_sommet;
	liste_sommet = creer_liste();

	for (i=0; i<num_sommet; i++) {

		//structure du fichier: numéro, x, y, nom

		if (fscanf(f, "%d %f %f %s", &sommet.numero, &sommet.coordonnee_x, &sommet.coordonnee_y, (sommet.nom)) != 4) {
			
			fprintf(stderr, "Format de fichier invalide\n");
			printf("ligne: %d\n", i);
			
			exit(EXIT_FAILURE);
		}
		// printf("%d %f %f \n", sommet.numero, sommet.coordonnee_x,
		       // sommet.coordonnee_y);

		liste_sommet = ajouter_queue(&sommet, liste_sommet, sizeof(Sommet));
		printf("%d/%d, %s \r",i+1, num_sommet,sommet.nom);
  		 fflush(stdout);
	} 
	printf("\n");


	// idem, on se positionne au niveau de la ligne de commentaire et on l'affiche
	fseek(f, 1, SEEK_CUR);
	fgets(s, 256, f);
	printf("%s", s);

	Arc arc;
	Liste liste_arc;
	liste_arc = creer_liste();

	int arrive, depart;
	for (j=0; j<num_arrete; j++) {
		// structure du fichier: depart, arrivee, coût
		if (fscanf(f, "%d %d %f", &arrive, &depart, &arc.cout) != 3) {
			
			fprintf(stderr, "Format de fichier invalide\n");
			
			exit(EXIT_FAILURE);
		}
		// printf("%d %d %f \n", arrivee, depart, arc.cout);

		liste_arc = ajouter_queue(&arc, liste_arc, sizeof(Arc));

		// il faut encore récupérer les sommets à mettre dans arc

		printf("%d/%d\r", j+1, num_arrete);
        fflush(stdout);

	}
	printf("\n");

	fclose(f);

	return 0;
}
