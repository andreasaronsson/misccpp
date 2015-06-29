#ifndef FRAMES_H
#define FRAMES_H
#include "Frame.h"
#include "Container.h"
using namespace std;
class Frames : public Container
{
 public:
  //Constructors
  //Frames();
  Frames(int id=0);

  //Destructor
  ~Frames();

  //Access Methods
  Frame* getItem(int); 

 private:
};
#endif
