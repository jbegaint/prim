#pragma once

struct NoeudArbre;
struct arc;
struct cellule;
struct maillon;

/* Sommet */
typedef struct {
	int numero;
	char nom[256];
	float coordonnee_x;
	float coordonnee_y;
	struct cellules* voisins;

	struct arc* arrive_par; // pointeur vers le meilleur arc à connecté à l’ACM
	float PPC; // cout de l’arc arrive_par

	struct NoeudArbre* noeudArbreACM;

} Sommet;


Sommet trouver_min_liste_sommet(struct maillon*);