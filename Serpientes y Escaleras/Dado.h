#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class Die {
  public:
  Die(int);
  int rollDie();
  int rollDieTablero();
  void start();
  void setDieSize(int);

  private:
  int dieSize;
};

Die::Die(int N) {
this->dieSize = N;
}

int Die::rollDie() {
  int randomNumber;
  randomNumber = (rand() % this->dieSize) + 1;
  return randomNumber;
}

void Die::start() {
  srand((unsigned) time(0));
}

int Die::rollDieTablero() {
  int randomNumber;
  randomNumber = (rand() % this->dieSize) - 2;
  return randomNumber;
}

void Die::setDieSize(int size){
  this->dieSize = size;
}