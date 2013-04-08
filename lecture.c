#include <stdio.h>
#include <stdlib.h>

#include "sommet.h"
#include "arc.h"
#include "liste.h"

int main(int argc, char *argv[])
{
	FILE *f;
	int i=0;
	int j=0;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	f = fopen(argv[1], "r");
	if (f == NULL) {
		fprintf(stderr, "Ouverture impossible\n");
		exit(EXIT_FAILURE);
	}

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
	ListeSommet liste_sommet;
	liste_sommet = (ListeSommet) creer_liste();

	//structure du fichier: numéro, x, y, nom
	do {
		if (fscanf
		    (f, "%d %f %f %s", &sommet.numero,
		     &sommet.coordonnee_x, &sommet.coordonnee_y,
		     &sommet.nom) != 4) {
			fprintf(stderr, "Format de fichier invalide\n");
			printf("ligne: %d\n", i);
			exit(EXIT_FAILURE);
		}
		// printf("%d %f %f \n", sommet.numero, sommet.coordonnee_x,
		       // sommet.coordonnee_y);

		liste_sommet = (ListeSommet) ajouter_queue(&sommet, (Liste) liste_sommet, sizeof(Sommet));
		printf("%d/%d\r", i+1, num_sommet);
        fflush(stdout);
		i++;
		// printf("%s\n", sommet.nom); // seg fault, va savoir pourquoi...

	} while (i < num_sommet);
		printf("\n");

	// idem, on se positionne au niveau de la ligne de commentaire et on l'affiche
	fseek(f, 1, SEEK_CUR);
	fgets(s, 256, f);
	printf("%s", s);

	Arc arc;
	ListeArc liste_arc;
	liste_arc = (ListeArc) creer_liste();

	int arrive, depart;
	// structure du fichier: depart, arrivee, coût
	do {
		if (fscanf(f, "%d %d %f", &arrive, &depart, &arc.cout) !=
		    3) {
			fprintf(stderr, "Format de fichier invalide\n");
			exit(EXIT_FAILURE);
		}
		// printf("%d %d %f \n", arrivee, depart, arc.cout);

		liste_arc = (ListeArc) ajouter_queue(&arc, (Liste) liste_arc, sizeof(Arc));

		// il faut encore récupérer les sommets à mettre dans arc

		printf("%d/%d\r", j+1, num_arrete);
        fflush(stdout);
		j++;

	} while (j < num_arrete);
	printf("\n");

	fclose(f);

	return 0;
}