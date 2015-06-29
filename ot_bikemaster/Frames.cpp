#include "Frames.h"
using namespace std;

Frames::Frames(int id)
{
  DbConn *db = DbConn::Instance();
    Frame* frame;    
    QSqlQuery query;
    query = db->get("SELECT id, name, model, serialnumber, sensorpos, type, description FROM frame ORDER BY name;");
    if (id)     query = db->get("SELECT id, name, model, serialnumber, sensorpos, type, description FROM frame WHERE id = "+QString::number(id)+" ORDER BY name;");
    while (query.next())
    {
      //Skapa nytt objekt
      frame = new Frame(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toString(), query.value(5).toString(), query.value(6).toString());
      this->addItem(frame);
    }
    

}

Frame* Frames::getItem(int index)
{
  return (Frame*)this->itemList.at(index);
}

Frames::~Frames()
{
  int i;
  int j = itemList.size();
  for (i=0; i<j; i++) {
    delete (this->getItem(i));
  }
}
