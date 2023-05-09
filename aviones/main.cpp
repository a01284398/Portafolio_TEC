/*André Borda Ramos A01284398
09/01/2021
Crear arreglo de 50 pesos de aviones, calcular desviación estandard y variancia de los valores del arreglo. Hacer la información accesible via un menu que se desplega hasta que se inserta 0.  */
#include <iostream>
#include <time.h>
#include <bits/stdc++.h> 
#include <cmath>
using namespace std;

void llenaArreglo(int arreglo[], int n){
  srand(time(NULL));
  for (int i = 0 ; i<n; i++){
    int num = rand() % 1000 + 5;
    arreglo[i] = num ;
    }
}
void cambiarValor(int arreglo[]){
  int numAvion = 0, nuevoV=0;
  cout<<"Inserte numero valor a cambiar (1-50): ";
  cin >> numAvion;
  if(numAvion >= 1 && numAvion <= 50){
    numAvion = numAvion - 1;
    cout<<"Inserte nuevo valor (5-1000): ";
    cin >> nuevoV;
    if(nuevoV <= 1000 && nuevoV >= 5){
      arreglo[numAvion] = nuevoV;}
    else{
      cout<<"Valor no válido"<<endl;}
}
}

void consultarAvion(int arreglo[]){
  int numAvion = 0;
  cout<<"Inserte # de avión que desea consultar (1-50)"<<endl;
  cin>> numAvion;
  if (numAvion >= 1 && numAvion <= 50){
    numAvion = numAvion - 1 ;
    cout << arreglo[numAvion] << endl;
  }
}

void desplegarArreglo(int arreglo[], int n){
  for (int k=0; k<n; k++){
    cout << k + 1 << " " << arreglo[k] << endl;
  }
}



void calcularDispersiones(int arreglo[], int n){
  int deviacion = 0, sumatoria = 0;
  float deviac = 0.0, mean, varianza;
  for(int i = 0; i < n; i++){
    sumatoria += arreglo[0];
  }
  mean = sumatoria / n;
  for(int i = 0 ; i < n ; i++){
    deviac += pow(arreglo[i]-mean,2);
  }
  deviac = sqrt(deviac / n);
  varianza = pow(deviac,2);
  cout << "La desviacion estándard es: " << deviac << ". La varianza es: "<< varianza <<endl;;
}

int main() {
  int n = 50, numAvion, nuevoV;
  int pesoAviones[n];
  llenaArreglo(pesoAviones, n);
  
  int resp=1;
  while (resp > 0){
    cout<<"Menu"<<endl;
    cout<<"<1> Desplegar arreglo "<<endl;
    cout<<"<2> Calcular desviación estándar y varianza"<<endl;
    cout<<"<3> Consultar el peso del i-ésimo avión"<<endl;
    cout<<"<4> Cambiar valor de elemento en el arreglo"<<endl;
    cout<<"<5> Ordenar valores en forma descendente"<<endl;
    cout<<"<0> Salir"<<endl;
    cin >> resp;
    switch (resp){
      case 1: desplegarArreglo(pesoAviones, n); break;
      case 2: calcularDispersiones(pesoAviones, n); break;
      case 3: consultarAvion(pesoAviones); break;
      case 4 : cambiarValor(pesoAviones); break;
      case 5: 
      n = sizeof(pesoAviones) / sizeof(pesoAviones[0]);
      sort(pesoAviones, pesoAviones + n, greater<int>());break;
      default: if (resp > 5){
        cout<<"Inserte una de las opciones del menu"<<endl;
      }
    }
  }   
}