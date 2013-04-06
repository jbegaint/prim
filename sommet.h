#ifndef SOMMET_H
#define SOMMET_H

#include "arc.h"

/* Sommet */
typedef struct {
	int numero;
	char* nom;
	float coordonnee_x;
	float coordonnee_y;
	ListeArc voisins;

	Arc* arrive_par; // pointeur vers le meilleur arc à connecté à l’ACM
	float PPC; // cout de l’arc arrive_par

	Arbre* noeudArbreACM;

} Sommet;


/* Liste de Sommet */
typedef struct cellules {
	Sommet val;
	struct cellules * suiv;
}* ListeSommet;

#endif