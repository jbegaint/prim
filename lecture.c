#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "sommet.h"
#include "arc.h"
#include "liste.h"

#include "utils.h"

int main(int argc, char *argv[])
{

	if (argc < 2) {
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	Sommet* tab_sommet;
	Arc* tab_arc;
	int len_tab_arc, len_tab_sommet;
	// lecture(argv[1], tab_sommet, tab_arc, &len_tab_sommet, &len_tab_arc);

	// printf("%d sommets et %d arcs \n", len_tab_sommet, len_tab_arc);

	return 0;
}
