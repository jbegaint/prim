#include <stdlib.h>
#include <stdio.h>

#include "liste.h"

int main() 
{
	size_t size_elt = sizeof(char);

	// Liste L = creer_liste(); warning à la compilation
	Liste L = NULL; // là ça marche ...

	// int c = 10210;
	// int d = 10000;
	// double c = 10210;
	// double d = 10000;

	char c = 'a';
	char d = 'b';
	L = ajouter_tete(&c, L, size_elt);
	printf("Liste: ");
	afficher_liste(L);

	L = ajouter_tete(&d, L, size_elt);
	printf("Liste: ");
	afficher_liste(L);

	L = supprimer_tete(L);
	printf("Liste: ");
	afficher_liste(L);

	return 0;
}