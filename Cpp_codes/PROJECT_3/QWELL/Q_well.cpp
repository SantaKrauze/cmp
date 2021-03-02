#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
///////////////////////////////////////////////////////////////////////////////
#define V_0 10.0   // głębokość studni potencjału - energia potencjalna
#define A   2.0   // szerokość studni potencjału
#define EPSILON V_0 / 100000.0 // precyzja wyznaczenia energii
#define DELTA_E V_0 / 100.0  // przedziały energii, w każdym szukamy max 1 miejsca zerowego
///////////////////////////////////////////////////////////////////////////////
double h = 0.99*V_0/(100-1);
int counter = 0;
fstream plik_out_1;
fstream plik_out_2;

///////////////////////////////////////////////////////////////////////////////
double Zero(double x_min, double x_max, double epsilon, double (*Function)(double)){
  double x_medium;

  if( Function(x_min) == 0 ) return x_min;
  if( Function(x_max) == 0 ) return x_max;

  while( (x_max-x_min) > epsilon){
    x_medium = (x_max+x_min)/2.0;
    if( Function(x_min)*Function(x_medium) < 0 ) x_max = x_medium;
    else x_min = x_medium;
  }

  return x_medium;
}

double F_even( double E ){
  double k = sqrt( 2.0*(V_0+E) );
  double F = sin( k*A/2.0 ) - cos( k*A/2.0 ) * sqrt( -2.0*E )/k;

  return F;
}

double F_odd( double E ){
  double k = sqrt( 2.0*(V_0+E) );
  double F = sin( k*A/2.0 ) + cos( k*A/2.0 ) * k/sqrt( -2.0*E );

  return F;
}

///////////////////////////////////////////////////////////////////////////////
int main(){
  double E, E_0;
  plik_out_1.open("out_1.data", ios::out);
  plik_out_2.open("out_2.data", ios::out);
  plik_out_1.precision(7);      // ustawiamy ilość cyfr po przecinku
  plik_out_2.precision(10);     // ustawiamy ilość cyfr po przecinku
  
  //zapisujemy do pliku wartości funkcji łączenia - gdy 0 to gładkie łączenie

  E = -V_0 + 0.001*V_0; 
  while( E < 0 ){
    plik_out_1 << E         << "   "
	       << F_even(E) << "   "
	       << F_odd(E)  << "   "
	       << endl;
    E = E + DELTA_E;
  }

  // szukamy energii przy których występują gładkie łączenia na granicy studni


  E = -V_0 + 0.001*V_0;
  while( E < 0 ){
    
    if( F_even(E)*F_even(E+DELTA_E) < 0 ){
      counter++;
      E_0 = Zero(E, E+DELTA_E, EPSILON, F_even);
      plik_out_2 << counter << " " << E_0 << endl;
    }

    if( F_odd(E)*F_odd(E+DELTA_E) < 0 ){
      counter++;
      E_0 = Zero(E, E+DELTA_E, EPSILON, F_odd);
      plik_out_2 << counter << " " << E_0 << endl;
    }

    E = E + DELTA_E;
  }

  plik_out_1.close();
  plik_out_2.close();
  return 0;
}

///////////////////////////////////////////////////////////////////////////////
