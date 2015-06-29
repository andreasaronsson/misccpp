#include "Container.h"

using namespace std;

Container::Container()
{
}

Container::~Container()
{
}

bool Container::addItem(void* item)
{
    this->itemList.push_back(item);
    return TRUE;
}

/*bool Container::addItem(string* test) 
{
  Container::addItem((void*) test);
}
*/
/**
bool Container::addItem(Wheel* wheel)
{
  Container::addItem((void* wheel);
}

bool Container::addItem(Tire* tire)
{
    Container::addItem((void*) tire));
}

*/
/*bool Container::addItem(Bike* bike)
{
  Container::addItem((void*) bike);
}

*/

int Container::getSize()
{
    return this->itemList.size();
}

bool Container::deleteItem(int index)
{
  vector<void*>::iterator it = this->itemList.begin();
  if (index < this->getSize() && index >=0)
    {
      it+=index;
      this->itemList.erase(it);
      return TRUE;
    }
  return FALSE;
  

}
