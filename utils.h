#pragma once

#include <stdio.h>

#include "sommet.h"
#include "arc.h"

void die(char*);
FILE* open_file(char*);
void lecture(char*, Sommet**, Arc**, int*, int*);
int get_param_sommet(int, int);