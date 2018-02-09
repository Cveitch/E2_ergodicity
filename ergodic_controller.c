/*
* ergodic_controller.c
*
* Created: 2018-02-06
*  Author: Conan
*/

#include "complex.h"
#include "ergodic_controller.h"
#include "ergodicity.h"

void E2_controller(E2_e_controller* EC) {
    EC->M = K;
    EC->N = K;
    EC->P = K;
}

// Get the coefficients of the domain distribution
void get_phi_coefficients(E2_e_controller* EC, three_d_domain* E2, double (*phi)[dist_y][dist_z], double complex (*phik)[K][K]) {
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

// Get the agents trajectory coefficients
void get_ck_coefficients(E2_e_controller* EC, double complex(*ck)[K][K], double traj[TIME][3], uint32_t state){
    uint32_t i; uint32_t j; uint32_t k;
    uint32_t m = EC->M; uint32_t n = EC->N; uint32_t p = EC->P;
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            for(k = 0; k < p; k++){
                double complex fk_sum= 0;
                uint32_t b;
                for(b=0; b < state; b++){
                    fk_sum += decompose_ck(i, j, k, traj[b][0], traj[b][1], traj[b][2]);
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
    double complex val = cpow(I, n-m)*cexp(I*(m*psi + (n - m)*z)) * bessel;
    return val;
}


double build_lambda(E2_e_controller* EC, double (*lambda)[K][K]){
    uint32_t k1; uint32_t k2; uint32_t k3;
    uint32_t m = EC->M; uint32_t n = EC->N; uint32_t p = EC->P;
    for(k1 = 0; k1 < m;k1++){
        for(k2 = 0; k2 < n; k2++){
            for(k3 = 0; k3 < p; k3++){
                double expon = (1 + k1*k1 + k2*k2 + k3*k3);
                double denom = expon*expon;
                lambda[k1][k2][k3] = 1 / denom;
            }
        }
    }
}

// Returns a value that explains how ergodic ck is when compared to phi
double ergodicity_value(E2_e_controller* EC, double complex (*phik)[dist_y][dist_z], double complex(*ck)[K][K], double (*lambda)[K][K]){
    double complex val = 0;
    uint32_t m = EC->M; uint32_t n = EC->N; uint32_t p = EC->P;
    int i; int j; int k;
    for(i = 0; i < m; i++){
        for(j = 0; j < n; j++){
            for(k = 0; k < p; k++){
                double complex d = phik[i][j][k] - ck[i][j][k];
                double dr = creal(d);
                double complex di = cimag(d);
                val += lambda[i][j][k] * (dr*dr + di*di);
            }
        }
    }
    double ergodic_score = creal(val);

    return ergodic_score;
}


// Takes a list of coefficients and averages them, then finds the
// ergodicity score of the system.  This function is for leaders
void system_ergodicity_value(double complex (*agent_coefficients)[K][K][K], uint32_t agents, double complex (*ck_s)[K][K]){
    uint32_t i; uint32_t j; uint32_t k; uint32_t l;
    for(i=0; i < agents; i++){
        for(j=0; j < K; j++){
            for(k=0; k < K; k++){
                for(l=0; l < K; l++){
                    ck_s[j][k][l] += agent_coefficients[i][j][k][l];
                }
            }
        }
    }
    i = 0; j = 0; k = 0;
    for(i=0; i < K; i++){
        for(j=0; j < K; j++){
            for(k=0; k < K; k++){
                    ck_s[i][j][k] /= agents;
            }
        }
    }

}

