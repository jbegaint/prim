#ifndef VIEW_H
#define VIEW_H
#include "sommet.h"
#include "arc.h"
#include "liste.h"
#include "file.h"

void pause();
void init_SDL (void);
SDL_Surface* init_ecran (SDL_Surface* ecran );
SDL_Surface* edit_point(SDL_Surface* ecran, Sommet* sommet, int len_tab_sommet);
SDL_Surface* affiche_cout (SDL_Surface* ecran, float cout);

#endif
