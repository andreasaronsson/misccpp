#include "RoadConditions.h"
using namespace std;

RoadConditions::RoadConditions()
{
  DbConn *db = DbConn::Instance();
  QString *roadCondition;  
  QSqlQuery query;
    query = db->get("SELECT DISTINCT (roadcondition) FROM trail ORDER BY roadcondition;");
 
    while (query.next())
    {
      //Skapa nytt objekt
     roadCondition  = new QString(query.value(0).toString());
      this->addItem(roadCondition);
    }
}

QString RoadConditions::getItem(int index)
{
    QString *temp = (QString *)this->itemList.at(index);
    return temp->left(temp->length());
}

RoadConditions::~RoadConditions()
{
  int i;
  int j = itemList.size();
  for (i=0; i<j; i++) {
    delete (this->getItem(i));
  }
}
