/*
PHYS 305 - Term Project
richardson_extrapolation.C

uses RK4 to calculate f(X=5) at two different resolutions: N = 3200 and N = 6400
and performs Richardson extrapolation with an order of 4
*/


#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include "header.h"
using namespace std;

int main(){

    double X_initial = 0.0, X_final = 5.0;
    // Rk4 has order 4
    int n = 4;  

    // First, we'll do 2 cases of running rk4
    // one for N=3200 and one for N=6400
    // Case 1: N = 3200
    int N1 = 3200;
    // step size
    double h2 = (X_final - X_initial) / N1;

    double u2[3];
    u2[0] = -0.5;
    u2[1] = 0.0;
    u2[2] = 0.25;

    double X = X_initial;
    for (int i = 0; i < N1; i++){
        rk4(X, u2, h2);
        X += h2;
    }
    double f_h2 = u2[0];


    // Case 2: N = 6400
    int N2 = 6400;
    // step size
    double h3 = (X_final - X_initial) / N2;

    double u3[3];
    u3[0] = -0.5;
    u3[1] = 0.0;
    u3[2] = 0.25;

    X = X_initial;
    for (int i = 0; i < N2; i++){
        rk4(X, u3, h3);
        X += h3;
    }
    double f_h3 = u3[0];

    // 4th order Richardson Extrapolation 
    // f_R = (2^n * f(h3) - f(h2)) / (2^n - 1)
    // use pow for 2^n
    double two_power_n = pow(2.0, n);
    double f_richardson = (two_power_n * f_h3 - f_h2) / (two_power_n- 1.0);

    // estimated error in the highest resolution value that we have
    // use absolute error
    double err_estimate = fabs(f_richardson - f_h3);

    // I will write the values both to a file,
    // as well as output them to the terminal

    ofstream outfile("data_files/richardson_results.txt");
    // the precision that I've been using throughout this project
    outfile << scientific << setprecision(15);

    outfile << "h2 (N=3200)    f(h2)" << endl;
    outfile << h2 << "    " << f_h2 << endl;
    // I'll put an empty line beween the different Ns
    outfile << "\n";
    outfile << "h3 (N=6400)    f(h3)" << endl;
    outfile << h3 << "    " << f_h3 << endl;
    outfile << "\n";
    outfile << "f_Richarson" << endl;
    outfile << f_richardson << endl; 
    outfile << "estimated_error" << endl;
    outfile << err_estimate << endl;

    // Now close the file
    outfile.close();
    // print them out in the terminal as well
    // set the precision of the terminal
    cout << scientific << setprecision(15);
    cout << "f(h2 = 5 with N = 3200) = " << f_h2 << endl;
    cout << "f(h3 = 5 with N = 6400) = " << f_h3 << endl;
    cout << "f_Richardson = " << f_richardson << endl;
    cout << "Estimated Error = " << err_estimate << endl;

    // finishing print statement
    cout << "Richardson Extrapolation Results written to data_files/richardson_results.txt" << endl;

    return 0;
}