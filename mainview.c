#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>

#include "view.h"


int main( int argc, char* args[] ) { 
	
   	int i,j;
	
	init_SDL ();

	SDL_Surface* ecran = NULL; //Defini un pointeur vers l'écran

	ecran=init_ecran(ecran);

/*

	pause(); // Mise en pause du programme

	SDL_Quit(); //Quitter SDL*/
	
	return 0; 
}
