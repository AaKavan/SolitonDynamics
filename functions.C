#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>
using namespace std;

// Function for computing F(X, u) where u = {f1, f2, f3}
void rhs(double X, double u[], double F[]){
    // unpacking the current values
    double f1 = u[0];
    double f2 = u[1];
    double f3 = u[2];

    // The explanation for this system is described in the Soliton_Dynamics.pdf file
    F[0] = f2;
    F[1] = f3;
    F[2] = (1.0 + 6.0 * f1) * f2;
}


// RK4 method for a 3D system of equations
// Since we are returning multiple values, we can either use a vector, or a void.
// I'll use a void since it's simpler
void rk4(double X, double u[], double h){
    // Initialize the Ks for the rk4 method
    double k1[3], k2[3], k3[3], k4[3];
    // The full explanation for these is in the pdf file

    // k1 = F(X,u)
    rhs(X, u, k1);
    
    // k2 = F(X + h/2, u + h/2 * k1)
    // since there are multiple elements, we have to do a for loop
    // define a temp variable for inside these loops (array of size 3)
    double temp[3];
    for (int i = 0; i < 3; i++){
        temp[i] = u[i] + 0.5 * h * k1[i];
    }
    rhs(X + 0.5 * h, temp, k2);

    // k3 = F(X + h/2, u + h/2 * k2)
    for (int i = 0; i < 3; i++) {
        temp[i] = u[i] + 0.5 * h * k2[i];
    }
    rhs(X + 0.5 * h, temp, k3);

    // k4 = F(X + h, u + h * k3)
    for (int i = 0; i < 3; i++) {
        temp[i] = u[i] + h * k3[i];
    }
    rhs(X + h, temp, k4);

    // u_{n+1} = u_n + h/6 * (k1 + 2 k2 + 2 k3 + k4)
    for (int i = 0; i < 3; i++) {
        u[i] += (h / 6.0) * (k1[i] + 2.0 * k2[i] + 2.0 * k3[i] + k4[i]);
    }

}


// Calculate the Lagrange polynomial L_nk(x)
// I had written this for Homework 3, so I'll reuse it here
double Lnk(int n, int k, double xi[], double x){

    // Since the Lagrange polynomial is a product of multiple terms,
    // set result to 1
    double product = 1.0;
  
    // The formula for this is given in the lecture notes
    for (int i = 0; i <= n; i++){
      if (i != k){
        product *= (x - xi[i]) / (xi[k] - xi[i]);
      }
    }
  
    return product;
}


// Calculate the n-th degree Lagrange interpolant Pn(x)
// Similarly, this was written in HW3
double Pn(int n, double xi[], double yi[], double x){

    // Since the interpolant is a sum of the different terms,
    // set it to 0.0 and add on to it
    double sum = 0.0;
  
    // From the lecture notes: Pn is the sum of Lnk(x)*f(x_k)
    // from k = 0 to k = n
    for (int k = 0; k <= n; k++){
      sum += yi[k] * Lnk(n, k, xi, x);
    }
  
    return sum;
}

// Helper function for writing the values of phi to a file
// make the filename[] a const char so it doesn't throw errors while compiling
void write_phi_file(const char filename[], double x[], double phi[], int Nx){

    // Write to a file in the data_files directory
    ofstream outfile("data_files/" + string(filename));

    // set the precision to a scientific with 15
    outfile << scientific << setprecision(15);

    // for loop for writing the values of x and phi to the file
    for (int i = 0; i < Nx; i++){
        outfile << x[i] << "    " << phi[i] << endl;
    }

    // close the file
    outfile.close();

}