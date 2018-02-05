/*
* ergodicity.h
*
* Created: 2018-01-28
*  Author: Conan
*/

#include <stdint.h>


#ifndef ERGODICITY_H_
#define ERGODICITY_H_



// These are hardcoded values. This is janky, but we can't dynamically
// assign values to multi-dim array due to bare metal restrictions on
// malloc.  So rather than split things, all distribution values are here.
#define dist_x 100
#define dist_y 100
#define dist_r 10
#define x_centre 50
#define y_centre 50



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
	double x_cell;

	double y_min;
	double y_max;
	double y_size;				// Minimums, maximums, measure for each axis
	double y_cell;

	double z_min;
	double z_max;
	double z_size;
	double z_cell;
}three_d_domain;


// Ergodicity information
typedef struct ergodic_controller{
	uint32_t M;						// M, N, P are directional indices
	uint32_t N;
	uint32_t P;
	//uint32_t phi[][];
}ergodic_controller;




void get_phi_coefficients();
void build_controller(uint32_t k, struct three_d_domain E2 );
void build_E2(three_d_domain* E2, uint32_t dim, double min[], double max[], double cells[]);
void build_distribution(three_d_domain* E2, uint32_t radius, uint32_t centre_x, uint32_t centre_y, uint32_t *distribution);


#endif /* ERGODICITY_H_ */
