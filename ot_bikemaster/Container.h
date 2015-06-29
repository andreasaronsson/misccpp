#ifndef CONTAINER_H
#define CONTAINER_H
#include <string>
#include <vector>
#include "DbConn.h"
using namespace std;
class Container
{
 public:
  //Constructors
  Container();

  //Destructor
  ~Container();

  //Accessor methods
  int getSize();
  bool addItem(void*);
  bool deleteItem(int);
protected:
  vector<void*> itemList;
 private:
};
#endif
