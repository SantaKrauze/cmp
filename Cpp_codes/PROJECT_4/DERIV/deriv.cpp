#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
//////////////////////////////////////////////////////////////////////////////
// ZMIENNE DO MODYFIKACJI PRZEZ UZYTKOWNIKA
#define H 0.01
#define N 1000
//////////////////////////////////////////////////////////////////////////////
// ZMIENNE PROGRAMOWE
double x[N];
double y[N];
double y_prim[N];
double y_prim_prim[N];

fstream plik;
//////////////////////////////////////////////////////////////////////////////
// FUNKCJE

double My_function(double x){
  double y = sin(x);
  return y;
}

double Fp3(double x, double h,  double (*Function)(double)){
  double fp3 = ( Function(x+h) - Function(x-h) ) /( 2.0 * h );
  return fp3;
}

double Fpp3(double x, double h,  double (*Function)(double)){
  double fpp3 = ( Function(x+h) + Function(x-h) -2.0 * Function(x) ) / (h*h); 
  return fpp3;
}
/////////////////////////////////////////////////////////////////////////////
// FUNKCJA GLOWNA

int main(){
  for(int i=0; i<N; i++){ x[i] = i*H; }
  for(int i=0; i<N; i++){ y[i] = My_function( x[i] ); }
  for(int i=1; i<N-1; i++){ y_prim[i] = Fp3( x[i], H, My_function); }
  for(int i=1; i<N-1; i++){ y_prim_prim[i] = Fpp3( x[i], H, My_function); }

  y_prim[0] = y_prim[1];
  y_prim[N-1] = y_prim[N-2];
  y_prim_prim[0] = y_prim_prim[1];
  y_prim_prim[N-1] = y_prim_prim[N-2];

  plik.open("deriv.data", ios::out);

  for(int i=0; i<N; i++){
    plik << x[i] << "   "
	 << y[i] << "   "
	 << y_prim[i] << "   "
	 << y_prim_prim[i] << "   "
	 << endl;
  }

  plik.close();
  return 0;
}
