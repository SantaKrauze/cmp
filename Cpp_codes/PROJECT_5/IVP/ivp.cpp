#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
///////////////////////////////////////////////////////////////////////////////
// ZMIENNE UŻYTKOWNIKA
#define X_0 0.0
#define X_N 1.0
#define Y_0 1.0
#define N 1000
///////////////////////////////////////////////////////////////////////////////
//ZMIENNE PROGRAMOWE
double x[N];
double y_E[N];
double y_RK5[N];
double y_AB3[N];
double h = (X_N-X_0)/(N-1);
fstream plik;
///////////////////////////////////////////////////////////////////////////////
double Euler(double x, double y_0, double h, double (*F)(double, double) ){
  double y_1 = y_0 + h*F(x, y_0);
  return y_1;
}

double AB3( double x, double y_1, double y_2, double y_3, double h, double (*F)(double, double)){
  double y_4 = y_3+h*(5.0*F(x-2.0*h, y_1)-16.0*F(x-h,y_2)+23.0*F(x,y_3))/12.0;
  //  double y_0 = y_1-h*(5.0*F(x-2.0*h, y_1)-16.0*F(x-h,y_2)+23.0*F(x,y_3))/12.0;

  return y_4;
  //return y_0;
}

double RK5(double x, double y_0, double h, double (*F)(double, double) ){
  double k_1 = h*F(x,y_0);
  double k_2 = h*F(x+h/2.0,y_0+k_1/2.0);
  double k_3 = h*F(x+h/2.0,y_0+k_2/2.0);
  double k_4 = h*F(x+h,y_0+k_3);
  double y_1 = y_0 + (k_1+2.0*k_2+2.0*k_3+k_4)/6.0;
  return y_1;
}

double Right_side_function(double x, double y){
  double out = 1.0*y;
  return out;
}
//////////////////////////////////////////////////////////////////////////////
int main(){
  for(int i=0; i<N; i++){ x[i]=X_0+h*i; }

  y_E[0]=Y_0;
  for(int i=0; i<N-1; i++){ y_E[i+1] = Euler(x[i],y_E[i],h,Right_side_function); }

  y_RK5[0]=Y_0;
  for(int i=0; i<N-1; i++){ y_RK5[i+1] = RK5(x[i],y_E[i],h,Right_side_function); }

  y_AB3[0]=Y_0;
  y_AB3[1]=y_RK5[1];
  y_AB3[2]=y_RK5[2];
  for(int i=2; i<N-1; i++){
    y_AB3[i+1] = AB3(x[i],y_AB3[i-2], y_AB3[i-1], y_AB3[i], h, Right_side_function);
  }

  plik.open("ivp.data", ios::out);
  plik.precision(10);
  plik.setf( ios::showpoint );

  
  for(int i=0; i<N; i++){
    plik << x[i]     << "   "
	 << y_E[i]   << "   "
	 << y_AB3[i] << "   "  //NAJLEPSZY
	 << y_RK5[i] << "   "
	 << endl;
  }
  
  plik.close();
  
  return 0;
}
