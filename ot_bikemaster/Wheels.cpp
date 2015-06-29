
#include "Wheels.h"
using namespace std;

Wheels::Wheels(string type)
{

  DbConn *db = DbConn::Instance();
    Wheel* wheel;    
    QSqlQuery query;
    query = db->get("SELECT id, name, brand, model, circumference, type, description FROM wheel WHERE type = '"+type+"' ORDER BY name ASC;");

    while (query.next())
    {
      //Skapa nytt objekt
      wheel = new Wheel(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toDouble(), query.value(5).toString(), query.value(6).toString());
      this->addItem(wheel);
    }
    

}

Wheels::Wheels(int id)
{
  DbConn *db = DbConn::Instance();

  Wheel* wheel;
  QSqlQuery query;
  query = db->get("SELECT id, name, brand, model, circumference, type, description FROM wheel WHERE id = "+QString::number(id)+";");

    if (query.next())
    {
      //Skapa nytt objekt
      wheel = new Wheel(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toDouble(), query.value(5).toString(), query.value(6).toString());
      this->addItem(wheel);
    }


}

Wheel* Wheels::getItem(int index)
{
  return (Wheel*)this->itemList.at(index);
}

Wheels::~Wheels()
{
  int i;
  int j = itemList.size();
  for (i=0; i<j; i++) {
    delete (this->getItem(i));
  }
}
