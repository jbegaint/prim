#pragma once

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

/* File d’Arc*/
typedef struct noeud {
	Arc arc;
	struct noeud * suiv;
}* FileArc;