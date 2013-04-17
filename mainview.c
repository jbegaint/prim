#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>

#include "view.h"

#include "sommet.h"
#include "arc.h"
#include "liste.h"
#include "file.h"

#include "utils.h"



int main( int argc, char* argv[] ) { 
	
   	
	Sommet* tab_sommet;
	Arc* tab_arc;
	int len_tab_arc, len_tab_sommet;


if (argc < 2) {
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

lecture(argv[1], &tab_sommet, &tab_arc, &len_tab_sommet, &len_tab_arc);
	
	init_SDL ();

	SDL_Surface* ecran = NULL; //Defini un pointeur vers l'écran

	ecran=init_ecran(ecran);

	ecran=edit_point(ecran, tab_sommet,len_tab_sommet );
				

	pause(); // Mise en pause du programme

	SDL_Quit(); //Quitter SDL
	
	return 0; 
}
