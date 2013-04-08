#include <stdio.h>
#include <stdlib.h>
#include <float.h>

#include "sommet.h"
#include "arc.h"
#include "liste.h"

#include "utils.h"


int main(int argc, char* argv[]) {

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

	return 0;
}