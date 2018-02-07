/*
* ergodic_controller.c
*
* Created: 2018-02-06
*  Author: Conan
*/

#include "complex.h"
#include "ergodic_controller.h"

void E2_controller(E2_e_controller* EC) {
    EC->M = K;
    EC->N = K;
    EC->P = K;
}

void get_phi_coefficients(E2_e_controller* EC, three_d_domain* E2, double (*phi)[dist_y][dist_z], double complex (*phik)[5][5]) {
    uint32_t i; uint32_t j; uint32_t k;
    uint32_t m = EC->M; uint32_t n = EC->N; uint32_t p = EC->P;
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            for(k = 0; k < p; k++){
                phik[m][n][p] = decompose_phi(EC, E2, phi, i, k, j);
            }
        }
    }
}

double complex decompose_phi(E2_e_controller* EC, three_d_domain* E2, double (*phi)[dist_y][dist_z], uint32_t a, uint32_t b, uint32_t c){

    double complex U = 0;
    uint32_t i; uint32_t j; uint32_t k;
    uint32_t m = E2->x_cells; uint32_t n = E2->y_cells; uint32_t p = E2->z_cells;
    for(i = 0; i < m; i++){
        double x = E2->x_min + ((i-0.5)* E2->x_size);
        for(j = 0; j < n; j++){
            double y = E2->y_min + ((j-0.5)* E2->y_size);
            double r = sqrt(x*x + y*y);
            double psi = atan2(y, x);
            // Curious about if this works, given that b can be
            // larger than a.
            double complex bessel = jn(a-b, c*r);
            for(k = 0; k < p; k++){
                double z = E2->z_min + ((k-0.5)* E2->z_size);
                U += phi[i][j][k] * exp(I*(m*psi+(b-a)*z)) * bessel;
            }
        }
    }
    return pow(I,b-a)*U*(E2->cell_size);
}


void get_ck_coefficients(E2_e_controller* EC, double complex(*ck)[5][5], double traj[3]){
    uint32_t i; uint32_t j; uint32_t k;
    uint32_t m = EC->M; uint32_t n = EC->N; uint32_t p = EC->P;
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            for(k = 0; k < p; k++){
                double complex fk_sum= 0;
                uint32_t a; uint32_t b;
                for(a=0; a < 3; a++){
                    double t1[3];
                    for(b=0; b < 3; b++){
                        t1[b] = traj[b];
                    }
                    fk_sum += decompose_ck(m, n, p, t1[0], t1[1], t1[2]);
                }
                ck[m][n][p] = fk_sum;
            }
        }
    }
}

double complex decompose_ck(uint32_t m, uint32_t n, uint32_t p, double x, double y, double z){
    double r = sqrt(x*x + y*y);
    double psi = atan2(y, x);
    double complex bessel = jn(m-n, p*r);
    double complex val = pow(I, n-m)*exp(I*(m*psi + (n - m)*z)) * bessel;
    return val;
}


double build_lambda(double (*lambda)[5]){
    uint32_t k1; uint32_t k2;
    for(k1 = 0; k2 < K;k1++){
        for(k2 = 0; k2 < K; k2++){
            double expon = (1 + k1*k1 + k2*k2);
            double denom = pow(1.5, expon);
            lambda[k1][k2] = 1 / denom;
        }
    }
}


