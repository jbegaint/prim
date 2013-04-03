#include <stdlib.h>
#include <stdio.h>

#include "liste.h"

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