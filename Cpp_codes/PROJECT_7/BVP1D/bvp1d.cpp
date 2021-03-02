#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// zmienne użytkownika
#define R_0 0.0          // początek obliczeń
#define R_MAX 10.0       // koniec obliczeń          
#define Y_0 0.0          // potencjał dla R = R_0
#define N 10000          // ilość próbek

////////////////////////////////////////////////////////////////////////////////
// zmienne programowe
double r[N];                    // promień
double fi[N];                   // zmienna pomocnicza - ułatwia rozwiązanie rów róż
double FI[N];                   // potencjał w funkcji promienia
double analytical_fi[N];        // analitycznie obliczony potencjał 
double h = (R_MAX - R_0)/(N-1); // krok obliczeń
fstream plik;                   // plik na dane wyjściowe

////////////////////////////////////////////////////////////////////////////////
// funkcje programowe
double Numerow(double x, double y_1, double y_2, double h,
	       double (*K2)(double), double (*S)(double)){
  
  double C_1 = 1.0+h*h*K2(x+h)/12.0;
  double C_2 = 2.0*(1.0-5.0*h*h*K2(x)/12.0);
  double C_3 = 1.0+h*h*K2(x-h)/12.0;
  double Right_side = h*h/12.0*(S(x+h)+10.0*S(x)+S(x-h));

  double y_3 = (Right_side-C_1*y_1+C_2*y_2)/C_3;       
  //  double y_0 = (Right_side-C_3*y_3+C_2*y_2)/C_1;     // można liczyć w drugą stronę

  return y_3;
  // return y_0;                                          
}

double K2(double x){                                     // funkcja
  double k_2 = 0.0;
  return k_2;
}

double S(double x){                                      // funkcja
  double right_side = -x*exp(-x)/2.0;
 return right_side;
}

double Analytical_solution(double x){
  double Fi = 1.0 - 0.5*(x+2.0)*exp(-x);
  return Fi;
}

///////////////////////////////////////////////////////////////////////////////
// funkcja główna programu
int main(){

  fi[0] = Y_0;
  fi[1] = 0.5*h;
  for(int i=0; i<N; i++){ r[i] = R_0+i*h; }
  for(int i=2; i<N; i++){ fi[i] = Numerow(r[i],fi[i-2],fi[i-1],h,K2,S); }
  for(int i=1; i<N; i++){ FI[i] = fi[i]/r[i]; }
  for(int i=0; i<N; i++){ analytical_fi[i] = Analytical_solution(r[i]); }
  FI[0] = FI[1];
    
  plik.open("BVP1D.data", ios::out);
  for(int i=0; i<N; i++){
    plik << r[i]             << "   "
	 << fi[i]            << "   "
	 << FI[i]            << "   "
	 << analytical_fi[i] << "   "
	 << endl;
  }
  plik.close();
}
