/*
* main.c
*
* Created: 2018-01-28
*  Author: Conan
*/


#include "ergodicity.h"
#include <stdio.h>
#include <complex.h>
#include <math.h>




int main(void) {

	printf("hello world");

    // Constructing domain 1.5mx1.5m, 10x10 cells
    double domain_min[]   =   {0, 0, -M_PI};
    double domain_max[]   =   {1.5,1.5, M_PI};
    double domain_cells[] =   {10, 10, 10};

    three_d_domain E2_;
    three_d_domain* E2=&E2_;
    build_E2(E2, 3, domain_min, domain_max, domain_cells);

    uint32_t distribution_[dist_x][dist_y];
    uint32_t* distribution = &distribution_;

    build_distribution(E2, dist_r, x_centre, y_centre, distribution);


	return 0;
}



void get_phi_coefficients() {

}






void build_controller(uint32_t k, struct three_d_domain E2 ) {

}




// For now, all of this is hardcoded to three dimensions.
// This is a bare metal restriction, since we can't use malloc.
void build_E2(three_d_domain* E2, uint32_t dim, double min[], double max[], double cells[]) {
	uint32_t i = 0;
	E2->x_len = max[i] - min[i];
	E2->x_cell_len = (max[i] - min[i]) / cells[i];
	E2->x_min = min[i];
	E2->x_max = max[i];
	E2->x_cell = cells[i];

	i++;
	E2->y_len = max[i] - min[i];
	E2->y_cell_len = (max[i] - min[i]) / cells[i];
	E2->y_min = min[i];
	E2->y_max = max[i];
	E2->y_cell = cells[i];

	i++;
	E2->z_len = max[i] - min[i];
	E2->z_cell_len = (max[i] - min[i]) / cells[i];
	E2->z_min = min[i];
	E2->z_max = max[i];
	E2->z_cell = cells[i];

	E2->cell_size = 1.0;
	int j;
	for (j = 0; j < i; j++) {
		E2->cell_size *= (max[j] - min[j]) / cells[j];
	}
}




void build_distribution(three_d_domain* E2, uint32_t radius, uint32_t centre_x, uint32_t centre_y, uint32_t *distribution){
	uint32_t r2 = radius * radius;
	//distribution[x][y];

}








//
//
//
//
//
////HOW TO USE COMPLEX.H
////
////double complex z1 = 1.0 + 3.0 * I;
////double complex z2 = 1.0 - 4.0 * I;
////
////printf("Working with complex numbers:\n\v");
////
////printf("Starting values: Z1 = %.2f + %.2fi\tZ2 = %.2f %+.2fi\n", creal(z1), cimag(z1), creal(z2), cimag(z2));
////
////double complex sum = z1 + z2;
////printf("The sum: Z1 + Z2 = %.2f %+.2fi\n", creal(sum), cimag(sum));
////
////double complex difference = z1 - z2;
////printf("The difference: Z1 - Z2 = %.2f %+.2fi\n", creal(difference), cimag(difference));
////
////double complex product = z1 * z2;
////printf("The product: Z1 x Z2 = %.2f %+.2fi\n", creal(product), cimag(product));
////
////double complex quotient = z1 / z2;
////printf("The quotient: Z1 / Z2 = %.2f %+.2fi\n", creal(quotient), cimag(quotient));
////
////double complex conjugate = conj(z1);
////printf("The conjugate of Z1 = %.2f %+.2fi\n", creal(conjugate), cimag(conjugate));
