#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h> 
#include <float.h>

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


File algo_fileACM(Sommet* tab_sommet, Arc* tab_arc, int len_tab_sommet, int len_tab_arc, int num_depart, float* cout_chemin) {

	File fileACM = NULL;
	Liste C = NULL;

	float cout = 0;

	Liste liste_sommet_atteint = NULL;

	Sommet d = tab_sommet[num_depart];

	/*
		DEBUT ALGO
	*/

	Sommet* smt;
	for (smt=tab_sommet; smt < tab_sommet+len_tab_sommet; smt++) {
		(*smt).PPC = FLT_MAX;
		(*smt).arrive_par = NULL;
	}
	
	d.PPC = 0;
	d.arrive_par = NULL;

	C = ajout_tri(&d, C);
	liste_sommet_atteint = ajouter_queue(&d, liste_sommet_atteint, sizeof(Sommet));

	/*int i=0;*/
	 /*compteur étapes*/

	while( !est_vide_liste(C) ) {

/*		 blabla itératif
*/
		/* printf("Étape: %d\n", i);
		 printf("C: "); afficher_liste(C);
		 printf("D: "); afficher_liste(liste_sommet_atteint);
		 printf("fileACM: "); afficher_file(fileACM);
		 printf("--------------\n");
		 getchar();
		 i++;*/

		/*sommet de C de plus petit PPC;*/
		Sommet sommet_ppc_min;

		/*on récupère le sommet de plus petit PPC et son coût*/
		/*Comme la liste est triée, c'est le premier élément de C*/
		sommet_ppc_min = *(Sommet*) C->val;

		/*supprimer j de C*/
		

		C = supprimer_tete(C);

		/*si j n'est pas d*/
		if ( sommet_ppc_min.numero != d.numero ) {
			cout += sommet_ppc_min.PPC;
			fileACM = enfiler(fileACM, sommet_ppc_min.arrive_par, sizeof(Arc));
			liste_sommet_atteint = ajouter_queue(&sommet_ppc_min, liste_sommet_atteint, sizeof(Sommet));
		}

		/* il faut maintenant récupérer les adjacents à j*/

		Liste liste_sommet_adjacent = NULL;
		Liste liste_arc_sortant = NULL;

		Arc* a;

		Liste ll;

		for (a=tab_arc; a < tab_arc + len_tab_arc; a++) {
			/* A voir pour la comparaison */
			if ( (*a).sommet_depart == sommet_ppc_min.numero ) {
				liste_sommet_adjacent = ajouter_queue(&tab_sommet[(*a).sommet_arrive], liste_sommet_adjacent, sizeof(Sommet));
			
				liste_arc_sortant = ajouter_queue(a, liste_arc_sortant, sizeof(Arc));
			}
			if ( (*a).sommet_arrive == sommet_ppc_min.numero ) {
				liste_sommet_adjacent = ajouter_queue(&tab_sommet[(*a).sommet_depart], liste_sommet_adjacent, sizeof(Sommet));
				
				liste_arc_sortant = ajouter_queue(a, liste_arc_sortant, sizeof(Arc));
			}
		}

		sommet_ppc_min.voisins = liste_arc_sortant;

		for (ll=liste_arc_sortant; !est_vide_liste(ll); ll=ll->suiv) {

			a = (Arc *) ll->val;

			if ( (tab_sommet[(*a).sommet_arrive]).PPC > (*a).cout ) {

				tab_sommet[(*a).sommet_arrive].PPC = (*a).cout;
				tab_sommet[(*a).sommet_arrive].arrive_par = a;

				if (recherche_elt_liste(liste_sommet_atteint, &tab_sommet[(*a).sommet_arrive]) != 1) {
					if (recherche_elt_liste(C, &tab_sommet[(*a).sommet_arrive]) != 1) {
						C = ajout_tri(&tab_sommet[(*a).sommet_arrive], C);
					}
				}	
			}

			if ( (tab_sommet[(*a).sommet_depart]).PPC > (*a).cout ) {

				tab_sommet[(*a).sommet_depart].PPC = (*a).cout;
				tab_sommet[(*a).sommet_depart].arrive_par = a;

				if (recherche_elt_liste(liste_sommet_atteint, &tab_sommet[(*a).sommet_depart]) != 1) {
					if (recherche_elt_liste(C, &tab_sommet[(*a).sommet_depart]) != 1) {				
						C = ajout_tri(&tab_sommet[(*a).sommet_depart], C);
					}
				}	
			}
		}

	}

	/*printf("Cout de l'acm: %f\n", cout);*/
	*cout_chemin=cout;
	return fileACM;
	/*FIN ALGO*/
}
