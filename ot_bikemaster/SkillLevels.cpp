#include "SkillLevels.h"
using namespace std;

SkillLevels::SkillLevels()
{
  DbConn *db = DbConn::Instance();
  QString *skillLevel;  
  QSqlQuery query;
    query = db->get("SELECT DISTINCT (skilllevel) FROM trail ORDER BY skilllevel;");
 
    while (query.next())
    {
      //Skapa nytt objekt
     skillLevel  = new QString(query.value(0).toString());
      this->addItem(skillLevel);
    }
}

QString SkillLevels::getItem(int index)
{
    QString *temp = (QString *)this->itemList.at(index);
    return temp->left(temp->length());
}

SkillLevels::~SkillLevels()
{
  int i;
  int j = itemList.size();
  for (i=0; i<j; i++) {
    delete (this->getItem(i));
  }
}
