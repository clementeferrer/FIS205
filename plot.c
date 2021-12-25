#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void plot(int pasos, string file, string file2) {
  TCanvas *c1 = new TCanvas("c1","Grafico",200,10,700,500);
  Double_t x[pasos], y[pasos];
  Int_t i=0;
  Int_t j=0;
  string linea;
  ifstream archivo(file.c_str());
  while (getline(archivo, linea)) {
    x[i] = stod(linea);
    i=i+1;
  }
  archivo.close();
  ifstream archivo2(file2.c_str());
  while (getline(archivo2, linea)) {
    y[j] = stod(linea);
    j=j+1;
  }
  archivo2.close();
  TGraph* gr = new TGraph(pasos,x,y);
  gr->SetTitle(" ");
  gr->Draw("AC");
  c1->SaveAs("ploteo.png");
}