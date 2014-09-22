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
	p = malloc(sizeof(*p));

	if (p == NULL)
		return NULL;	

	p->val = malloc(size_elt); 	

	if (p->val == NULL)
		return NULL;

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
		return NULL;	

	p->val = malloc(size_elt);

	if (p->val == NULL)
		return NULL;

	p->suiv = NULL;

	memcpy(p->val, elt, size_elt);

	if (!est_vide_liste(L)) {
		for (q = L; !est_vide_liste(q); q = q->suiv) {
			if (est_vide_liste(q->suiv))
				break;
		}

		q->suiv = p;
		return L;
	}

	return p;
}

Liste ajout_tri(Sommet * s, Liste L)
{

	Liste p = NULL;
	Liste q;

	if (est_vide_liste(L) || (*s).PPC < (*(Sommet *) L->val).PPC) {
		return ajouter_tete(s, L, sizeof(Sommet));
	}

	for (q = L; !est_vide_liste(q->suiv); q = q->suiv) {
		if ( s->PPC < (*(Sommet *) q->suiv->val).PPC) {
			break;
		}
	}

	p = malloc(sizeof(*p));

	p->val = s;
	p->suiv = q->suiv;
	q->suiv = p;

	return L;
}

Liste supprimer_tete(Liste L)
{
	Liste p;

	if (est_vide_liste(L))
		return NULL;

	p = (Liste) malloc(sizeof(*p));

	if (p == NULL)
		return NULL;

	p = L->suiv;
	free(L);
	
	return p;
}

Liste supprimer_queue(Liste L)
{
	Liste p;
	if (est_vide_liste(L) || est_vide_liste(L->suiv))
		return NULL;

	p = L;
	while (!est_vide_liste(p->suiv->suiv)) {
		p = p->suiv;
	}
	free(p->suiv);
	p->suiv = NULL;

	return L;
}

void afficher_liste(Liste L)
{
	printf("{");
	if (!est_vide_liste(L)) {
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

void afficher_arc(Arc arc)
{
	printf("a%d_%d", arc.sommet_depart, arc.sommet_arrive);
}

int recherche_elt_list(Liste L, void *elt)
{
	Liste p;
	for (p = L; !est_vide_liste(p); p = p->suiv) {
		if ((*(Sommet *) p->val).numero == (*(Sommet *) elt).numero)
			return 1;
	}
	return 0;
}
