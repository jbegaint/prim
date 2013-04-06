#pragma once

/* Arc */
// typedef struct {
// 	int numero_debut;
// 	int numero_fin;
// 	float cout;
// } Arc;

#include "sommet.h"

typedef struct arc {
	Sommet sommet_depart;
	Sommet sommet_arrive;
	float cout;
} Arc;

/* Liste d’Arc*/
typedef struct cellule {
	Arc arc;
	struct cellule * suiv;
}* ListeArc;