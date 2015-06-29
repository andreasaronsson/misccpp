#ifndef GEARINGS_H
#define GEARINGS_H
#include "Container.h"
#include "Gearing.h"
using namespace std;
class Gearings : public Container
{
 public:
  //Constructors
  Gearings(string);
  Gearings(int);
  //Destructor
  ~Gearings();

  //Access methods
  Gearing *getItem(int);
 private:
};
#endif
