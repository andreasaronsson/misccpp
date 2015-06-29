#include "Gearings.h"
using namespace std;

Gearings::Gearings(string type)
{
    DbConn *db = DbConn::Instance();
    Gearing *gearing;    
    QSqlQuery query;
    query = db->get("SELECT id, name, noofcogwheels, noofteeth, type FROM gearing WHERE type = '"+type+"' ORDER BY name;");
    while (query.next())
    {
      //Skapa nytt objekt
      gearing = new Gearing(query.value(0).toInt(), query.value(1).toString(), query.value(2).toInt(), query.value(3).toString(), query.value(4).toString());
      this->addItem(gearing);
    }
    
}

Gearings::Gearings(int id)
{
    DbConn *db = DbConn::Instance();
    Gearing *gearing;    
    QSqlQuery query;
    query = db->get("SELECT id, name, noofcogwheels, noofteeth, type FROM gearing WHERE id = "+QString::number(id)+" ORDER BY name;");
    while (query.next())
    {
      //Skapa nytt objekt
      gearing = new Gearing(query.value(0).toInt(), query.value(1).toString(), query.value(2).toInt(), query.value(3).toString(), query.value(4).toString());
      this->addItem(gearing);
    }
 
}

Gearing *Gearings::getItem(int index)
{
  return (Gearing*)this->itemList.at(index);
}

Gearings::~Gearings()
{
  int i;
  int j = itemList.size();
  for (i=0; i<j; i++) {
    delete (this->getItem(i));
  }
}
