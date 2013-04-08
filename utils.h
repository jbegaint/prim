#pragma once

FILE* open_file(char* file_name) {
	FILE *f;

	f = fopen(file_name, "r");
	if (f == NULL) {
		fprintf(stderr, "Ouverture impossible\n");
		exit(EXIT_FAILURE);
	}
	return f;
}