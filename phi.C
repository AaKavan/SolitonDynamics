/*
  PHYS305 - Term Project
  phi.C
  Calculates phi(x,t) = f(x-t) for t = 1, 2, 3, 4, 5
  using a third order Lagrange interpolation
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include "header.h"
using namespace std;

int main(){
  // define a max size array for N
  // since we took h = 0.001 and X_final = 20, there should be 20001 rows
  // to be safe, define a constant N max
  // could have used vectors, but I don't want to make it more convoluted
  const int MAXN = 30000;

  // initialize our arrays
  double X[MAXN], f[MAXN], fp[MAXN], fpp[MAXN], C[MAXN], err[MAXN];

  // Load the forward solutions (X >= 0)
  ifstream infile("kdv_forward_solution.txt");

  // skip header line
  string header;
  getline(infile, header);   

  int N_forward = 0;

  while (infile >> X[N_forward] >> f[N_forward] >> fp[N_forward] >> fpp[N_forward]
	 >> C[N_forward] >> err[N_forward]) {N_forward++;}

  // close it now 
  infile.close();


  // Build the full interval using the symmetry of the problem

  // initalize the full interval arrays
  double X_full[2 * MAXN], f_full[2 * MAXN];

  // This will be used in the for loop that I'll do for filling f_full
  int N_full = 0;

  // First let's do the negative side, and then the positive side
  // be careful to skip x = 0 to avoid it being duplicated
  // start the loop backwards
  for (int i = N_forward - 1; i >= 1; i--) {
    X_full[N_full] = -X[i];
    f_full[N_full] =  f[i];
    N_full++;
  }


  // Positive side
  for (int i = 0; i < N_forward; i++) {
    X_full[N_full] = X[i];
    f_full[N_full] = f[i];
    N_full++;
  }


  // Now we can get to calculating phi(x,t) for t = 1, ..., 5
  // initalize an array for the values of t
  double t_values[6] = {0, 1, 2, 3, 4, 5};

  // Since we want phi(x,t) for x in [-10, 10], define the interval 
  double x_inital = -10.0, x_final = 10.0;

  // choose a step size of 0.01
  // I'll make it smaller than the one I ran rk4 for (which was 0.001) 
  // in order to use interpolation
  double dx = 0.01;

  // make the grid now
  // + 1 to include everything
  int Nx = int((x_final - x_inital)/dx) + 1;

  // Initalize the x grid now and file it up
  double x_vals[MAXN];
  for (int i = 0; i < Nx; i++){
    x_vals[i] = x_inital + i * dx;
  }

  // Initalize the phi(x,t) values
  double phi[MAXN];

  // Now, calculate phi(x,t) = f(x-t) for each t and 
  // write the values to a file
  for (int t_run = 0; t_run < 6; t_run++){
    // set the value of t to the value of this run
    double t = t_values[t_run];

    for (int i = 0; i < Nx; i++){
      // define X_query; the point we want to find using interpolation
      double X_query = x_vals[i] - t;

      // find the index in X_full that is closest to the X_query
      // Then we'll use it for interpolation
      int idx = 0;
      for (int j = 0; j < N_full - 1; j++){
	// Interval where X_query is, so
	// X_fill[j] <= X_query <= X_full[j+1]
	if (X_full[j] <= X_query && X_query <= X_full[j+1]){
	  // set the index (idx) to this index (j), and 
	  // break the for loop
	  idx = j;
	  break;
	}
      }  // <-- end of j-loop

      // Now take 4 points around idx for the 
      // 3rd order lagrange interpolation
      int i0 = idx - 1;
      int i1 = idx;
      int i2 = idx + 1;
      int i3 = idx + 2;

      // There will be issues at the boundries, so
      // we can make two if statements for those cases
      // left boundry point
      if (i0 < 0) {
	i0 = 0; i1 = 1; i2 = 2; i3 = 3;
      }
      // right bounrdry point
      if (i3 >= N_full){
	i3 = N_full - 1; i2 = i3 - 1; i1 = i3 - 2; i0 = i3 - 3;
      }
                
      // build the xi and yi arrays
      double xi[4] = { X_full[i0], X_full[i1], X_full[i2], X_full[i3] };
      double yi[4] = { f_full[i0], f_full[i1], f_full[i2], f_full[i3] };
                
      // Use the nth degree lagrange interpolant Pn (written in functions.C)
      phi[i] = Pn(3, xi, yi, X_query);

    } // <-- end of i-loop


    // Now write phi(x,t) to text files
    // since there are only 5 cases (t = 0, ..., 5), I will hardcode the values
    // otherwise I could use strings to write the values

    if (t == 0) write_phi_file("data_files/phi_t0.txt", x_vals, phi, Nx);
    if (t == 1) write_phi_file("data_files/phi_t1.txt", x_vals, phi, Nx);
    if (t == 2) write_phi_file("data_files/phi_t2.txt", x_vals, phi, Nx);
    if (t == 3) write_phi_file("data_files/phi_t3.txt", x_vals, phi, Nx);
    if (t == 4) write_phi_file("data_files/phi_t4.txt", x_vals, phi, Nx);
    if (t == 5) write_phi_file("data_files/phi_t5.txt", x_vals, phi, Nx);

    // now everything should be written to the text files
  }

  // output a statement in the terminal to make sure that the code has finished running
  cout << "phi(x,t) files have been created for t=0,1,2,3,4,5" << endl;

  return 0;
}
