#include <stdlib.h>
#include <stdio.h>

#include "liste.h"
#include "file.h"
#include "arc.h"
#include "sommet.h"
#include "arbre.h"

void success()
{
	printf(" ok\n");
}

int main() 
{
	size_t size_char = sizeof(char);

	Sommet sommet1, sommet2, sommet3;

	/* Test Liste */
	Liste liste1 = NULL;
	Liste liste2 = ajouter_queue( &sommet1, liste2, size_char); 
// Liste ajouter_tete(void *, Liste, size_t);
// Liste ajouter_queue(void *, Liste, size_t);
// void afficher_liste(Liste);
// void afficher_arc(void *);
// void afficher_sommet(Sommet);
// Liste supprimer_tete(Liste);

// int recherche_elt_liste(Liste, void *);
// Liste ajout_tri(Sommet *, Liste);
	printf("[Test Liste]\n");

	printf("est_vide_liste... ");
	if ( est_vide_liste(liste1) && !est_vide_liste(liste2) )
		success();



	return 0;
}