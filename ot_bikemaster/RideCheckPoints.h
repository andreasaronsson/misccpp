#ifndef RIDECHECKPOINTS_H
#define RIDECHECKPOINTS_H
#include "RideCheckPoint.h"
#include "Container.h"
using namespace std;
class RideCheckPoints : public Container
{
 public:
  //Constructors
  RideCheckPoints();
  RideCheckPoints(int);
  //Destructor
  ~RideCheckPoints();

  //Access Methods
  RideCheckPoint* getItem(int); 

 private:
};
#endif
