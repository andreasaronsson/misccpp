#ifndef FRAMETYPES_H
#define FRAMETYPES_H
#include "Container.h"
using namespace std;
class FrameTypes : public Container
{
 public:
  //Constructors
  FrameTypes();
  //Destructor
  ~FrameTypes();

  //Access Methods
  QString getItem(int); 

 private:
};
#endif
