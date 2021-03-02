#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
//////////////////////////////////////////////////////////////////////////////
// ZMIENNE DO MODYFIKACJI PRZEZ UZYTKOWNIKA
#define Y_MIN -5.0
#define Y_MAX 5.0
#define N 500
#define N_INT 100
#define LAMBDA 1.0
#define AMPLITUDE 10.0
#define D 10.0
//////////////////////////////////////////////////////////////////////////////
// ZMIENNE PROGRAMOWE
double k = 2.0 * 3.1415 / LAMBDA;
double h = (Y_MAX - Y_MIN)/(N-1);

double y[N];
double complex_amplitude[N];

fstream plik;
//////////////////////////////////////////////////////////////////////////////
// FUNKCJE
double Real(double x, double y){
  double r = sqrt( D*D+(y-x)*(y-x) );
  double amplitude = AMPLITUDE * cos(k*r)/sqrt(r);

  return amplitude;
}

double Imag(double x, double y){
  double r = sqrt( D*D+(y-x)*(y-x) );
  double amplitude = AMPLITUDE * sin(k*r)/sqrt(r);

  return amplitude;
}

double Simpson(double x_min, double x_max, double y, double n,  double (*Function)(double, double)){
  double h = (x_max - x_min) / (2.0 * n );
  double simpson = 0.0;
  double x = x_min+h;
  
  for(int i=0; i<n; i++){
    simpson = simpson + h*( Function(x+h, y) + 4.0*Function(x, y) + Function(x-h, y) ) / 3.0;
    x = x+2.0*h;
  }

  return simpson;
}
/////////////////////////////////////////////////////////////////////////////
// FUNKCJA GLOWNA

int main(){
  double real, imag;

  for(int i=0; i<N; i++){ y[i] = i*h + Y_MIN; }
  
  for(int i=0; i<N; i++){
    real = Simpson(Y_MIN, Y_MAX, y[i], N_INT, Real);
    imag = Simpson(Y_MIN, Y_MAX, y[i], N_INT, Imag);
    complex_amplitude[i] = real*real + imag*imag;
  }

  plik.open("wave.data", ios::out);

  for(int i=0; i<N; i++){
    plik << y[i] << "   "
	 << complex_amplitude[i] << "   "
	 << endl;
  }

  plik.close();
  
  return 0;
}
