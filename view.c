#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>

#include "view.h"

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
      
	ecran=SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); // ouvre une fenetre de 640*480 32 bits, dans la mémoire video ou double buffer
	SDL_WM_SetCaption("Chemin le plus court", NULL);//Nomme la fenetre

	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 80, 80, 80));//Mise en couleur de l'écran

	SDL_Flip(ecran); //Mise à jour de l'écran

	return ecran;	
}

//////////////////////////A mettre en forme
SDL_Surface* edit_point(SDL_Surface* ecran)
{
SDL_Surface *point = NULL;

SDL_Rect position;

	point = SDL_CreateRGBSurface(SDL_HWSURFACE, 9, 9, 32, 0, 0, 0, 0);//Point 

	SDL_FillRect(point, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

	position.x = 0; // Les coordonnées de la surface seront (0,0)
    	position.y = 0; 
       	    	
	SDL_BlitSurface(point, NULL, ecran, &position); // Collage de la surface sur l'écran
	SDL_Flip(ecran); // Mise à jour de l'écran		

	
	SDL_FreeSurface(point); 
}
