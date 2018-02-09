# E2_ergodicity

Enormous thanks to Louis Dressel for his ErgodicControl.jl (https://github.com/dressel/ErgodicControl.jl).  

This is a C implementation intended for use with embedded systems, as such, utility is drastically reduced.

(Will stick everything in proper files when I figure out how it fits with RPERTs)



The main function in ergodicity.c gives a list of the structs/array required in order to go about measuring ergodicity.

Ergodicity.h gives several values that can be changed:  

The number of fourier coefficients K will default to 5, keep this unless you're sure you know how many coefficients you require for your domain.

dist_x, dist_y, and dist_z are the axes that we have discretized.  Change these values to change the number of discrete squares we are cutting the domain into.

TIME is how many discrete state changes we require.  Default is 100, that means that 100 different states will be generated.  These trajectories are not informed by the metric, they are arbitrary for testing purposes.

num_agents is the number of agents we want in our system.