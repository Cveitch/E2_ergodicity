/*
* ergodic_controller.c
*
* Created: 2018-01-28
*  Author: Conan
*/

#include "domain.h"

// Initializes E2 struct values
void build_E2(three_d_domain* E2, uint32_t dim, double min[], double max[], uint32_t cells[]) {
	uint32_t i = 0;
	E2->x_len = max[i] - min[i];
	E2->x_size = (max[i] - min[i]) / cells[i];
	E2->x_min = min[i];
	E2->x_max = max[i];
	E2->x_cells = cells[i];
    // iterate over the 3-tuples.
	i++;
	E2->y_len = max[i] - min[i];
	E2->y_size = (max[i] - min[i]) / cells[i];
	E2->y_min = min[i];
	E2->y_max = max[i];
	E2->y_cells = cells[i];
    // iterate over the 3-tuples.
	i++;
	E2->z_len = max[i] - min[i];
	E2->z_size = (max[i] - min[i]) / cells[i];
	E2->z_min = min[i];
	E2->z_max = max[i];
	E2->z_cells = cells[i];

	E2->cell_size = 1.0;
	int j;
	for (j = 0; j < i; j++) {
		E2->cell_size *= (max[j] - min[j]) / cells[j];
	}
}
