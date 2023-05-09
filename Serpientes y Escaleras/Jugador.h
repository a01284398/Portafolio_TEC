#include <iostream>
using namespace std;

class Jugador {
private:
  string nombre;
  int puntuacion;
  int casilla;

public:
  Jugador();
  Jugador(string);
  void setPuntuacion(int);
  int getPuntuacion();
  string getNombre();
  void setNombre(string);
  void restart();
  int getCasilla();
  void move(int);
};

Jugador::Jugador(){
  this->nombre = "N/A";
  this->puntuacion = 0;
  this->casilla = 0;
}

Jugador::Jugador(string name) {
  this->nombre = name;
  this->puntuacion = 0;
  this->casilla = 0;
}

void Jugador::setPuntuacion(int cuanto) {
  puntuacion = puntuacion + cuanto;
}

int Jugador::getPuntuacion() {
  return puntuacion;
}

string Jugador::getNombre(){
  return nombre;
}

int Jugador::getCasilla(){
  return casilla;
}
void Jugador::move(int cuantos){
  this->casilla = casilla + cuantos;
}

void Jugador::setNombre(string nombre){
  this->nombre = nombre;
}

void Jugador::restart(){
  this->casilla = 0;
}