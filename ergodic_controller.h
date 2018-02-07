/*
* ergodic_controller.h
*
* Created: 2018-02-06
*  Author: Conan
*/

#ifndef ERGODIC_CONTROLLER_H_INCLUDED
#define ERGODIC_CONTROLLER_H_INCLUDED

#define K 5

// Ergodicity information
typedef struct E2_e_controller{
	uint32_t M;						// M, N, P are directional indices
	uint32_t N;
	uint32_t P;
}E2_e_controller;


void get_phi_coefficients(E2_e_controller* EC, three_d_domain* E2, double (*phi)[dist_y][dist_z], double complex (*phik)[5][5]);

double complex decompose_phi(E2_e_controller* EC, three_d_domain* E2, double (*phi)[dist_y][dist_z], uint32_t a, uint32_t b, uint32_t c);
void E2_controller(E2_e_controller* EC);
double construct_phik(double (*phi)[dist_y][dist_z]);
double complex decompose_ck(uint32_t m, uint32_t n, uint32_t p, double xs, double y, double z);
void get_ck_coefficients(E2_e_controller* EC, double complex (*ck)[5][5], double traj[3]);
double build_lambda(double (*lambda)[5]);

#endif // ERGODIC_CONTROLLER_H_INCLUDED
