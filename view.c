#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>

#include "view.h"
#include "sommet.h"
#include "arc.h"
#include "liste.h"
#include "file.h"

#include "utils.h"

void pause() //permet de conserver l'affichage et d'initialiser la croix pour fermer le programme
{
    int continuer = 1;
    

    SDL_Event event;
  
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}


void init_SDL (void)
{ if (SDL_Init(SDL_INIT_VIDEO) == -1) // Démarrage de la SDL. Si erreur :
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); // Écriture de l'erreur
        exit(EXIT_FAILURE); // On quitte le programme
    }
}

SDL_Surface* init_ecran (SDL_Surface* ecran)
{
      
	ecran=SDL_SetVideoMode(700, 700, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); // ouvre une fenetre de 640*480 32 bits, dans la mémoire video ou double buffer
	SDL_WM_SetCaption("Chemin le plus court", NULL);//Nomme la fenetre

	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 80, 80, 80));//Mise en couleur de l'écran

	SDL_Flip(ecran); //Mise à jour de l'écran

	return ecran;	
}


SDL_Surface* edit_point(SDL_Surface* ecran, Sommet* sommet, int len_tab_sommet)
{
int i=0;
SDL_Surface *point = NULL;

SDL_Rect position;

	point = SDL_CreateRGBSurface(SDL_HWSURFACE, 2, 2, 32, 0, 0, 0, 0);//Point 

	SDL_FillRect(point, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

for (i=0;i<len_tab_sommet;i++){
	position.x=sommet[i].coordonnee_x*700;
	position.y=sommet[i].coordonnee_y*700;
	
       	    	
	SDL_BlitSurface(point, NULL, ecran, &position); // Collage de la surface sur l'écran
	SDL_Flip(ecran); // Mise à jour de l'écran		
	}
	
	SDL_FreeSurface(point); 
}
