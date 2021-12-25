#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

const double t_inicial = 0;
const int n = 1000;
const double t_max = 100;
const double h = (t_max-t_inicial)/n;
const double c[4] = {100,0,0,0};
const double l1 = 0.0152;
const double l2 = 0.315;
const double l3 = 0.00355;

double N_1(double t,double y);
double N_2(double t,double y, vector<double> &n1, int i);
double N_3(double t,double y, vector<double> &n2, int i);
double N_4(double t,double y, vector<double> &n3, int i);
void generar(vector<double> &vect, string input);

int main() {
  double t0, y0, tn, yn, slope;
  int i;
  vector<double> t_array, n1_array, n2_array, n3_array, n4_array;

  t0 = t_inicial;
  y0 = c[0];

  /* Método de Euler N1 */
  for(i = 0; i < n; i++){
    slope = N_1(t0, y0);
    yn = y0 + h * slope;
    t_array.push_back(t0);
    n1_array.push_back(y0/c[0]);
    y0 = yn;
    t0 = t0+h;
  }

  t0 = t_inicial;
  y0 = c[1];

  /* Método de Euler N2 */
  for(i=0; i < n; i++){
    slope = N_2(t0, y0, n1_array, i);
    yn = y0 + h * slope;
    n2_array.push_back(y0/c[0]);
    y0 = yn;
    t0 = t0+h;
  }

  t0 = t_inicial;
  y0 = c[2];

  /* Método de Euler N3 */
  for(i=0; i < n; i++){
    slope = N_3(t0, y0, n2_array, i);
    yn = y0 + h * slope;
    n3_array.push_back(y0/c[0]);
    y0 = yn;
    t0 = t0+h;
  }

  t0 = t_inicial;
  y0 = c[3];

  /* Método de Euler N4 */
  for(i=0; i < n; i++){
    slope = N_4(t0, y0, n3_array, i);
    yn = y0 + h * slope;
    n4_array.push_back(y0/c[0]);
    y0 = yn;
    t0 = t0+h;
  }

  generar(t_array, string("times"));
  generar(n1_array, string("N1"));
  generar(n2_array, string("N2"));
  generar(n3_array, string("N3"));
  generar(n4_array, string("N4"));
}

double N_1(double t,double y){
  return -l1*y;
}

double N_2(double t,double y, vector<double> &n1, int i){
  return l1*n1.at(i)-l2*y;
}

double N_3(double t,double y, vector<double> &n2, int i){
  return l2*n2.at(i)-l3*y;
}

double N_4(double t,double y, vector<double> &n3, int i){
  return l3*n3.at(i);
}

void generar(vector<double> &vect, string input){
  ofstream myfile (input);
  if (myfile.is_open()){
    for(int count = 0; count < n; count ++){
      if (count == n-1)
        myfile << vect.at(count);
      else
        myfile << vect.at(count) << "\n";
    }
    myfile.close();
  }
}