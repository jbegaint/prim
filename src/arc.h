#pragma once

#include "sommet.h"

typedef struct arc {
	int sommet_depart;
	int sommet_arrive;
	float cout;
} Arc;