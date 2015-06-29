#include "FrameTypes.h"
using namespace std;

FrameTypes::FrameTypes()
{
  DbConn *db = DbConn::Instance();
  QString *frameType;  
  QSqlQuery query;
    query = db->get("SELECT DISTINCT (type) FROM frame ORDER BY type;");
 
    while (query.next())
    {
      //Skapa nytt objekt
     frameType  = new QString(query.value(0).toString());
      this->addItem(frameType);
    }
}

QString FrameTypes::getItem(int index)
{
    QString *temp = (QString *)this->itemList.at(index);
    return temp->left(temp->length());
}

FrameTypes::~FrameTypes()
{
  int i;
  int j = itemList.size();
  for (i=0; i<j; i++) {
    delete (this->getItem(i));
  }
}
