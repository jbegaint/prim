#ifndef VIEW_H
#define VIEW_H
#include "sommet.h"

void pause();
void init_SDL (void);
SDL_Surface* init_ecran (SDL_Surface* ecran );
SDL_Surface* edit_point(SDL_Surface* ecran, Sommet* sommet, int len_tab_sommet);

#endif
