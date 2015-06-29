
#include "RideCheckPoints.h"
using namespace std;

RideCheckPoints::RideCheckPoints(int id)
{
    QTime time;
    DbConn *db = DbConn::Instance();
    RideCheckPoint* rideCheckPoint;    
    QSqlQuery query;
    query = db->get("SELECT r.id, c.id, rcp.checktime FROM checkpoint c LEFT JOIN ride r ON (r.trail = c.trail) LEFT JOIN ridecheckpoint rcp ON (rcp.ride = r.id AND rcp.checkpoint = c.id) WHERE r.id ="+QString::number(id)+" ORDER BY c.distance ASC");
 
    while (query.next())
    {
      //Skapa nytt objekt
        time = query.value(2).toTime();
        rideCheckPoint = new RideCheckPoint(query.value(0).toInt(), query.value(1).toInt(), time);
      this->addItem(rideCheckPoint);
    }
    
}

RideCheckPoint* RideCheckPoints::getItem(int index)
{
  return (RideCheckPoint*)this->itemList.at(index);
}

RideCheckPoints::~RideCheckPoints()
{
  int i;
  int j = itemList.size();
  for (i=0; i<j; i++) {
    delete (this->getItem(i));
  }
}
