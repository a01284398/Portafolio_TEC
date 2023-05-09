#include <iostream>
#include <exception>
using namespace std;

class  InvalidConfigurationException : public exception{
  virtual const char* what() const throw()
  {
    return "Invalid tiles value";
  }
} invconfex;
