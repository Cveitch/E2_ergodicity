/*
* distribution.c
*
* Created: 2018-02-06
*  Author: Conan
*/

#include "distribution.h"



void build_distribution(three_d_domain* E2, double radius, double centre_x, double centre_y, double (*distribution)[dist_y]){
    // Formula for circle is (x-a)^2 + (y-b)^2 = r^2
	double r2 = E2->x_size * E2->x_size * radius * radius;
    uint32_t dim_x = E2->x_cells;
    uint32_t dim_y = E2->y_cells;
    uint32_t i; uint32_t j;
    double a = centre_x;
    double b = centre_y;

    for(i=0; i < dim_x; i++){

        for(j = 0; j< dim_y; j++){

            double x = E2->x_min + (i-0.5)*E2->x_size;
            double y = E2->y_min + (j-0.5)*E2->y_size;
            double x1 = x - a;
            double y1 = y - b;
            double c = x1*x1 + y1*y1;
            if(c < r2){
                distribution[i][j] = 1;

            }
        }
    }
    //Normalize the matrix so that (i*j)/sum(matrix) = 1.0
    double sum = 0;
    i = 0; j = 0;
    for(i=0; i < dim_x; i++){
        for(j=0; j < dim_y; j++){
            sum += distribution[i][j];
        }
    }
    // I'm not convinced on multiplying the sum by the cell size.
    double norm = 1.0 / (sum * E2->cell_size);
    i = 0; j = 0;
    for(i=0; i < dim_x; i++){
        for(j=0; j < dim_y; j++){
            distribution[i][j] *= norm;
        }
    }

}
