/*
  PHYS305 - Term Project
  Header file for the functions written in functions.C
*/
void rhs(double X, double u[], double F[]);
void rk4(double X, double u[], double h);
double Lnk(int n, int k, double xi[], double x);
double Pn(int n, double xi[], double yi[], double x);
void write_phi_file(const char filename[], double x[], double phi[], int Nx);
