#ifndef BIKES_H
#define BIKES_H
#include "Container.h"
#include "Bike.h"
using namespace std;
class Bikes : public Container
{
 public:
  //Constructors
  //Bikes();
  Bikes(int id=0);

  //Destructor
  ~Bikes();

  Bike *getItem(int);
 private:
};
#endif
