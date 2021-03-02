#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
//////////////////////////////////////////////////////////////////////////////
#define N 100             // ilość próbek w każdej serii
#define R_0 2.0           // promień wewnętrznej powłoki kondensatora
#define R_N 10.0          // promien zewnętrznej powłoki kondensatora
#define omega 1.0         // współczynnik "miksowania"
#define epsilon 0.00001   // wartość zmiany energii dla kolejnych kroków przy której skończymy 
#define FI_0 2.0          // potencjał powłoki wewnętrznej
#define FI_N 10.0         // potencjał powłoki zewnętrznej
//////////////////////////////////////////////////////////////////////////////
double h = (R_N-R_0)/N;          // krok numeryczny
double FI[N];                    // tablica potencjału wewnątrz kondensatora
double FI_new[N];                // tymczasowa tablica potencjału
double F_value=0;                // wartosć funkcjonału dla FI_new
double F_value_old = 1000000;    // wartosc funkcjonału starszego potencjału 
double r[N];                     // tablica promieni, poza r[0] i r[N-1] zbędna
long long int step=0;            // licznik kroków przy których osiągnęliśmy zakładaną dokładność
                                 // wyznaczenia trajektorii funkcji potencjału
fstream plik_potential;          // tu zapisujemy przebieg optymalnego potencjału w kondensatorze
fstream plik_f_value;            // zapisujemy kolejne wartości dla wcześniejszych funkcjonałów 
//////////////////////////////////////////////////////////////////////////////
void Init(){                                           // inicjujemy zmienne
  r[0]        = R_0;                                   // ustalamy warunki początkowe
  r[N-1]      = R_N;
  FI[0]       = FI_0;
  FI[N-1]     = FI_N;
  FI_new[0]   = FI_0;
  FI_new[N-1] = FI_N;
  
  for(int i=0;i<N;i++){
    FI[i] = FI[0] + (FI[N-1]-FI[0])/(r[N-1]-r[0])*i*h; //funkcja liniowa
  }
}

void Gauss_Seidle_substitution(){
  for(int i=1;i<N-1;i++){
    FI_new[i] = (FI[i+1]+FI[i-1])/2.0 + h*(FI[i+1]-FI[i-1])/4.0/(r[0]+h*i);
  }
}

void Mixing(){
  for(int i=0;i<N;i++){
    FI[i] = FI_new[i]*omega + FI[i]*(1.0-omega);
  }
}

void Calculate_functional_value(){
  F_value=0;

  for(int i=1;i<N;i++){
    F_value = F_value + (FI[i]-FI[i-1])*(FI[i]-FI[i-1]) * (r[0]+i*h-h/2);
  }
  
  F_value = F_value/2.0/h;

  plik_f_value << step    << " "
	       << F_value << " "
	       << endl;
  step++;
}

void Write_potential(){
  for(int i=0; i<N; i++){
    plik_potential << r[0]+h*i << " "
		   << FI[i]    << " "
		   << endl;
  }
}
//////////////////////////////////////////////////////////////////////////////
int main(){
  plik_potential.open("potential.data", ios::out);
  plik_f_value.open("f_value.data", ios::out);

  Init();

  while( abs(F_value-F_value_old) > epsilon ){
  // for(int i=0; i<10000; i++){
    F_value_old=F_value;
    Gauss_Seidle_substitution();
    Mixing();
    Calculate_functional_value();
  }
  cout << "KROK: " << step << endl;
  Write_potential();
  
  plik_potential.close();
  plik_f_value.close();

  return 0;
}
