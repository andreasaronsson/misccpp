#ifndef COMPUTERS_H
#define COMPUTERS_H
#include "Container.h"
#include "Computer.h"
using namespace std;
class Computers : public Container
{
 public:
  //Constructors
  //Computers();
  Computers(int id=0);

  //Destructor
  ~Computers();

  //Access methods
  Computer* getItem(int);
 private:
};
#endif
