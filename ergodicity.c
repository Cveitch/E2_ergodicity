/*
* ergodicity.c
*
* Created: 2018-01-28
*  Author: Conan
*/

// Darkshik, don't ask.  I know I should only have to include the h file
// For some reason it wouldn't compile properly unless I did it this way.
// I blame Codeblocks.
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
#include <stdlib.h>
#include <time.h>


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
    double phi_[dist_x][dist_y][dist_z] = {0};
    double (*phi)[dist_y][dist_z] = &phi_;
    build_distribution(E2, dist_r, x_centre, y_centre, phi);

    // Construct ergodic controller, handles decomposition
    E2_e_controller EC_;
    E2_e_controller* EC = &EC_;
    E2_controller(EC);

    // Find distribution coefficients
    double complex phik_[K][K][K] = {0};
    double complex (*phik)[K][K] = &phik_;
    get_phi_coefficients(EC, E2, phi, phik);

    // Find trajectory coefficients
    double complex ck_[K][K][K] = {0};
    double complex (*ck)[K][K] = &ck_;

    // Construct a trajectory
    double trajectory[TIME][3] = {0};
    generate_test_trajectory(trajectory);
    uint32_t time_elapsed = 3;
    get_ck_coefficients(EC, ck, trajectory, time_elapsed);

    // Use the ergodicity metric to compare trajectory
    // and distribution coefficients
    double lambda_[K][K][K] = {0};
    double (*lambda)[K][K] = &lambda_;
    build_lambda(EC, lambda);
    double score = ergodicity_value(EC, phik, ck, lambda);

    printf("%lf \n", score);

	return 0;
}




void generate_test_trajectory(double traj[TIME][3]){
    uint32_t i; uint32_t j; uint32_t k;
    srand ( time(NULL) );
    for(i=0; i < TIME; i++){
        for(j=0; j < 3; j++){
            uint32_t coinflip = rand() % 2;
            if(coinflip == 2 || traj[i][0] > 6 || traj[i][1] > 6 || traj[i][2] > 6){
                traj[i][0] -= rand() % 5;
                traj[i][1] -= rand() % 5;
                traj[i][2] -= rand() % 2;
            }
            else{
                traj[i][0] += rand() % 5;
                traj[i][1] += rand() % 5;
                traj[i][2] += rand() % 2;
            }

        }
    }
}




