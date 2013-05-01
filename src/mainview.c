#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include <stdlib.h>
#include <stdio.h>

#include "view.h"
#include "algo.h"

#include "sommet.h"
#include "arc.h"
#include "liste.h"
#include "file.h"

#include "utils.h"

#include "SDL_draw.h"


int main(int argc, char **argv)
{
	Sommet *tab_sommet;
	Arc *tab_arc;
	int len_tab_arc, len_tab_sommet;

	File fileACM;

	float cout_chemin;
	int num_depart;
	float x1, y1, x2, y2;
	File p;


	if (argc < 2) {
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	lecture(argv[1], &tab_sommet, &tab_arc, &len_tab_sommet,
		&len_tab_arc);

	init_SDL();

	SDL_Surface *ecran = NULL;	/*Defini un pointeur vers l'écran */

	ecran = init_ecran(ecran);

	ecran = edit_point(ecran, tab_sommet, len_tab_sommet);

	if (argc > 2) {
		num_depart = atoi(argv[2]);
	} else {
		printf("Entrez le numéro du sommet de départ: [0,%d]\n",
		       len_tab_sommet-1);
		scanf("%d", &num_depart);
	}

	num_depart = get_param_sommet(num_depart, len_tab_sommet);

	fileACM = algo_fileACM(tab_sommet, tab_arc, len_tab_sommet, len_tab_arc, num_depart, &cout_chemin);	/*Récupère la file ACM, ainsi que le cout */


	ecran = affiche_cout(ecran, cout_chemin);

	/* Début affichage des lignes */

	Arc arc;	
	
	float window_width = get_width(ecran);

	int couleur = 0;		//0xff0000FF; 

	for (p = fileACM->suiv; p != fileACM; p = p->suiv) {
		arc =  *((Arc* ) p->val);

		x1 = tab_sommet[arc.sommet_depart].coordonnee_x*window_width;
		y1 = tab_sommet[arc.sommet_depart].coordonnee_y*window_width;

		x2 = tab_sommet[arc.sommet_arrive].coordonnee_x*window_width;
		y2 = tab_sommet[arc.sommet_arrive].coordonnee_y*window_width;

		Draw_Line(ecran, x1, y1, x2, y2, couleur);

		SDL_Flip(ecran);
	}

	/* NE PAS OUBLIER D'AFFICHER LE DERNIER, cf afficher_file */
	arc =  *((Arc* ) fileACM->val);

	x1 = tab_sommet[arc.sommet_depart].coordonnee_x*window_width;
	y1 = tab_sommet[arc.sommet_depart].coordonnee_y*window_width;

	x2 = tab_sommet[arc.sommet_arrive].coordonnee_x*window_width;
	y2 = tab_sommet[arc.sommet_arrive].coordonnee_y*window_width;

	Draw_Line(ecran, x1, y1, x2, y2, couleur);

	printf("Fin\n");

	SDL_Flip(ecran);

	/* Fin affichage des lignes */

	pause_sdl();		/* Mise en pause du programme */

	SDL_Quit();		/*quitte SDL */

	return 0;
}
