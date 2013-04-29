#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#include "view.h"
#include "sommet.h"
#include "arc.h"
#include "liste.h"
#include "file.h"
#include "utils.h"


void pause_sdl()
{				/*permet de conserver l'affichage et d'initialiser la croix pour fermer le programme */
	int continuer = 1;


	SDL_Event event;

	while (continuer) {
		SDL_WaitEvent(&event);
		switch (event.type) {
		case SDL_QUIT:
			continuer = 0;
		}
	}
}


void init_SDL(void)
{
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {	/* Démarrage de la SDL. Si erreur : */
		fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());	/* Écriture de l'erreur */
		exit(EXIT_FAILURE);	/* On quitte le programme */
	}
}

SDL_Surface *init_ecran(SDL_Surface * ecran)
{
	/* ouvre une fenetre de 640*480 32 bits, dans la mémoire video ou double buffer */
	ecran =
	    SDL_SetVideoMode(600, 700, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption("Chemin le plus court", NULL);	/* Nomme la fenetre */
	SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 70, 70, 70));	/*Mise en couleur de l'écran */
	SDL_Flip(ecran);	/*Mise à jour de l'écran */
	return ecran;
}


SDL_Surface *edit_point(SDL_Surface * ecran, Sommet * sommet,
			int len_tab_sommet)
{
	int i = 0;

	/* Sert pour les couleurs des sommets */
	char a, b, c;
	srand(time(NULL));

	TTF_Init();		/*Initialise SDL_TTF (police d'écriture) */
	TTF_Font *police = NULL;	/*Pointeur vers police */
	police = TTF_OpenFont("DroidSans.ttf", 15);

	if (police == NULL) {
		die("Erreur lecture fichier police");
	}

	SDL_Color couleur = { 0, 0, 0 };	/*Couleur Noire */

	SDL_Surface *nom_sommet = NULL;	/*Surface pour l'écriture du sommet */
	SDL_Surface *point = NULL;	/*Surface pour affichage des points */
	SDL_Surface *progression = NULL;	/*Surface pour la barre de progression */

	SDL_Rect position_sommet;	/*Position pour les noms des sommets */
	SDL_Rect position;	/*Position pour la progression */
	SDL_Rect position_progression;	/*Position pour les sommets */

	point = SDL_CreateRGBSurface(SDL_HWSURFACE, 2, 2, 32, 0, 0, 0, 0);	/*Création d'un rectangle 2*2 en couleur 32 bits) */
	progression = SDL_CreateRGBSurface(SDL_HWSURFACE, 10, 10, 32, 0, 0, 0, 0);	/*Création d'un rectangle 10*10 en couleur 32 bits) */


	for (i = 0; i < len_tab_sommet; i++) {

		/* Position des noms des sommets */
		position_sommet.x = sommet[i].coordonnee_x * 600.0 - 5;
		position_sommet.y = sommet[i].coordonnee_y * 600.0;

		nom_sommet = TTF_RenderText_Blended(police, sommet[i].nom, couleur);	/*Nomme les sommets */
		SDL_BlitSurface(nom_sommet, NULL, ecran, &position_sommet);	/*Affiche les noms */

		/*Position des sommets */
		position.x = sommet[i].coordonnee_x * 600.0;
		position.y = sommet[i].coordonnee_y * 600.0;

		/*Initialises couleur des sommets de manière aléatoire */
		a = rand() % (255 - 0) + 0;
		b = rand() % (255 - 0) + 0;
		c = rand() % (255 - 0) + 0;

		SDL_FillRect(point, NULL, SDL_MapRGB(ecran->format, a, b, c));	/*Place les sommets */
		SDL_BlitSurface(point, NULL, ecran, &position);	/* Collage des sommets sur l'écran */

		/*Mise à jour de l'écran */
		SDL_Flip(ecran);

		/*Idem mais pour la barre de progression */
		position_progression.y = 650;
		position_progression.x = i * 300 / len_tab_sommet + 150;
		SDL_FillRect(progression, NULL,
			     SDL_MapRGB(ecran->format, 255, 255, 255));
		SDL_BlitSurface(progression, NULL, ecran,
				&position_progression);
		SDL_Flip(ecran);
	}
	/*On libère la mémoire de la police, des surfaces nom_sommet, point, progression et on stope SDL_TTF */
	TTF_CloseFont(police);
	SDL_FreeSurface(nom_sommet);
	SDL_FreeSurface(point);
	SDL_FreeSurface(progression);
	TTF_Quit();
	return ecran;
}


SDL_Surface *affiche_cout(SDL_Surface * ecran, float cout)
{
	/*Affichage cout : Même principe que pour afficher le nom des sommets :
	   On ouvre une police, on initialise couleur, position et on l'affiche.
	   Puis on libère la mémoire */

	TTF_Init();

	TTF_Font *police = NULL;
	police = TTF_OpenFont("DroidSans.ttf", 25);
	SDL_Color couleur = { 0, 0, 0 };
	SDL_Rect position_cout;
	SDL_Surface *cout_chemin = NULL;

	char buffer_cout[50];

	sprintf(buffer_cout, "%f", cout);	/*Convertie le float en chaine de caractère */

	position_cout.x = 470;
	position_cout.y = 620;

	cout_chemin = TTF_RenderText_Blended(police, "cout :", couleur);
	SDL_BlitSurface(cout_chemin, NULL, ecran, &position_cout);

	position_cout.x = 470;
	position_cout.y = 650;

	cout_chemin = TTF_RenderText_Blended(police, buffer_cout, couleur);
	SDL_BlitSurface(cout_chemin, NULL, ecran, &position_cout);
	SDL_Flip(ecran);


	TTF_CloseFont(police);
	SDL_FreeSurface(cout_chemin);

	TTF_Quit();

	return ecran;
}



SDL_Surface *Ligne(SDL_Surface * ecran, float x1, float y1, float x2,
		   float y2)
{				/*algorithme de Bresenham */

	int x, y, ValAbsx, ValAbsy, deplacementx, deplacementy, milieu, i;
	long couleur = 65536 * 255 + 256 * 255 + 255;
	/*Convertie la couleur en long */
	int BytesPixel;
	char *position;

	x1 = x1 * 600.0; 
	x2 = x2 * 600.0;
	y1 = y1 * 600.0;
	y2 = y2 * 600.0;

	ValAbsx = abs(x2 - x1);
	ValAbsy = abs(y2 - y1);

	deplacementx = (x1 > x2) ? -1 : 1;
	deplacementy = (y1 > y2) ? -1 : 1;

	x = x1;
	y = y1;

	if (ValAbsx > ValAbsy) {
		milieu = ValAbsx / 2;
		for (i = 0; i < ValAbsx; i++) {
			x = x + deplacementx;
			milieu = milieu + ValAbsy;
			if (milieu > ValAbsx) {
				milieu = milieu - ValAbsx;
				y = milieu + deplacementy;
			}
			BytesPixel = ecran->format->BytesPerPixel;
			position =
			    (unsigned char *) ecran->pixels +
			    y * ecran->pitch + x * BytesPixel;
			if (BytesPixel == 4) {
				*(unsigned long *) position = couleur;
			}
		}
	} else {
		milieu = ValAbsy / 2;
		for (i = 0; i < ValAbsy; i++) {
			y = y + deplacementy;
			milieu += ValAbsx;

			if (milieu > ValAbsy) {
				milieu = milieu - deplacementx;
				x = x + deplacementx;
			}
			BytesPixel = ecran->format->BytesPerPixel;
			position =
			    (unsigned char *) ecran->pixels +
			    y * ecran->pitch + x * BytesPixel;
			if (BytesPixel == 4) {
				*(unsigned long *) position = couleur;
			}
		}

	}
	return ecran;
}
