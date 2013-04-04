#ifndef LISTE_H
#define LISTE_H

typedef struct maillon {
	void *val;
	struct maillon *suiv;
} *Liste;

Liste crer_liste(void);
int est_vide_liste(Liste);
Liste ajouter_tete(void *, Liste, size_t);
void afficher_liste(Liste);
void afficher_element(Liste);
Liste free_list(Liste);
Liste supprimer_tete(Liste);

#endif