#include <stdlib.h>
#include <stdio.h>

#include "utils.h"
#include "sommet.h"
#include "arc.h"

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

	f = open_file(filename);

	if (fscanf(f, "%d %d", len_tab_sommet, len_tab_arc) != 2) {
		die("Format de fichier invalide");
	}

	printf("%d sommets et %d arretes\n", *len_tab_sommet, *len_tab_arc);

	*tab_sommet = malloc((*len_tab_sommet)*sizeof(Sommet));
	
	if (*tab_sommet==NULL) {
		die("Allocation impossible");
	}
	/*on se positionne au niveau de la ligne de commentaire et on l'affiche*/
	fseek(f, 1, SEEK_CUR);
	char s[256];
	fgets(s, 256, f);

	Sommet sommet;
		
	for (i=0; i<*len_tab_sommet; i++) {

		/*structure du fichier: numéro, x, y, nom*/
		/*attention le nom peut être composé...*/

		/*a voir: fgets + sscanf plutôt*/

		if (fscanf(f, "%d %f %f %[^\n]s", &sommet.numero, &sommet.coordonnee_x, &sommet.coordonnee_y, (sommet.nom)) != 4) {
			die("Format de fichier invalide\n");
		}
		(*tab_sommet)[i] = sommet;

/*		printf("%d/%d, %s \r",i+1, *len_tab_sommet, sommet.nom);
*/	} 

	/*idem, on se positionne au niveau de la ligne de commentaire et on l'affiche*/
	fseek(f, 1, SEEK_CUR);
	fgets(s, 256, f);

	Arc arc;
	Arc arc1;
	float cout;
	*tab_arc = malloc(2*(*len_tab_arc)*sizeof(Arc));

	*len_tab_arc *= 2;

	int arrive, depart;

	for (j=0; j < *len_tab_arc; j+=2) {

		/*structure du fichier: depart, arrive, coût*/
		if (fscanf(f, "%d %d %f", &depart, &arrive, &cout) != 3) {
			die("Format de fichier invalide");
		}
		arc.sommet_depart = depart;
		arc.sommet_arrive = arrive;
		arc.cout = cout;

		arc1.sommet_depart = arrive;
		arc1.sommet_arrive = depart;
		arc1.cout = cout;

		(*tab_arc)[j] = arc;
		(*tab_arc)[j+1] = arc1;

		printf("%d/%d %f\r", j+1, *len_tab_arc, arc.cout);

        fflush(stdout); 

   	}
}

int get_param_sommet(int param, int len_tab) {
	if ( param >= 0 && param < len_tab) {
		return param;
	}
	printf("Paramètre invalide: le nombre doit être inférieur à %d\n", len_tab);
	printf("0 sera utilisé\n");
	return 0;
}

