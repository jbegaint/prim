#include <stdlib.h>
#include <stdio.h>

#include "liste.h"
#include "file.h"
#include "arc.h"
#include "sommet.h"
#include "arbre.h"
#include "utils.h"

void test(int res)
{
	char* c;
	c = (res) ? "[OK]" : "[ERROR]";
	printf("%s\n", c);
}

int main() 
{

	Sommet sommet1, sommet2, sommet3;

	/* Test Liste */
	Liste liste1 = NULL;
	Liste liste2 = NULL; 

	printf("[Test Liste]\n");


	printf("ajouter_tete... ");
	liste1 = ajouter_tete(&sommet1, liste1, sizeof(Sommet));
	test( !est_vide_liste(liste1) && (memcmp(&sommet1, (Sommet *) liste1->val, sizeof(Sommet)) == 0) );

	printf("ajouter_queue... ");
	liste1 = ajouter_queue(&sommet2, liste1, sizeof(Sommet));
	test( (memcmp(&sommet2, (Sommet *) liste1->suiv->val, sizeof(Sommet)) == 0) );


	printf("est_vide_liste... ");
	test( !est_vide_liste(liste1) && est_vide_liste(liste2) );

	printf("supprimer_tete... ");
	liste1 = supprimer_tete(liste1);
	test( (memcmp(&sommet2, (Sommet *) liste1->val, sizeof(Sommet)) == 0) );

	printf("recherche_elt_liste... ");
	test( recherche_elt_liste(liste1, &sommet2));

	printf("ajout_tri... ");
	liste1 = NULL;
	sommet1.PPC = 1;
	sommet2.PPC = 2;
	sommet3.PPC = 3;

	liste1 = ajout_tri(&sommet2, liste1);
	liste1 = ajout_tri(&sommet1, liste1);
	liste1 = ajout_tri(&sommet3, liste1);


	test( (memcmp(&sommet1, (Sommet *) liste1->val, sizeof(Sommet)) == 0) 
			&& (memcmp(&sommet2, (Sommet *) liste1->suiv->val, sizeof(Sommet)) == 0)
			&& (memcmp(&sommet3, (Sommet *) liste1->suiv->suiv->val, sizeof(Sommet)) == 0)
		 );

	printf("\n");

	/* Test Liste */
	printf("[Test File]\n");

	File file1 = NULL;
	File file2 = NULL;

	printf("enfiler... ");
	file1 = enfiler( file1, &sommet1, sizeof(Sommet));
	test( (memcmp(&sommet1, (Sommet *) file1->val, sizeof(Sommet)) == 0) );

	printf("est_vide_file... ");
	test( !est_vide_file(file1) && est_vide_file(file2) );

	printf("defiler... ");
	file1 = enfiler( file1, &sommet2, sizeof(Sommet));
	test( (memcmp( &sommet1, (Sommet *) defiler(&file1), sizeof(Sommet)) == 0) );

	printf("\n");

	/* Test Sommet */
	printf("[Test Sommet]\n");

	printf("trouver_min_liste_sommet... ");
	Sommet smt;
	smt = trouver_min_liste_sommet(liste1);
	test( (memcmp( &smt, &sommet1, sizeof(Sommet)) == 0) );

	printf("\n");

	/* Test Arbre */
	printf("[Test Arbre]\n");

	printf("ajouter_arbre... ");

	Arc arc1;
	arc1.sommet_depart = 0;
	arc1.sommet_arrive = 1;

	Arbre arbre1 = malloc(sizeof(Arbre));
	arbre1->sommet = &sommet1;

	sommet1.noeudArbreACM = arbre1;
	Sommet tab_sommet[2];
	tab_sommet[0] = sommet1;
	tab_sommet[1] = sommet2;

	ajouter_arbre( &arc1, tab_sommet);
	test( (memcmp(&sommet1, (sommet1.noeudArbreACM)->sommet, sizeof(Sommet)) == 0) );

	printf("\n");

	/* Test Utils */
	printf("[Test Utils]\n");

	printf("get_arc... ");
	Arc arc2;
	arc1.cout = 1;
	arc2 = get_arc(0, 1, 1);
	test( (memcmp(&arc1, &arc2, sizeof(Arc)) == 0) );

	printf("get_param_sommet... ");
	test( (get_param_sommet(1, 2) == 1 ) && (get_param_sommet(2, 2) == 0) && (get_param_sommet(3, 2) == 0));

	printf("open_file... ");
	FILE* f;
	f = open_file("exemple.txt");
	test( f != NULL );
	fclose(f);

	return 0;
}