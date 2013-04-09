#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "sommet.h"
#include "arc.h"
#include "liste.h"
#include "file.h"
#include "utils.h"


FileArc algo_fileACM(void) {
	ListeSommet C;
	FileArc fileACM;
	Sommet d; // Sommet de départ

	ListeSommet liste_sommet; // liste de tous les sommets du fichier
	ListeArc liste_arc; // liste de tous les arcs du fichier

	// DEBUT ALGO

	ListeSommet p;
	for(p=liste_sommet; !est_vide_liste((Liste) p); p=p->suiv) {
		(p->sommet).PPC = FLT_MAX; 	//mettre un coût infini
		(p->sommet).arrive_par = NULL;
	}

	d.PPC = 0;
	d.arrive_par = NULL;
	fileACM = (FileArc) creer_liste();
	C = (ListeSommet) ajouter_queue(&d, (Liste) C, sizeof(Sommet));

	while( !est_vide_file((File) fileACM) ) {


		/* POUR TOUTES LES FONCTIONS QUI SUIVENT FAUDRA LES ECRIRE DANS UN FICHIER
		 POUR UN CODE PLUS EXPLICITE */

		// sommet j de C de plus petit PPC;
		Sommet sommet_ppc_min;
		sommet_ppc_min = trouver_min_liste_sommet(C);
		float min = sommet_ppc_min.PPC;
		// on récupère le sommet de plus petit PPC et son coût

		// supprimer j de C;
		if ( C->sommet.PPC == min) {
			// cas si j premier élément de C
			C = C->suiv;
		} 
		else {
			for (p=C; !est_vide_liste((Liste) p); p=p->suiv) {
				if ( (p->suiv->sommet).PPC == min ) {
					// on a trouvé j
					// il faut maintenant le supprimer de la liste

					// cas général
					// a voir si bug dans cas particuliers
					ListeSommet tmp;
					tmp = p->suiv->suiv;
					free_liste((Liste) p->suiv);
					p->suiv = tmp;
				}
			}
		}

		// si j n'est pas dans d;
		if (recherche_elt_liste((Liste) C, &sommet_ppc_min) != 1) {
			fileACM = (FileArc) enfiler((File) fileACM, &sommet_ppc_min.arrive_par, sizeof(Arc));
		}

		// il faut maintenant récupérer les adjacents à j

		ListeSommet liste_sommet_adjacent;
		ListeArc q;
		for (q=liste_arc; !est_vide_liste((Liste) liste_arc); q=q->suiv) {
			/* on a le droit au memcmp ici: il faut passé par calloc+memset, soit malloc
			 ici on regarde a gauche et a droite de l'arc car on a juste les arcs dans un 
			 seul sens pour le moment, il faudrait peut être les doubler lors de la lecture */
			if ( memcmp((q->arc).sommet_depart, sommet_ppc_min ) == 1 ){
				liste_sommet_adjacent = (ListeSommet) ajouter_queue(&(q->arc).sommet_depart, (Liste) liste_sommet_adjacent, sizeof(Sommet));
			} 
			else if ( memcmp((q->arc).sommet_arrive, sommet_ppc_min ) == 1) {
				liste_sommet_adjacent = (ListeSommet) ajouter_queue(&(q->arc).sommet_arrive, (Liste) liste_sommet_adjacent, sizeof(Sommet));
			}
		}

		// ListeSommet p

		for (p=liste_sommet_adjacent; !est_vide_liste((Liste) p); p=p->suiv) {
			if ( (p->sommet).PPC > min ) {

				(p->sommet).PPC = min;
				(p->sommet).arrive_par = sommet_ppc_min;

				if (recherche_elt_liste((Liste) C), &(p->sommet)) {
					C = (ListeSommet) ajouter_queue(&(p->sommet), (Liste) C, sizeof(Sommet));
				}
				else {
					printf("nothing now \n");
				}	

			}
		}
	}

	return fileACM;
	// FIN ALGO
}


int main(int argc, char* argv[]) {

	FileArc fileACM;
	fileACM = algo_fileACM();	

	return 0;
}