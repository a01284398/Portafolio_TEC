#include <iostream>
using namespace std;

class Tablero {
  public:
  Tablero();
  Tablero(int, int);
  int getId();
  void setId(int);
  int getBonus();
  void setBonus(int);

  private:
  int id;
  int bonus;
};

Tablero::Tablero(){
  this->id = 0;
  this->bonus = 0;
}

Tablero::Tablero(int id, int bonus) {
  this->id = id;
  this->bonus = bonus;
}

int Tablero::getId(){
  return id;
}
int Tablero::getBonus(){
  return bonus;
}

void Tablero::setId(int id){
  this->id = id;
}

void Tablero::setBonus(int bonus){
  this->bonus = bonus;
}