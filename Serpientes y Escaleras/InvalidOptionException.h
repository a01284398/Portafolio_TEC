#include <iostream>
#include <exception>
using namespace std;

class  InvalidOptionException : public exception{
  virtual const char* what() const throw()
  {
    return "Invalid option, please press C to continue next turn or E to end the game";
  }
} invOpt;
