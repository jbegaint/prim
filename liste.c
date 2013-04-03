#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "liste.h"

Liste creer_liste(void)
{
	return NULL;
}

int est_vide_liste(Liste L) 
{
	return !L;
}

Liste ajouter_tete(void *elt, Liste L, size_t size_elt) 
{
	Liste p;
	p = (Liste) malloc(sizeof(*p));

	if (p == NULL)
		return NULL; // cas d'erreur d'attribution de mémoire

	// alloue de la mémoire pour p->val
	p->val = malloc(size_elt);
	if (p->val == NULL)
		return NULL;

	memcpy(p->val, elt, size_elt);

	p->suiv = L;
	return p;
}

Liste free_list(Liste L) {
	free(L->val);
	free(L);
}

Liste supprimer_tete(Liste L)
{
	Liste p;
	p = (Liste) malloc(sizeof(*p));
	if (p == NULL)
		return NULL;
	p = L -> suiv;
	free_list(L);
	return p;
}

void afficher_liste(Liste L) 
{
	Liste p;
	for (p=L; !est_vide_liste(p); p=p->suiv) {
		printf("%d\n", *(int *) p->val);
	}
}

int main() 
{
	size_t size_elt = sizeof(int);
	Liste L = creer_liste();
	int c = 10210;
	int d = 10000;
	L = ajouter_tete(&c, L, size_elt);
	L = ajouter_tete(&d, L, size_elt);

	afficher_liste(L);
	L = supprimer_tete(L);
	afficher_liste(L);

	return 0;
}