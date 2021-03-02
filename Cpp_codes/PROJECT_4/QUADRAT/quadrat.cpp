#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
//////////////////////////////////////////////////////////////////////////////
// ZMIENNE DO MODYFIKACJI PRZEZ UZYTKOWNIKA
#define NH_0 1.0
#define X_MIN 0.0
#define X_MAX 1.0
#define N 15
#define I_FACT 0.1
//////////////////////////////////////////////////////////////////////////////
// ZMIENNE PROGRAMOWE
double nh[N];
double square[N];

fstream plik;
//////////////////////////////////////////////////////////////////////////////
// FUNKCJE

double My_function(double x){
  double y = sin(x);
  return y;
}

double Simpson(double x_min, double x_max, double n,  double (*Function)(double)){
  double h = (x_max - x_min) / (2.0 * n );
  double simpson = 0.0;
  double x = x_min+h;
  
  for(int i=0; i<n; i++){
    simpson = simpson + h*( Function(x+h) + 4.0*Function(x) + Function(x-h) ) / 3.0;
    x = x+2.0*h;
  }

  return simpson;
}
/////////////////////////////////////////////////////////////////////////////
// FUNKCJA GLOWNA

int main(){
  nh[0] = NH_0;
  for(int i=1; i<N; i++){ nh[i] = nh[i-1]* I_FACT; }
  for(int i=0; i<N; i++){ square[i] = Simpson(X_MIN, X_MAX, nh[i], My_function); }

  plik.open("quadrat.data", ios::out);

  for(int i=0; i<N; i++){
    plik << log10( nh[i] ) << "   "
	 << square[i] << "   "
	 << endl;
  }
  
  plik.close();
  return 0;
}
