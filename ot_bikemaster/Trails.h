#ifndef TRAILS_H
#define TRAILS_H
#include "Container.h"
#include "Trail.h"
using namespace std;
class Trails : public Container
{
 public:
  //Constructors
    //     Trails();
     Trails(int id=0);
  //Destructor
  ~Trails();

  //Access methods
  Trail* getItem(int);
 private:
};
#endif
