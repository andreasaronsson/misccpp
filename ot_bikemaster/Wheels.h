#ifndef WHEELS_H
#define WHEELS_H
#include "Wheel.h"
#include "Container.h"
using namespace std;
class Wheels : public Container
{
 public:
  //Constructors
  Wheels();
  Wheels(string);
  Wheels(int);
  //Destructor
  ~Wheels();

  //Access Methods
  Wheel* getItem(int); 

 private:
};
#endif
