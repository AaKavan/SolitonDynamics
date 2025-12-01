/*
PHYS305 - Term Project
C_convergence.C
Looks at the convergence of the constant of motion C at x = 5
for different step sizes using RK4.
This file uses rhs() and rk4() from functions.C
*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "header.h"
using namespace std;

int main(){
    // integration range in X is from 0 to 5
    // since we need C(X=5)
    double X_initial = 0.0;
    double X_final = 5.0;

    // Choose different numbers of steps, like we had done in HW6
    int N_values[] = {50, 100, 200, 400, 800, 1600};
    int number_of_cases = 6;

    // Output file for writing h and deltaC to
    ofstream outfile("C_convergence.txt");
    outfile << "h    deltaC_at_X5" << endl;
    // set the precision to 15 and scientific
    outfile << scientific << setprecision(15);

    for (int run = 0; run < number_of_cases; run ++){
        // set the value of N for this
        int N = N_values[run];

        // step size h = (X_final - X_intial) / N
        double h = (X_final - X_initial) / N;

        // Initial conditions at X = 0
        // f(0) = -1/2, f'(0) = 0, f''(0) = 1/4
        // Initialize u and fill it up
        double u[3];
        u[0] = -0.5;   // f
        u[1] = 0.0;    // f'
        u[2] = 0.25;   // f''

        double X = X_initial;

        // Constant of motion at X=0 (exactly zero for this problem)
        double C0 = u[2] - (1.0 + 3.0 * u[0]) * u[0];

        double C_at_5 = C0;

        // Integrate from X=0 to X=5
        for (int i = 0; i <= N; i++) {

            // Compute C(X) at this step
            double C = u[2] - (1.0 + 3.0 * u[0]) * u[0];

            if (i == N) {
                // At the last step, X should be X_final = 5
                // so set it to C
                C_at_5 = C;
            }

            // Go forward one step unless we are at the last step
            // use rk4()
            if (i < N){
                rk4(X, u, h);
                X += h;
            }
        }

        // For this problem and our initial conditions, C_exact(5) = 0, so deltaC = |C(5)|
        double deltaC = fabs(C_at_5 - C0);

        // save to the file
        outfile << h << "    " << deltaC << endl;
    }

    // Now close the file and output a statement to the terminal showing that the file 
    // has finished running
    outfile.close();
    cout << "Convegence results have been written to C_convergence.txt" << endl;

    return 0;
}
