#include <stdlib.h>
#include <stdio.h>

#include "liste.h"
#include "file.h"

int main() 
{
	size_t size_elt = sizeof(char);

	/* ------- TEST LISTE -------------------------------- */

	Liste L;
	L = creer_liste(); 

	/* pour tester d'autres types, attention pour le moment, 
	il faut aussi changer size_elt et afficher_element */
	
	// int c = 10210;
	// int d = 10000;
	// double c = 10210;
	// double d = 10000;

	char c = 'a';
	char d = 'b';
	char e = 'c';

	printf("##########\n");
	printf("TEST LISTE\n");
	printf("##########\n");


	printf("Liste: ");
	afficher_liste(L);

	L = ajouter_tete(&c, L, size_elt);
	printf("Liste: ");
	afficher_liste(L);

	L = ajouter_tete(&d, L, size_elt);
	printf("Liste: ");
	afficher_liste(L);

	L = supprimer_tete(L);
	printf("Liste: ");
	afficher_liste(L);

	/* ------- TEST FILE -------------------------------- */
	printf("##########\n");
	printf("TEST FILE\n");
	printf("##########\n");

	File F = creer_file();
	printf("File: ");
	afficher_file(F);

	F = enfiler(&c, F, size_elt);
	printf("File: ");
	afficher_file(F);

	F = enfiler(&d, F, size_elt);
	printf("File: ");
	afficher_file(F);

	defiler(&F);
	printf("File: ");
	afficher_file(F);

	F = enfiler(&e, F, size_elt);
	printf("File: ");
	afficher_file(F);

	// void *tmp = defiler(&F);
	afficher_element(defiler(&F));
	printf("défilé ");

	printf("\n");

	printf("File: ");
	afficher_file(F);

	return 0;
}