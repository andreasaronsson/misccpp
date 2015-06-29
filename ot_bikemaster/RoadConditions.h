#ifndef ROADCONDITIONS_H
#define ROADCONDITIONS_H
#include "Container.h"
using namespace std;
class RoadConditions : public Container
{
 public:
  //Constructors
  RoadConditions();
  //Destructor
  ~RoadConditions();

  //Access Methods
  QString getItem(int); 

 private:
};
#endif
