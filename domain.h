/*
* ergodic_controller.c
*
* Created: 2018-01-28
*  Author: Conan
*/

#ifndef DOMAIN_H_INCLUDED
#define DOMAIN_H_INCLUDED

// E_2 domain
typedef struct three_d_domain{
	double x_len;
	double y_len;				// domain lengths
	double z_len;

	double x_cell_len;
	double y_cell_len;			// Cell lengths
	double z_cell_len;

	double cell_size;			// measure of cell

	double x_min;
	double x_max;
	double x_size;
	double x_cells;

	double y_min;
	double y_max;
	double y_size;				// Minimums, maximums, measure for each axis
	double y_cells;

	double z_min;
	double z_max;
	double z_size;
	double z_cells;
}three_d_domain;


void build_E2(three_d_domain* E2, uint32_t dim, double min[], double max[], uint32_t cells[]);


#endif // DOMAIN_H_INCLUDED
