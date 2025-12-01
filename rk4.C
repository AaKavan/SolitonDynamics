/*
PHYS305 - Term Project
rk4.C
Main file that integrates the KdV reduced ODE using RK4
This file uses rhs() and rk4() that were implemented in functions.C
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "header.h"
using namespace std;

int main(){

    // integration range in X
    // Since we showed that solutions are symmetric, we can plot [-20, 20] using the [0, 10] interval
    double X_initial = 0.0;
    double X_final = 20.0;

    // step size
    // set it to an optional h for now, we can change it later
    double h = 0.001;

    // Number of steps
    // use int() since the X_final - X_initial/h might not be an integer
    int N = int((X_final - X_initial)/h);

    // initalize u
    double u[3];

    // Initial conditions
    // f(0) = -1/2, f'(0) = 0, f''(0) = 1/4
    u[0] = -0.5;   // f
    u[1] = 0.0;    // f'
    u[2] = 0.25;   // f''

    double X = X_initial;

    // Output file for writng the values to
    ofstream outfile("data_files/kdv_forward_solution.txt");
    outfile << "X    f(X)    f'(X)    f''(X)    C(X)    absolute_error" << endl;
    // set it to scientific precision with 15
    outfile << scientific << setprecision(15);

    // Calculate the inital C(X) (constant of motion)
    double C0 = u[2] - (1.0 + 3.0 * u[0]) * u[0];

    // Start the main loop for integration
    for (int i = 0; i <= N; i++){
        // Calculate C for this iteration
        // Ideally, it should be completely constant throughout the problem
        double C = u[2] - (1.0 + 3.0 * u[0]) * u[0];

        // Compute the absolute error of C since C0 = 0
        double absolute_error = fabs(C - C0);

        // save the current step to the file
        outfile << X << "    " << u[0] << "    " << u[1] << "    " << u[2] << "    "
            << C << "    " << absolute_error << endl;
        
        // run rk4 now
        rk4(X, u, h);

        // Go forward for one step h in X and initalize the next loop
        X += h;
    }

    // Now that everything has been written to the file,
    // close it
    outfile.close();
    
    // Output something in the terminal indicating that the code has finished running
    cout << "Integration is complete. Results have been written to kdv_forward_solution.txt" << endl;

    return 0;
}