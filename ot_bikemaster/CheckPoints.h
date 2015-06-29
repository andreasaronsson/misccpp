#ifndef CHECKPOINTS_H
#define CHECKPOINTS_H
#include "Container.h"
#include "CheckPoint.h"
using namespace std;
class CheckPoints : public Container
{
 public:
  //Constructors
  //CheckPoints();
  CheckPoints(int);
  CheckPoints(int, bool);

  //Destructor
  ~CheckPoints();

  //Access methods
  CheckPoint* getItem(int);
 private:
};
#endif
