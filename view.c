#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 

#include "view.h"
#include "sommet.h"
#include "arc.h"
#include "liste.h"
#include "file.h"

#include "utils.h"

void pause() /*permet de conserver l'affichage et d'initialiser la croix pour fermer le programme*/
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
{ if (SDL_Init(SDL_INIT_VIDEO) == -1) /* Démarrage de la SDL. Si erreur :*/
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError()); /* Écriture de l'erreur */
        exit(EXIT_FAILURE); /* On quitte le programme*/
    }
}

SDL_Surface* init_ecran (SDL_Surface* ecran)
{
      
	ecran=SDL_SetVideoMode(600, 700, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); 
	/* ouvre une fenetre de 640*480 32 bits, dans la mémoire video ou double buffer*/
	SDL_WM_SetCaption("Chemin le plus court", NULL);/* Nomme la fenetre*/
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 70, 70, 70));/*Mise en couleur de l'écran*/
	SDL_Flip(ecran); /*Mise à jour de l'écran*/
	return ecran;	
}


SDL_Surface* edit_point(SDL_Surface* ecran, Sommet* sommet, int len_tab_sommet)
{
int i=0;
char a,b,c;
srand(time(NULL));
SDL_Surface *point = NULL;
SDL_Surface *progression = NULL;

SDL_Rect position;
SDL_Rect position_progression;

	point = SDL_CreateRGBSurface(SDL_HWSURFACE, 2, 2, 32, 0, 0, 0, 0);/*//Point */
	progression = SDL_CreateRGBSurface(SDL_HWSURFACE, 10, 10, 32, 0, 0, 0, 0);/*//Point*/


for (i=0;i<len_tab_sommet;i++){
	position.x=sommet[i].coordonnee_x*600;
	position.y=sommet[i].coordonnee_y*600
;
	a=rand()%(255-0)+0;/*//Initialises couleur des points*/
	b=rand()%(255-0)+0;
	c=rand()%(255-0)+0;
       	SDL_FillRect(point, NULL, SDL_MapRGB(ecran->format, a, b, c));    	
	SDL_BlitSurface(point, NULL, ecran, &position); /*// Collage de la surface sur l'écran*/
	SDL_Flip(ecran); /*// Mise à jour de l'écran*/

	position_progression.y=650;
	position_progression.x=i*300/len_tab_sommet+150;
	SDL_FillRect(progression, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));  
	SDL_BlitSurface(progression, NULL, ecran, &position_progression); /* Collage de la surface sur l'écran*/
	SDL_Flip(ecran); /* Mise à jour de l'écran*/
  
}	

	
	
	SDL_FreeSurface(point); 
	return ecran;
}
