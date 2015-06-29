#include "Tires.h"
using namespace std;

Tires::Tires(int id)
{
    DbConn *db =  DbConn::Instance();
    Tire* tire;    
    QSqlQuery query;
    query = db->get("SELECT id, name, brand, model FROM tire ORDER BY name;");
    if (id) db->get("SELECT id, name, brand, model FROM tire WHERE id = "+QString::number(id)+";");
    while (query.next())
    {
      //Skapa nytt objekt
      tire = new Tire(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString());
      this->addItem(tire);
    }

}

Tire* Tires::getItem(int index)
{
  return (Tire*)(this->itemList.at(index));
}

Tires::~Tires()
{
  int i;
  int j = itemList.size();
  for (i=0; i<j; i++) {
    delete (this->getItem(i));
  }
}
