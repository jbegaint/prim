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
		return NULL;	// problème d'attribution de mémoire

	// alloue de la mémiore pour p->val
	p->val = malloc(size_elt);
	if (p->val == NULL)
		return NULL;	// idem

	memcpy(p->val, elt, size_elt);

	p->suiv = L;
	return p;
}

Liste ajouter_queue(void *elt, Liste L, size_t size_elt)
{
	Liste p;
	Liste q;

	p = (Liste) malloc(sizeof(*p));

	if (p == NULL)
		return NULL;	// problème d'attribution de mémoire

	// alloue de la mémiore pour p->val
	p->val = malloc(size_elt);
	if (p->val == NULL)
		return NULL;	// idem

	memcpy(p->val, elt, size_elt);

	if (est_vide_liste(L))
		return p;

	for (q=L; !est_vide_liste(q); q=q->suiv) {
		if (q->suiv == NULL)
			break;
	}

	q->suiv = p;
	return L;
}

void free_liste(Liste L)
{
	free(L->val);
	free(L);
}

Liste supprimer_tete(Liste L)
{
	Liste p;
	p = (Liste) malloc(sizeof(*p));
	if (p == NULL)
		return NULL;
	p = L->suiv;
	free_liste(L);
	return p;
}

void afficher_liste(Liste L)
{
	if (est_vide_liste(L)) {
		printf("La liste est vide\n");
	} else {
		Liste p;
		for (p = L; !est_vide_liste(p); p = p->suiv) {
			afficher_element(p->val);
		}
		printf("\n");
	}
}

void afficher_element(void *elt)
{
	printf("%c |", *(char *) elt);
}

void afficher_liste_arc(ListeArc L)
{
	if (est_vide_liste((Liste)L)) {
		printf("La liste est vide\n");
	} else {
		ListeArc p;
		for (p = L; !est_vide_liste((Liste)p); p = p->suiv) {
			afficher_element_arc(p->arc);
		}
		printf("\n");
	}
}

void afficher_element_arc(Arc a)
{
	printf("Arc: \n");
}
