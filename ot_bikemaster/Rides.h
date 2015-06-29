#ifndef RIDES_H
#define RIDES_H
#include "Ride.h"
#include "Container.h"
using namespace std;
class Rides : public Container
{
 public:
  //Constructors
  Rides();
  Rides(QDate rideDate);
  Rides(int);

  //Destructor
  ~Rides();

  //Access Methods
  Ride* getItem(int); 
 private:
};
#endif
