/*
* ergodicity.h
*
* Created: 2018-01-28
*  Author: Conan
*/

#include <stdint.h>
#include "domain.h"

#ifndef ERGODICITY_H_
#define ERGODICITY_H_



// These are hardcoded values. This is janky, but we can't dynamically
// assign values to multi-dim array due to bare metal restrictions on
// malloc.
#define dist_x 10
#define dist_y 10       // Number of discrete squares domain cut into per axis.
#define dist_z 10

#define K 5             // Number of Fourier coefficients.

#define TIME 100        // Total number of states

#define num_agents  1   // Number of agents in system



void generate_test_trajectory(double traj[TIME][3]);

#endif /* ERGODICITY_H_ */
