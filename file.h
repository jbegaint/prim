#pragma once

#include "liste.h"

typedef struct maillon_file {
	void *val;
	struct maillon_file *suiv;
} *File;

File creer_file(void);
int est_vide_file(File);
void afficher_file(File);
File enfiler(File, void*, size_t);
void* defiler(File*);
void free_file(File);