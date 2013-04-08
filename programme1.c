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

	ListeSommet liste_sommet; //liste de tous les sommets du fichier

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
		float min = FLT_MAX;
		Sommet sommet_ppc_min;
		for(p=C; !est_vide_liste((Liste) p); p=p->suiv) {
			if ( (p->sommet).PPC < min ) {
				min = (p->sommet).PPC;
				sommet_ppc_min = p->sommet;
			}
		}

		// supprimer j de C;
		for (p=C; !est_vide_liste((Liste) p); p=p->suiv) {
			if ( p->suiv == sommet_ppc_min ) {
				// on a trouvé j
				// il faut maintenant le supprimer de la liste

				// cas général
				p->suiv == sommet_ppc_min->suiv;
				free_liste((Liste) p->suiv);
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