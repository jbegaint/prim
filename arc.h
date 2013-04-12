#pragma once

#include "sommet.h"

typedef struct arc {
	Sommet* sommet_depart;
	Sommet* sommet_arrive;
	float cout;
} Arc;