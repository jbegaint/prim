#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>

#include "view.h"
#include "algo.h"

#include "sommet.h"
#include "arc.h"
#include "liste.h"
#include "file.h"

#include "utils.h"



int main( int argc, char* argv[]){
	
   	
	Sommet* tab_sommet;
	Arc* tab_arc;
	int len_tab_arc, len_tab_sommet;
	File fileACM;
	float cout_chemin;
	


if (argc < 2) {
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	lecture(argv[1], &tab_sommet, &tab_arc, &len_tab_sommet, &len_tab_arc);
	
	init_SDL ();

	SDL_Surface* ecran = NULL; /*Defini un pointeur vers l'écran*/

	ecran=init_ecran(ecran);

	ecran=edit_point(ecran, tab_sommet,len_tab_sommet);

	int num_depart;

	if (argc > 2){
		num_depart = atoi(argv[2]);
	}
	else {
		printf("Entrez le numéro du sommet de départ: [0,%d]\n", len_tab_sommet);
		scanf("%d", &num_depart);
	}
  
	num_depart =  get_param_sommet(num_depart, len_tab_sommet);

	fileACM = algo_fileACM(tab_sommet, tab_arc, len_tab_sommet, len_tab_arc, num_depart, &cout_chemin);	
				
	
	pause_sdl(); /* Mise en pause du programme*/

	SDL_Quit(); /*Quitter SDL*/
	
	return 0; 
}


