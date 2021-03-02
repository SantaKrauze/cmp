#include <iostream>
#include <fstream>
using namespace std;
/////////////////////////////////////////////////////////////////////////////
#define N 10000            // wybieramy ilość punktów pomiarowych
#define FI_zero 20.0       // temperatura z jednej strony sciany
#define FI_N 1.0           // temperatura z drugiej strony sciany
#define h 0.0001           // stała siatki
//////////////////////////////////////////////////////////////////////////////
double D[N];               // przenikalnosć termiczna ściany
double D_prim[N];          // pochodna przenikalnosci
double A_minus[N];         // A_minus[i] = D[i]-h*D'[i]/2
double A_zero[N];          // A_zero[i] = -2*D[i]
double A_plus[N];          // A_minus[i] = D[i]+h*D'[i]/2
double b[N];               // prawa strona rownania rozniczkowego
double FI[N];              // temperatura wewnątrz ściany

double alpha[N];           // pod-diagonala
double betha[N];           // diagonala
double gamma[N];           // nad-diagonala

fstream plik;              // plik do ktorego zapisujemy wyniki
//////////////////////////////////////////////////////////////////////////////
void Init(){
  FI[0] = FI_zero;         // ustalamy temperatury z jednej strony sciany
  FI[N-1] = FI_N;          // i z drugiej
  
  for(int i=0; i<N; i++){  // liczymy rozklad przenikalnosci cieplnej sciany
    D[i]=0.1+10.0*i*h;     // tu wstawaimy funkcje rozkladu D
    D_prim[i]=10.0;        // i jej pochodną policzoną analitycznie
  }

  for(int i=0; i<N; i++){                // w tej pętli wyliczmy wspolczynniki rownania rozniczkowego
    A_minus[i] = D[i]-h*D_prim[i]/2.0;   // A-
    A_zero[i]  = -2.0*D[i];              // A0
    A_plus[i]  = D[i]+h*D_prim[i]/2.0;   // A+
    b[i]       = 0.0;                    // i prawą stronę równania, u nas równą zero (rów jednorodne)
  }
}

void Gauss(){            // funkcja licząca elementy na diagonali i na ich podstawie nasze FI
  betha[N-2]=FI[N-1];    // na samym dole FI[n=N] = alpha[n=N]+betha[n=N] i a[n=N]=0 => betha[n=N]=FI[n=N]
  alpha[N-2]=0.0;        // Fi[n=N] znamy, jest to jeden z wybranych warunkow brzegowych

  for(int i=N-2; i>0; i--){    // petla musi leciec od konca - skrypt równania 55 i 56
    gamma[i]=-1.0/(A_zero[i]+A_plus[i]*alpha[i]);
    alpha[i-1]=A_minus[i]*gamma[i];
    betha[i-1]=(A_plus[i]*betha[i]-b[i])*gamma[i];
  }

  for(int i=0; i<N-2; i++){    // na koncu mozemy policzyc nasze FI z równania 51
    FI[i+1]=alpha[i]*FI[i]+betha[i];
  }

  // liczac wspolczynniki alpha betha i gamma od konca uzywamy jednego warunku brzegowego
  // liczac FI od poczatku uzywamy drugiego warunku brzegowego
  
}

void Save_data(){
  plik.open("diff_0.data", ios::out);  // otwieramy plik o nazwie "diff_0.data" do zapisu
  plik.setf( ios::scientific );        // ustawiamy tryb zapisu w notacji naukowej
  
  for(int i=0; i<N; i++){      // i zapisujemy interesujace nas informacje
    plik << i*h        << " "  //1 - x
	 << FI[i]      << " "  //2 - temperatura wewnatrz muru
	 << D[i]       << " "  //3 - przenikalnosc termiczna muru
	 << D_prim[i]  << " "  //4 - pochodna przenikalnosci
	 << A_minus[i] << " "  //5 - wspolczynnik
	 << A_zero[i]  << " "  //6 - wspolczynnik
	 << A_plus[i]  << " "  //7 - wspolczynnik
	 << b[i]       << " "  //8 - prawa strona rownania rozniczkowego (u nas b=0, rów jednorodne)
	 << alpha[i]   << " "  //9 - wspolczynnik pod-diagonali
	 << betha[i]   << " "  //10 - wspolczynnik diagonali
	 << gamma[i]   << " "  //11 - wspolczynnik nad-diagonali
	 << endl;              // koniec linii
  }
  
  plik.close();                // zamykamy plik
}
//////////////////////////////////////////////////////////////////////////////
int main(){
  Init();          //inicjujemy tablice przenikalnosci termicznej i warunki początkowe
  Gauss();         // liczymy temperaturę wewnątrz sciany
  Save_data();     // zapisujemy dane do pliku
  return 0;
}
