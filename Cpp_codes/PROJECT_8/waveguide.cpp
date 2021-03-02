#include<iostream>
#include<fstream>
#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include"methods_test.h"


///////////////////////////////////////////////////////////////////////////////
#define n 2000           // ilość próbek w każdej serii
double x0=0.5;          // początek przedziału 
double xE=1.0;            // koniec przedziału

double h=(xE-x0)/n;       // krok obliczeniowy
double Kmax=20.0;          // maksymalna wartosć współczynnika K
double dK=Kmax/100.0;      // przyrost współczynnika K; jeśli pomiędzy K a K+dK będą dwa miejsca zerowe, wykryjemy tylko jedno
double tol=Kmax/10000.0;   // precyzja wyznaczenia współczynnika K; im mniejsze tym lepsza dokładność
double K1=0.001*Kmax;     // K początkowe; K nie może być równe zeru, wiec zaczynamy od 0+kawałek
double K2=K1+dK;          // K drugie
///////////////////////////////////////////////////////////////////////////////
double zero[100];         // tablica na miejsca zerowe; w tej wersji programu jest miejsce na max 100 miejsc zerowych
double *x;                // ciężko powiedzieć co to może być
vector<double> FI, fi;        // tablica wartosci funkcji podzielonej przez pierwiastek z r (uprosciliśmy w ten sposób rów różniczkowe)
int number=0;             // ilość znalezionych miejsc zerowych

fstream plik;             // plik do którego będziemy zapisywac dane
///////////////////////////////////////////////////////////////////////////////
double k2(double x,double K){                  // współczynnik przy nieróżniczkowanej funkcji
  return K*K+1.0/4.0/x/x;
}

double fiE(double K){                          // funckja licząca wartości funcki fi(r)	
  double x=x0;                                 // zaczynamy obliczenia od x=x(0)
  double yp1=sqrt(x0);                         // funkcja FI(0)=1 i fi(x)=sqrt(x)*FI(x) => fi(0) = sqrt(x_0)
  double yp2=sqrt(x0+h);                       // drugi punkt pomiarowy jest dla x=x_0+h 
  fi = numerow2(x0,xE,n,yp1,yp2,k2,K);
  FI=fi;   // liczymy wartosci funkcji fi(x)
  for(int i : FI) {
    FI.at(i)/=sqrt((double)i/n+0.001);
  }
  
  return FI.at(n-1);                             // na koniec zwracamy wartosć funkcji falowej w x=1
}

double Write_data(){                           // funkcja zapisująca dane do pliku
  cout << "K: " << zero[number];               // wypisujemy na ekranie kolejne wartości współczynników K przy których FI(r=1)=0

  for(int i=0; i<n-1; i++){ 
    plik << (double)i/n << " "  // 1 - r 
	 << fi[i]       << " "  // 2 - fi(r)
	 << FI[i]       << " "  // 3 - FI(r)
	 << endl;
  }
  
}


////////////////////////////////////////////////////////////////////////////////
int main(){
  
  plik.open("wave.data", ios::out);         // otwieramy plik do zapisu danych 
  
  while (K2<Kmax){                          // pętla skończy się gdy zbadamy cały przedział K (od 0 do K_max)
    
    if (fiE(K1)*fiE(K2)<=0.0){              // jeśli pomiedzy dwoma K (K i K+dK) jest miejsce zerowe zaczamy poszukiwania
      zero[number]=bisec(K1,K2,tol,fiE);    // używamy do tego metody bisekcji
      Write_data();                         // po znalezieniu K z założoną dokłądnością (tol) zapisujemy dane do pliku
      number++;                             // zapisujemy informację o znalezieniu kolejnego współczynnika K
      getchar();                            // czekamy aż użytkownik kliknie enter
    }                                       
    
    K1=K2;                                  // przesuwamy zakres poszukiwań o dK
    K2=K1+dK;
  }                                         // i kontynuujemy poszukiwania kolejnego współczynnika

  plik.close();                             // zamykamy plik z danymi
}
