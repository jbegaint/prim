#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"
#include "liste.h"

int est_vide_file(File F)
{
	return est_vide_liste((Liste) F);
}

void afficher_file(File F)
{
	printf("{");
	if (est_vide_file(F)) {
	} else {
		File p;
		for (p = F->suiv; p != F; p = p->suiv) {
			afficher_element(p->val);
			printf(", ");
		}
		afficher_element(F->val);	/*affichage du dernier*/
	}
	printf("}\n");
}

File enfiler(File F, void *elt, size_t size_elt)
{

	File p;
	p = malloc(sizeof(*p));
	if (p == NULL) {
		return NULL;
	}

	p->val = malloc(size_elt);
	if (p->val == NULL) {
		return NULL;
	}

	memcpy(p->val, elt, size_elt);

	if (est_vide_file(F)) {
		p->suiv = p;
	} else {
		p->suiv = F->suiv;	 
		/*F->suiv : premier elt de la file et p : nouveau dernier
		 fifo: first in first out*/
		F->suiv = p;
	}
	return p;
}

void* defiler(File* F)
{
	if (est_vide_file(*F)) {
		fprintf((stderr), "Erreur: impossible de défiler une file vide \n");;
		exit(EXIT_FAILURE);
	}

	void *val = (*F)->suiv->val;

	if ((*F)->suiv != *F) {
		File tmp = (*F)->suiv->suiv;
		free((*F)->suiv);
		(*F)->suiv = tmp;
	} else {
		free(*F);
		*F = NULL;
	}
	return val;
}
