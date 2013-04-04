#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

File creer_file(void) 
{
	return (File) creer_liste();
}

int est_vide_file(File F) 
{
	return est_vide_liste((Liste) F);
}

void afficher_file(File F)
{
	if (est_vide_file(F)) {
		printf("La file est vide \n");
	} else {
		File p;
		for(p=F->suiv; p != F; p=p->suiv) {
			afficher_element(p->val);
		}
		afficher_element(F->val); // affichage du dernier
	}
	printf("\n");
}

File enfiler(void* elt, File F, size_t size_elt)
{
	File p;
	p = malloc(sizeof(*p));
	if (p==NULL) {
		return NULL;
	}

	p->val = malloc(size_elt);
	if (p->val==NULL) {
		return NULL;
	}

	memcpy(p->val, elt, size_elt);

	if (est_vide_file(F)) {
		p->suiv = p;
	} else {
		p->suiv = F->suiv; // F->suiv : premier elt de la file et p : nouveau dernier
		// fifo: first in first ou
		F->suiv = p;
	}

	return p;
}