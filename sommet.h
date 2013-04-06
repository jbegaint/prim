#ifndef SOMMET_H
#define SOMMET_H

/* Sommet */
typedef struct {
	int numero;
	char* nom;
	float coordonnee_x;
	float coordonnee_y;
	ListeARC voisins;

	*Arc arrive_par; // pointeur vers le meilleur arc à connecté à l’ACM
	float PPC; // cout de l’arc arrive_par
} Sommet;


/* Liste de Sommet */
struct cellule {
	Sommet val;
	struct cellule * suiv;
};
typedef struct cellule* ListeSommet;

#endif