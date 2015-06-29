#include "Bikes.h"
#include "qdatetime.h"
using namespace std;

Bikes::Bikes(int id)
{
  DbConn *db = DbConn::Instance();
    Bike *bike;    
    QSqlQuery query;
    query = db->get("SELECT id, frame, backwheel, frontwheel, bikegearing, wheelgearing, fronttire, backtire, computer, assemblydate FROM bike ORDER BY assemblydate;");
    if (id) query = db->get("SELECT id, frame, backwheel, frontwheel, bikegearing, wheelgearing, fronttire, backtire, computer, assemblydate FROM bike WHERE id = "+QString::number(id)+";");

    while (query.next())
    {
      bike = new Bike(query.value(0).toInt(), query.value(1).toInt(), query.value(2).toInt(), query.value(3).toInt(), query.value(4).toInt(), query.value(5).toInt(), query.value(6).toInt(), query.value(7).toInt(), query.value(8).toInt(), query.value(9).toDate());
      this->addItem(bike);
    }
    
}

Bike *Bikes::getItem(int index)
{
  return (Bike *)(this->itemList.at(index));
}

Bikes::~Bikes()
{
  int i;
  int j = itemList.size();
  for (i=0; i<j; i++) {
    delete (this->getItem(i));
  }
}
