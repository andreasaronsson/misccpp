#ifndef TIRES_H
#define TIRES_H
#include "Container.h"
#include "Tire.h"
using namespace std;
class Tires : public Container
{
 public:
  //Constructors
  //Tires();
  Tires(int id=0);

  //Destructor
  ~Tires();

  //Access methods
  Tire* getItem(int);
 private:
};
#endif
