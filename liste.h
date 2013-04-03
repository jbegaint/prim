#ifndef LISTE_H
#define LISTE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct maillon {
	void *val;
	struct maillon *suiv;
} *Liste;

Liste crer_liste(void);
int est_vide_liste(Liste);
Liste ajouter_tete(void *, Liste, size_t);
void afficher_liste(Liste);


#endif