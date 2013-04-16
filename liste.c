#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <float.h>

#include "liste.h"

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

	p = malloc(sizeof(*p));

	if (p == NULL)
		return NULL;	// problème d'attribution de mémoire

	// alloue de la mémiore pour p->val
	p->val = malloc(size_elt);
	if (p->val == NULL)
		return NULL;	// idem
	p->suiv = NULL;

	memcpy(p->val, elt, size_elt);
	
	if (!est_vide_liste(L)) {
		for (q=L; !est_vide_liste(q); q=q->suiv) {
			if (q->suiv == NULL)
				break;
		}

		q->suiv = p;
		return L;
	}

	return p;
}

Liste ajout_tri(Sommet s, Liste L) {
	Liste p;
	p = malloc(sizeof(*p));

	return p;
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
	printf("{");
	if (est_vide_liste(L)) {
	} 
	else {
		Liste p;
		for (p = L; !est_vide_liste(p); p = p->suiv) {
			afficher_sommet(*(Sommet *) p->val);
			if (!est_vide_liste(p->suiv))
				printf(", ");
		}
	}
	printf("}\n");
}

void afficher_sommet(Sommet s)
{
	printf("%s", s.nom);
}

void afficher_element(void *elt)
{
	// printf("%f |", (*(Arc *) elt).cout );
	printf("a%d_%d", (*(Arc *) elt).sommet_depart, (*(Arc *) elt).sommet_arrive );
}

int recherche_elt_liste(Liste L, void* elt) 
{
	Liste p;
	for (p=L; !est_vide_liste(p); p=p->suiv) {
		if ( (*(Sommet*) p->val).numero == (*(Sommet*) elt).numero)
			return 1;
	}
	return 0;
}

int len_liste(Liste L) 
{
	Liste p;
	int i=0;
	for (p=L; !est_vide_liste(p); p=p->suiv)
		i++;
	return i;
}