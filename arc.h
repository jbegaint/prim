#ifndef ARCH_H
#define ARCH_H

/* Arc */
typedef struct {
	int numero_debut;
	int numero_fin;
	float cout;
} Arc;

/* Liste d’Arc*/
typedef struct cellule {
	Arc arc;
	struct cellule * suiv;
}* ListeArc;


#endif