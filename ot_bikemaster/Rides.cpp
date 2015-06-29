#include "Rides.h"
#include "qdatetime.h"
using namespace std;

Rides::Rides()
{
}


Rides::Rides(QDate rideDate)
{

  DbConn *db = DbConn::Instance();
    Ride* ride;    
    QSqlQuery query;
    query = db->get("SELECT ridedate, starttime, amountofsleep, trainingtime, elapsedtime, odobefore, odoafter, averagespeed, maxspeed, tempdata, maxtemp, mintemp, rating, type, bike, trail, id FROM ride WHERE ridedate = '"+rideDate.toString("yyyy-MM-dd")+"';");
    while (query.next())
    {
      //Skapa nytt objekt
      ride = new Ride(query.value(16).toInt(), query.value(0).toDate(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toString(), query.value(5).toDouble(), query.value(6).toDouble(), query.value(7).toDouble(), query.value(8).toDouble(), query.value(9).toBool(), query.value(10).toDouble(), query.value(11).toDouble(), query.value(12).toString(), query.value(13).toString(), query.value(14).toInt(), query.value(15).toInt());
      this->addItem(ride);

    }

}

Rides::Rides(int id)
{

  DbConn *db = DbConn::Instance();
    Ride* ride;    
    QSqlQuery query;
    query = db->get("SELECT ridedate, starttime, amountofsleep, trainingtime, elapsedtime, odobefore, odoafter, averagespeed, maxspeed, tempdata, maxtemp, mintemp, rating, type, bike, trail, id FROM ride WHERE id = "+QString::number(id)+";");
    while (query.next())
    {
      //Skapa nytt objekt
      ride = new Ride(query.value(16).toInt(), query.value(0).toDate(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toString(), query.value(5).toDouble(), query.value(6).toDouble(), query.value(7).toDouble(), query.value(8).toDouble(), query.value(9).toBool(), query.value(10).toDouble(), query.value(11).toDouble(), query.value(12).toString(), query.value(13).toString(), query.value(14).toInt(), query.value(15).toInt());
      this->addItem(ride);

    }

}


Ride* Rides::getItem(int index)
{
  return (Ride*)(this->itemList.at(index));
}

Rides::~Rides()
{
  int i;
  int j = itemList.size();
  for (i=0; i<j; i++) {
    delete (this->getItem(i));
  }
}
