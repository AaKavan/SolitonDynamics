/*
PHYS305 - Term Project
f_self_convergence.C
Computes f(5) for different step sizes to demonstrate self convergence
uses rhs() and rk4() from the functions.C file
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "header.h"
using namespace std;


int main(){
    // Initial and finals values of X
    // We want f(X=5), so [0, 5]
    double X_initial = 0.0, X_final = 5.0;

    // Choose multiple N values
    // I used the same values as the hw
    int N_values[] = {50, 100, 200, 400, 800, 1600};
    int number_of_cases = 6;

    // Create a file to write the values to
    ofstream outfile("/data_files/f_self_convergence.txt");
    outfile << "h    f_at_5" << endl;
    
    // set the precision of the output to scientific and 15
    // (This is the convention that I've been using throughout this project)
    outfile << scientific << setprecision(15);

    // Start the for loop
    for (int run = 0; run < number_of_cases; run++){

        // set the value of N to the value of this run
        int N = N_values[run];

        // step size
        double h = (X_final - X_initial) / N;

        // Initial conditions
        // f(0) = -1/2, f'(0) = 0, f''(0) = 1/4
        // Initialize the array with the size 3 first
        double u[3];
        u[0] = -0.5;   // f
        u[1] = 0.0;    // f'
        u[2] = 0.25;   // f''

        // set X to its starting value
        double X = X_initial;

        // Now use rk4 to solve this
        for (int i = 0; i < N; i++) {
            rk4(X, u, h);
            X += h;
        }

        // u[0] is f(X=5)
        outfile << h << "   " << u[0] << endl;
    }

    // Now that everything has been writte, close the file
    outfile.close();
    // print a statement showing that the code has finished running
    cout << "Self convergence data has been written to /data_files/f_self_convergence.txt" << endl;

    return 0;

}