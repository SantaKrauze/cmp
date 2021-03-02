#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
///////////////////////////////////////////////////////////////////////////////
// ZMIENNE UŻYTKOWNIKA
#define T_0 0.0
#define T_MAX 20.0
#define N 100000
#define E_0_coefficient 0.1 // stosunek E_0_kin do energii niezbędnej do pełnego obrotu 
#define g 10.0
#define l 1.0
#define m 1.0
#define ALPHA_0 0.0
///////////////////////////////////////////////////////////////////////////////
//ZMIENNE PROGRAMOWE
double t[N];
double alpha[N];
double omega[N];
double E_tot[N];
double h = (T_MAX-T_0)/(N-1);
double E_0 = m*g*2.0*l* E_0_coefficient;
fstream plik;
///////////////////////////////////////////////////////////////////////////////
void Euler_D2(double x, double y_1_0, double y_2_0, double h,
		double *y_1_k, double *y_2_k,
		double (*Deriv_1)(double, double, double),
		double (*Deriv_2)(double, double, double)){
  
  *y_2_k = y_2_0+h*Deriv_2(x, y_1_0, y_2_0); //
  *y_1_k = y_1_0+h*Deriv_1(x, y_1_0, y_2_0);
}


void RK5_D2(double x, double y_1_0, double y_2_0, double h,
		double *y_1_k, double *y_2_k,
		double (*Deriv_1)(double, double, double),
		double (*Deriv_2)(double, double, double)){
  
  double k_11 = h*Deriv_1(x,y_1_0,y_2_0);
  double k_21 = h*Deriv_2(x,y_1_0,y_2_0);

  double k_12 = h*Deriv_1(x+h/2.0, y_1_0+k_11/2.0, y_2_0+k_21/2.0);
  double k_22 = h*Deriv_2(x+h/2.0, y_1_0+k_11/2.0, y_2_0+k_21/2.0);
  
  double k_13 = h*Deriv_1(x+h/2.0, y_1_0+k_12/2.0, y_2_0+k_22/2.0);
  double k_23 = h*Deriv_2(x+h/2.0, y_1_0+k_12/2.0, y_2_0+k_22/2.0);
    
  double k_14 = h*Deriv_1(x+h, y_1_0+k_13, y_2_0+k_23);
  double k_24 = h*Deriv_2(x+h, y_1_0+k_13, y_2_0+k_23);
    
  *y_1_k = y_1_0 + (k_11+2.0*k_12+2.0*k_13+k_14)/6.0;
  *y_2_k = y_2_0 + (k_21+2.0*k_22+2.0*k_23+k_24)/6.0;

}

double D_omega(double t, double alpha, double omega){ // pochodna omegi po czasie
  double deriv = -1.0*(g/l)*sin(alpha);
  return deriv;
}

double D_alpha(double t, double alpha, double omega){ // pochodna kąta po czasie
  double deriv = omega;
  return deriv;
}

//////////////////////////////////////////////////////////////////////////////
int main(){
  t[0] = T_0;
  alpha[0] = ALPHA_0;
  omega[0] = sqrt(2.0*E_0/m) / l;

  for(int i=1; i<N; i++){ t[i] = t[i-1]+h; }
  for(int i=0; i<N; i++){ 
    //Euler_D2(t[i], alpha[i], omega[i], h, &alpha[i+1], &omega[i+1], D_alpha, D_omega);
    RK5_D2(t[i], alpha[i], omega[i], h, &alpha[i+1], &omega[i+1], D_alpha, D_omega);
    E_tot[i] = m*l*l*omega[i]*omega[i]/2+m*g*l*(1.0-cos(alpha[i])); // E_kin+E_pot
  }

	
  plik.open("pendulum.data", ios::out);
  plik.precision(6);   // ilość cyfr po przecinku
  plik.setf( ios::showpoint );

  
  for(int i=0; i<N; i++){
    plik << t[i]     << "   "
	 << alpha[i]   << "   "
	 << omega[i] << "   "  //NAJLEPSZY
	 << E_tot[i] << "   "
	 << endl;
  }
  
  plik.close();
  
  return 0;
}
