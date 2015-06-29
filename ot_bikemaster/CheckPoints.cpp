#include "CheckPoints.h"
using namespace std;

CheckPoints::CheckPoints(int trail)
{

  DbConn *db = DbConn::Instance();
  CheckPoint* checkPoint;    
  QSqlQuery query;
  QString string;
  query = db->get("SELECT id, location, distance, altitude, trail FROM checkpoint WHERE trail = "+string.setNum(trail)+" ORDER BY distance ASC;");

  while (query.next())
    {
      //Skapa nytt objekt
      checkPoint = new CheckPoint(query.value(0).toInt(), query.value(1).toString(), query.value(2).toDouble(), query.value(3).toDouble(), query.value(4).toInt());
      this->addItem(checkPoint);
    }

}

CheckPoints::CheckPoints(int id, bool temp)
{

  DbConn *db = DbConn::Instance();
  CheckPoint* checkPoint;    
  QSqlQuery query;
  QString string;
  query = db->get("SELECT id, location, distance, altitude, trail FROM checkpoint WHERE id = "+string.setNum(id)+" ORDER BY distance ASC;");

  while (query.next())
    {
      //Skapa nytt objekt
      checkPoint = new CheckPoint(query.value(0).toInt(), query.value(1).toString(), query.value(2).toDouble(), query.value(3).toDouble(), query.value(4).toInt());
      this->addItem(checkPoint);
    }

}

CheckPoint* CheckPoints::getItem(int index)
{
  return (CheckPoint*)(this->itemList.at(index));
}

        
CheckPoints::~CheckPoints()
{
  int i;
  int j = itemList.size();
  for (i=0; i<j; i++) {
    delete (this->getItem(i));
  }
}
