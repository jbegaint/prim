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

	struct maillon* voisins; /* liste de pointeurs vers les arcs sortant du sommet */
	struct arc *arrive_par;	/*pointeur vers le meilleur arc à connecté à l’ACM */
	float PPC;	/*cout de l’arc arrive_par */

	struct NoeudArbre* noeudArbreACM; /* adresse du noeud de l'arbre qui contient le sommet */

} Sommet;


Sommet trouver_min_liste_sommet(struct maillon *);
