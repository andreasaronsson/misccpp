#ifndef SKILLLEVELS_H
#define SKILLLEVELS_H
#include "Container.h"
using namespace std;
class SkillLevels : public Container
{
 public:
  //Constructors
  SkillLevels();
  //Destructor
  ~SkillLevels();

  //Access Methods
  QString getItem(int); 

 private:
};
#endif
