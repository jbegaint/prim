#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

FILE* open_file(char* file_name) {
  FILE *f;

  f = fopen(file_name, "r");
  if (f == NULL) {
    fprintf(stderr, "Ouverture impossible\n");
    exit(EXIT_FAILURE);
  }
  return f;
}