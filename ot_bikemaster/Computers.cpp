#include "Computers.h"
using namespace std;

Computers::Computers(int id)
{

  DbConn *db = DbConn::Instance();
  Computer* computer;    
    QSqlQuery query;
    query = db->get("SELECT id, name, brand, model, serialnumber, settings, tripdistance, triptime, odometer, averagecadence, altimeter, maxspeed, averagespeed, maxodo FROM computer ORDER BY name;");
    if (id) db->get("SELECT id, name, brand, model, serialnumber, settings, tripdistance, triptime, odometer, averagecadence, altimeter, maxspeed, averagespeed, maxodo FROM computer WHERE id = "+QString::number(id)+";");
    while (query.next())
    {
      //Skapa nytt objekt
      computer = new Computer(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toString(), query.value(5).toDouble(), query.value(6).toBool(), query.value(7).toBool(), query.value(8).toBool(), query.value(9).toBool(), query.value(10).toBool(), query.value(11).toBool(), query.value(12).toBool(), query.value(13).toDouble());
      this->addItem(computer);
    }

}

Computer* Computers::getItem(int index)
{
  return (Computer*)(this->itemList.at(index));
}

Computers::~Computers()
{
  int i;
  int j = itemList.size();
  for (i=0; i<j; i++) {
    delete (this->getItem(i));
  }
}
