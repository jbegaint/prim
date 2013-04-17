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

void lecture(char* filename, Sommet** tab_sommet, Arc** tab_arc, int* len_tab_sommet, int* len_tab_arc)
{
	FILE *f;
	int i, j; /* compteurs */

	f = open_file(filename);

	int num_sommet, num_arrete;

	if (fscanf(f, "%d %d", &num_sommet, &num_arrete) != 2) {
		fprintf(stderr, "Format de fichier invalide\n");
		exit(EXIT_FAILURE);
	}

	*len_tab_sommet = num_sommet;
	*len_tab_arc = num_arrete; /* a voir si faut pas un *2 */

	printf("%d sommets et %d arretes\n", num_sommet, num_arrete);

	*tab_sommet = malloc(num_sommet*sizeof(Sommet));
	
	if (*tab_sommet==NULL) {
		fprintf(stderr, "Allocation impossible\n");
		exit(EXIT_FAILURE);
	}
	/*on se positionne au niveau de la ligne de commentaire et on l'affiche*/
	fseek(f, 1, SEEK_CUR);
	char s[256];
	fgets(s, 256, f);

	Sommet sommet;
		
	int a = 0;
	int b = 0;

	for (i=0; i<num_sommet; i++) {

		/*structure du fichier: numéro, x, y, nom*/
		/*attention le nom peut être composé...*/

		/*a voir: fgets + sscanf plutôt*/

		if (fscanf(f, "%d %f %f %[^\n]s", &sommet.numero, &sommet.coordonnee_x, &sommet.coordonnee_y, (sommet.nom)) != 4) {
			

			fprintf(stderr, "Format de fichier invalide\n");
			printf("ligne: %d\n", i);
			
			exit(EXIT_FAILURE);
		}
		(*tab_sommet)[i] = sommet;

		/*printf("%d %f %f \n", sommet.numero, sommet.coordonnee_x, sommet.coordonnee_y);*/
		/*printf("%d/%d, %s \r",i+1, num_sommet, sommet.nom);*/
 	 	/*fflush(stdout);*/
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
			printf("%d\n", i+j);
			fprintf(stderr, "Format de fichier invalide\n");
			exit(EXIT_FAILURE);
		}
		arc.sommet_depart = depart;
		arc.sommet_arrive = arrive;

		(*tab_arc)[j] = arc;

		/*il faut encore récupérer les sommets à mettre dans arc*/
		/*printf("%d/%d %f\r", j+1, num_arrete, arc.cout);

        fflush(stdout);*/ 

   	}
}
