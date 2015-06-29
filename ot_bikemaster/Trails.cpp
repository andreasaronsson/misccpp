#include "Trails.h"
using namespace std;

Trails::Trails(int id)
{

  DbConn *db = DbConn::Instance();
  Trail* trail;    
  QSqlQuery query;
  query = db->get("SELECT id, name, stationary, usefrontwheel, usebackwheel, mapreference, distance, maxaltitude, minaltitude, accumaltitude, roadcondition, skilllevel, description FROM trail ORDER BY name;");
  if (id) query = db->get("SELECT id, name, stationary, usefrontwheel, usebackwheel, mapreference, distance, maxaltitude, minaltitude, accumaltitude, roadcondition, skilllevel, description FROM trail WHERE id = "+QString::number(id)+";");
  while (query.next())
      {
	  //Skapa nytt objekt
	  trail = new Trail(query.value(0).toInt(), query.value(1).toString(), query.value(2).toBool(), query.value(3).toBool(), query.value(4).toBool(), query.value(5).toString(), query.value(6).toDouble(), query.value(7).toDouble(), query.value(8).toDouble(), query.value(9).toDouble(), query.value(10).toString(), query.value(11).toString(), query.value(12).toString());
	  this->addItem(trail);
      }

}

Trail* Trails::getItem(int index)
{
    return (Trail*)(this->itemList.at(index));
}

Trails::~Trails()
{
  int i;
  int j = itemList.size();
  for (i=0; i<j; i++) {
    delete (this->getItem(i));
  }
}
