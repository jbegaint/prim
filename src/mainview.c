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


void draw_arc( SDL_Surface* ecran, Arc arc, Sommet* tab_sommet) 
{
	float x1, x2, y1, y2;
	float window_width = get_width(ecran);
	int offset = 25;
	x1 = tab_sommet[arc.sommet_depart].coordonnee_x*window_width + offset;
	y1 = tab_sommet[arc.sommet_depart].coordonnee_y*window_width + offset;

	x2 = tab_sommet[arc.sommet_arrive].coordonnee_x*window_width + offset;
	y2 = tab_sommet[arc.sommet_arrive].coordonnee_y*window_width + offset;

	int couleur = 0;

	Draw_Line(ecran, x1, y1, x2, y2, couleur);
	SDL_Flip(ecran);
}

int main(int argc, char **argv)
{

	if (argc < 2) {
		fprintf(stderr, "Usage: %s fichier\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	Sommet* tab_sommet;
	Arc* tab_arc;

	int len_tab_sommet, len_tab_arc;

	lecture(argv[1], &tab_sommet, &tab_arc, &len_tab_sommet, &len_tab_arc);

	int num_depart;
	if (argc > 2)
		num_depart = atoi(argv[2]);
	else {
		printf("Entrez le numéro du sommet de départ: [0,%d]\n", len_tab_sommet);
		scanf("%d", &num_depart);
	}

	num_depart = get_param_sommet(num_depart, len_tab_sommet);

	File fileACM;
	float cout = 0;
	fileACM = algo_fileACM(tab_sommet, tab_arc, len_tab_sommet, len_tab_arc, num_depart, &cout);	
	printf("FileACM: ");
	afficher_file(fileACM);

	Arbre arbreACM;
	arbreACM = algo_arbreACM(fileACM, tab_sommet, num_depart);

	/*float cout_arbre = 0;
	cout_arbreACM(arbreACM, &	cout_arbre);
	printf("%f\n", cout_arbre);*/

	printf("arbreACM (recursif): ");
	printf("[ ");
	afficheRSB(arbreACM);
	printf("]\n");

	printf("arbreACM (iteratif): ");

	Liste arbre;
	arbre = afficheRSB_iteratif(arbreACM);
	afficher_liste(arbre);

	init_SDL();

	SDL_Surface *ecran = NULL;	/*Defini un pointeur vers l'écran */

	ecran = init_ecran(ecran);

	ecran = edit_point(ecran, tab_sommet, len_tab_sommet);

	float cout_chemin;

	ecran = affiche_cout(ecran, cout_chemin);

	/* Début affichage des lignes */

	Arc arc;	
	
	float window_width = get_width(ecran);
	float x1, x2, y1, y2;

	// int couleur = 0;		//0xff0000FF; 

	// for (p = fileACM->suiv; p != fileACM; p = p->suiv) {
	// 	arc =  *((Arc* ) p->val);
	// 	draw_arc(ecran, arc, tab_sommet);
	// }

	/* NE PAS OUBLIER D'AFFICHER LE DERNIER, cf afficher_file */
	// arc =  *((Arc* ) fileACM->val);
	// draw_arc(ecran, arc, tab_sommet);


	// TEST AATATAAT
	float offset = 25;
	int couleur = 0;

	
	Liste pp;
	Sommet sommet1, sommet2;

	for ( pp = arbre; !est_vide_liste(pp) && !est_vide_liste(pp->suiv); pp = pp->suiv){

		sommet1 = *(Sommet *) pp->val;
		sommet2 = *(Sommet *) pp->suiv->val;

		x1 = sommet1.coordonnee_x*window_width + offset;
		y1 = sommet1.coordonnee_y*window_width + offset;

		x2 = sommet2.coordonnee_x*window_width + offset;
		y2 = sommet2.coordonnee_y*window_width + offset;

		Draw_Line(ecran, x1, y1, x2, y2, couleur);
		SDL_Flip(ecran);

	}

	/* Fin affichage des lignes */

	printf("Fin\n");

	/* Mise en pause du programme */
	pause_sdl();		

	/* quitte SDL */
	SDL_Quit();		

	return 0;
}
