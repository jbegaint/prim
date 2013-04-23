#pragma once

#include "arbre.h"
#include "sommet.h"
#include "arc.h"
#include "file.h"

void afficheRSB(Arbre);
Arbre algo_arbreACM(File, Sommet*, int, float* cout);
File algo_fileACM(Sommet*, Arc*, int, int, int, float*);
