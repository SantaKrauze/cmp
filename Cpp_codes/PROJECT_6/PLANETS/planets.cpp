#include<stdio.h>
#include<math.h>
#include<fstream>
#include<iostream>
#include <cstdlib>
#include <cstdio>
#include <iomanip>
using namespace std;
//////////////////////////////////////////////
//DANE WEJSCIOWE
int N = 4000;  // ilość próbek
double h=0.5;  // krok czasowy
int czy_uklad_srodka_masy=1; // ukłąd odniesienia porusza się ze środkiem masy
double G=1; // stała Grawitacyjna

//////////////////////////////////////////////
class Object;
Object *Objects[10]; // maksymalna liczba obiektów
double t=0;          

//srodek masy
double xM[3];  // położenie
double vM[3];  // prędkość
double M;      // masa
/////////////////////////////////////////////////
class Object{
 public:
  int id;
  double m;
  double x[3];
  double v[3];
  double a[3];
  double F[3];
  double E_k, E_p, E_c, Lz;
  fstream plik;
 public:
  Object(double a, double b, double *c, double *d);
  ~Object();
  void Calculate_F();
  void Calculate_a();
  void Calculate_v();
  void Calculate_x();
  void Calculate_other();
  void Calculate_all();
  void Write_data();
  void Step();
};

Object::Object(double a, double b, double *c, double *d){
  id = a;
  m = b;
  x[0]=c[0];
  x[1]=c[1];
  x[2]=c[2];
  v[0]=d[0];
  v[1]=d[1];
  v[2]=d[2];

  char name[40];

  sprintf(name,"%d", id);
  plik.open( name, ios::out);
}

Object::~Object(){
  plik.close();
}

void Object::Calculate_F(){
  double r, F_c;
  double tmp_1, tmp_2, tmp_3;
  F[0]=0; F[1]=0; F[2]=0;
  E_p =0;
  
  for(int i=0; i<10; i++){
    if(i==id){ continue; }
    if(Objects[i]==NULL){ break; }
    
    tmp_1 = x[0] - Objects[i]->x[0];
    tmp_2 = x[1] - Objects[i]->x[1];
    tmp_3 = x[2] - Objects[i]->x[2];
	    
    r = sqrt(tmp_1*tmp_1 + tmp_2*tmp_2 + tmp_3*tmp_3 );
    F_c = -1.0*G* Objects[i]->m *m/r/r;
    
    F[0]= F[0] + F_c*tmp_1/r;
    F[1]= F[1] + F_c*tmp_2/r;
    F[2]= F[2] + F_c*tmp_3/r;

    E_p = E_p + F_c*r;
  }
}

void Object::Calculate_a(){
  a[0]=F[0]/m;
  a[1]=F[1]/m;
  a[2]=F[2]/m;
}

void Object::Calculate_v(){
    v[0]=v[0]+a[0]*h;
    v[1]=v[1]+a[1]*h;
    v[2]=v[2]+a[2]*h;
 
}
void Object::Calculate_x(){

  x[0]=x[0]+v[0]*h;
  x[1]=x[1]+v[1]*h;
  x[2]=x[2]+v[2]*h;

  if(czy_uklad_srodka_masy){
    x[0] = x[0] - vM[0]*h;
    x[1] = x[1] - vM[1]*h;
    x[2] = x[2] - vM[2]*h;
  }
}

void Object::Calculate_other(){
  double v_c = v[0]*v[0]+v[1]*v[1]+v[2]*v[2];
  E_k = m*v_c /2.0;
  E_c = E_k+E_p;

  Lz = (x[0]-xM[0])*(v[1]-vM[1])-(x[1]-xM[1])*(v[0]-vM[0]);
  
}

void Object::Calculate_all(){
  Calculate_F();
  Calculate_a();
  Calculate_v();
  Calculate_x();
  Calculate_other();
}

void Object::Write_data(){

  plik << setprecision(5)<<fixed;
  
  plik << t << " "
       << x[0] << " "
       << x[1] << " "
       << "   "
       << E_k  << " "
       << E_p  << " "
       << E_c  << " "
       << Lz   << " "
       << endl;
}

void Object::Step(){
  Calculate_all();
  Write_data();
}
//////////////////////////////////////////////
void Srodek_masy_calculate(){
  M=0;
  xM[0]=0; xM[1]=0; xM[2]=0;
  vM[0]=0; vM[1]=0; vM[2]=0;
  
  for(int i=0; i<10; i++){
    if(Objects[i]==NULL){ break; }
    vM[0] = vM[0] + Objects[i]->m*Objects[i]->v[0];
    vM[1] = vM[1] + Objects[i]->m*Objects[i]->v[1];
    vM[2] = vM[2] + Objects[i]->m*Objects[i]->v[2];

    xM[0] = (xM[0]*M + Objects[i]->x[0]*Objects[i]->m)/(M+Objects[i]->m);
  
    M = M + Objects[i]->m; //dodaję masy  
  }

  vM[0]=vM[0]/M;  vM[1]=vM[1]/M;   vM[2]=vM[2]/M;
}

void Srodek_masy_write(){
  cout << "SRODEK MASY" << endl
       << "M = " << M << endl
       << "X = " << xM[0] << " " << xM[1] << " " << xM[2] << endl
       << "V = " << vM[0] << " " << vM[1] << " " << vM[2] << endl
       << endl;
}

void Is_stable(){
  double E=0;
  double vx, vy, vz;
  double xx, xy, xz;

  cout << "STABILNOŚĆ" << endl;
  
  for(int i=0; i<10; i++){
    if(Objects[i]==NULL){ break; }

    vx = Objects[i]->v[0]-vM[0];
    vy = Objects[i]->v[1]-vM[1];
    vz = Objects[i]->v[2]-vM[2];

    xx = Objects[i]->x[0]-xM[0];
    xy = Objects[i]->x[1]-xM[1];
    xz = Objects[i]->x[2]-xM[2];
	    
    E = Objects[i]->m*(vx*vx+vy*vy+vz*vz)/2.0;
    cout << E << endl;
    E= E - Objects[i]->m*(M-Objects[i]->m)*G/sqrt(xx*xx+xy*xy+xz*xz);

    cout << "Obiekt " << i << " E całkowita = " << E << endl;
  }
  cout << endl;
}

///////////////////////////////////////////////
int main(){
  int proc=0;
  double x[3], v[3], m;
  for(int i=0; i<0; i++){ Objects[i]=NULL; }
  
  //////////////////////////////////////////////////
  //SŁONCE
  x[0]=0;  // położenie
  x[1]=0;
  x[2]=0;
  v[0]=0;  // prędkość
  v[1]=0;
  v[2]=0;
  m=1000;  // masa
  
  Objects[0] = new Object(0, m, x, v);
  ////////////////////////////////////////////////
  //ZIEMIA
  x[0]=100; // położenie
  x[1]=0;
  x[2]=0;
  v[0]=0;   // prędkość
  v[1]=2;
  v[2]=0;
  m=2;      // masa
  
  Objects[1] = new Object(1, m, x, v);

  /////////////////////////////////////////////////////////
  // OBLICZENIA STABILNIOŚCI

  Srodek_masy_calculate();
  Srodek_masy_write();
  Is_stable();

  /////////////////////////////////////////////////////////
  // PĘTLA OBLICZEŃ

  cout << "OBLICZENIA POŁOŻEŃ" << endl;  
  for(int i=0; i<N; i++){
    if(i%(N/10)==0){ cout << proc << "%" << endl; proc=proc+10; }
    for(int j=0; j<10; j++){
      if(Objects[j]==NULL) break;
      Objects[j]->Step();
    }
    t=t+h;
  }

  ///////////////////////////////////////////////////////////
  return 0;
}
