#pragma once

#include "arbre.h"
#include "sommet.h"
#include "arc.h"
#include "file.h"

void afficheRSB(Arbre);
void afficheRSB_iteratif(Arbre);
Arbre algo_arbreACM(File, Sommet*, int);
File algo_fileACM(Sommet*, Arc*, int, int, int, float*);
