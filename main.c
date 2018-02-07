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
#include "ergodic_controller.h"
#include "domain.h"
#include "distribution.h"
#include "domain.c"
#include "distribution.c"
#include "ergodic_controller.c"


int main(void) {

    // Domain, Distribution, and ergodic controller values.
    double dist_r = 2;
    double x_centre = 75;
    double y_centre = 75;
    double domain_min[]   =   {0, 0, -M_PI};
    double domain_max[]   =   {150,150, M_PI};
    uint32_t domain_cells[] =   {10, 10, 10};
    // Construct E2.
    three_d_domain E2_;
    three_d_domain* E2 = &E2_;
    build_E2(E2, 3, domain_min, domain_max, domain_cells);
    // Construct circular distribution over E2
    double distribution_[dist_x][dist_y] = {0};
    double (*distribution)[dist_y] = &distribution_;
    build_distribution(E2, dist_r, x_centre, y_centre, distribution);

//    int n; int m;
//    for(n=0; n < dist_x; n++){
//        for(m=0; m < dist_y; m++){
//            printf("%lf ", distribution[n][m]);
//        }
//        printf("\n");
//    }

    E2_e_controller EC_;
    E2_e_controller* EC = &EC_;
    E2_controller(EC);
    double phi_[dist_x][dist_y][dist_z] = {0};
    double (*phi)[dist_y][dist_z] = &phi_;
    double complex phik_[K][K][K] = {0};
    double complex (*phik)[K][K] = &phik_;

    get_phi_coefficients(EC, E2, phi, phik);

//    int m = 0; int n = 0; int p;
//    for(n=0; n < 5; n++){
//        for(m=0; m < 5; m++){
//                for(p=0; p < 5; p++){
//                    printf("%lf ", phik[n][m][p]);
//        }
//        printf("\n");
//        }
//        printf("\n");
//    }

    double complex ck_[K][K][K] = {0};
    double complex (*ck)[K][K] = &ck_;

	return 0;
}


