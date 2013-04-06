#ifndef ARCH_H
#define ARCH_H

#include "sommet.h"

/* Arc */
// typedef struct {
// 	int numero_debut;
// 	int numero_fin;
// 	float cout;
// } Arc;

typedef struct {
	Sommet sommet_depart;
	Sommet sommet_arrivee;
	float cout;
} Arc;

/* Liste d’Arc*/
typedef struct cellule {
	Arc arc;
	struct cellule * suiv;
}* ListeArc;


#endif