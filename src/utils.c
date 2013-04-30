#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "sommet.h"
#include "arc.h"

Arc get_arc(int depart, int arrive, float cout)
{
	Arc arc;
	
	arc.sommet_depart = depart;
	arc.sommet_arrive = arrive;
	arc.cout = cout;

	return arc;
}

void die(char *c)
{
	fprintf(stderr, "%s \n", c);
	exit(EXIT_FAILURE);
}

FILE* open_file(char* filename) 
{
  FILE *f;

  f = fopen(filename, "r");
  if (f == NULL) {
    die("Ouverture impossible");
  }
  return f;
}

void lecture(char* filename, Sommet** tab_sommet, Arc** tab_arc, int* len_tab_sommet, int* len_tab_arc)
{
	FILE *f;
	int i, j; /* compteurs */
	char s[256];
	Sommet sommet;
	int arrive, depart;
	float cout;

	f = open_file(filename);

	// if (fscanf(f, "%d %d", len_tab_sommet, len_tab_arc) != 2) {
	// 	die("Format de fichier invalide");
	// }

	char line[256];

	if (fgets(line, sizeof(line), f) != 0) {
		if (sscanf(line, "%d %d", len_tab_sommet, len_tab_arc) != 2) {
			die("Format de fichier invalide");
		}
	}

	printf("%d sommets et %d arretes\n", *len_tab_sommet, *len_tab_arc);

	*tab_sommet = malloc((*len_tab_sommet)*sizeof(Sommet));
	
	if (*tab_sommet==NULL) {
		die("Allocation impossible");
	}
	
	fgets(s, 256, f);

	printf("Sommets:\n");
	for (i=0; i<*len_tab_sommet; i++) {

		/*structure du fichier: numéro, x, y, nom*/
		/*attention le nom peut être composé...*/

		/*a voir: fgets + sscanf plutôt*/

		// if (fscanf(f, "%d %f %f %[^\n]s", &sommet.numero, &sommet.coordonnee_x, &sommet.coordonnee_y, (sommet.nom)) != 4) {
		// 	die("Format de fichier invalide\n");
		// }

		if (fgets(line, sizeof(line), f) != 0) {
			if (sscanf(line, "%d %f %f %[^\n]s", &sommet.numero, &sommet.coordonnee_x, &sommet.coordonnee_y, (sommet.nom)) != 4) {
				die("Format de fichier invalide");
		}

	}
		(*tab_sommet)[i] = sommet;

		printf("%d/%d\r",i+1, *len_tab_sommet);
		fflush(stdout);

	} 
	printf("\n");

	fgets(s, 256, f);


	*tab_arc = malloc(2*(*len_tab_arc)*sizeof(Arc));
	*len_tab_arc *= 2;


	printf("Arcs:\n");
	for (j=0; j < *len_tab_arc; j+=2) {

		/*structure du fichier: depart, arrive, coût*/
		if (fscanf(f, "%d %d %f", &depart, &arrive, &cout) != 3) {
			die("Format de fichier invalide");
		}

		(*tab_arc)[j] = get_arc(depart, arrive, cout);
		(*tab_arc)[j+1] = get_arc(arrive, depart, cout);

		printf("%d/%d\r", j+2, *len_tab_arc);
        fflush(stdout); 

   	}
	printf("\n");

}

int get_param_sommet(int param, int len_tab) {
	if ( param >= 0 && param < len_tab) {
		return param;
	}
	printf("Paramètre invalide: le nombre doit être inférieur à %d\n", len_tab);
	printf("0 sera utilisé\n");
	return 0;
}

