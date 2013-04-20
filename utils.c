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

	int num_sommet, num_arrete;

	if (fscanf(f, "%d %d", &num_sommet, &num_arrete) != 2) {
		die("Format de fichier invalide");
	}

	*len_tab_sommet = num_sommet;
	*len_tab_arc = num_arrete; /* a voir si faut pas un *2 */

	printf("%d sommets et %d arretes\n", num_sommet, num_arrete);

	*tab_sommet = malloc(num_sommet*sizeof(Sommet));
	
	if (*tab_sommet==NULL) {
		die("Allocation impossible");
	}
	/*on se positionne au niveau de la ligne de commentaire et on l'affiche*/
	fseek(f, 1, SEEK_CUR);
	char s[256];
	fgets(s, 256, f);

	Sommet sommet;
		
	for (i=0; i<num_sommet; i++) {

		/*structure du fichier: numéro, x, y, nom*/
		/*attention le nom peut être composé...*/

		/*a voir: fgets + sscanf plutôt*/

		if (fscanf(f, "%d %f %f %[^\n]s", &sommet.numero, &sommet.coordonnee_x, &sommet.coordonnee_y, (sommet.nom)) != 4) {
			die("Format de fichier invalide\n");
		}
		(*tab_sommet)[i] = sommet;

		printf("%d/%d, %s \r",i+1, num_sommet, sommet.nom);
		
		if ( (i/num_sommet)*100 % 10 == 0)
			printf("%d\n", i);	

	} 

	/*idem, on se positionne au niveau de la ligne de commentaire et on l'affiche*/
	fseek(f, 1, SEEK_CUR);
	fgets(s, 256, f);

	Arc arc;
	*tab_arc = malloc(2*num_arrete*sizeof(Arc));

	int arrive, depart;

	for (j=0; j<num_arrete; j++) {

		/*structure du fichier: depart, arrive, coût*/
		if (fscanf(f, "%d %d %f", &depart, &arrive, &arc.cout) != 3) {
			die("Format de fichier invalide");
		}
		arc.sommet_depart = depart;
		arc.sommet_arrive = arrive;

		(*tab_arc)[j] = arc;

		printf("%d/%d %f\r", j+1, num_arrete, arc.cout);

        fflush(stdout); 

   	}
}

int get_param_sommet(int param, int len_tab) {
	if ( param > 0 && param < len_tab) {
		return param;
	}
	printf("Paramètre invalide: le nombre doit être inférieur à %d\n", len_tab);
	printf("0 sera utilisé\n");
	return 0;
}

