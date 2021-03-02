#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
///////////////////////////////////////////////////////////////////////////////
#define X_MIN 1.0
#define X_MAX 4.0
#define EPSILON 0.0001

///////////////////////////////////////////////////////////////////////////////
double zero_point;
fstream plik_out;
///////////////////////////////////////////////////////////////////////////////
double My_function(double x){
  double y = sin(x);
  return y;
}

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
///////////////////////////////////////////////////////////////////////////////
int main(){
  plik_out.open("out.data", ios::out);

  zero_point = Zero(X_MIN, X_MAX, EPSILON, My_function); 

  cout << "Miejsce zerowe: " << zero_point << endl
       << "Epsilon: " << EPSILON << endl;

  plik_out << "Miejsce zerowe: " << zero_point << endl
	   << "Epsilon: " << EPSILON << endl;
  
  getchar(); // oczekujemy na wciśnięcie klawisza aby zakończyć

  return 0;
}

///////////////////////////////////////////////////////////////////////////////
