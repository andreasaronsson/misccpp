#ifndef REPORTITEM_H
#define REPORTITEM_H
#include <qstring.h>
#include <qdatetime.h>
#include <sstream>
using namespace std;

class ReportItem 
{

public:
  //constructors
  ReportItem();
  ReportItem(QString, QString, QString); /*this is used for items */
  ReportItem(QString, QString, QString, double, double); /* this is used for interalls*/
  ReportItem(QString, QString, QString, QDate, QDate); /* this is used for date interval */
  
  //methods
  void setOperator(QString);
  void setItemType(QString);
  void setItemName(QString);
  void setMinValue(double);
  void setMaxValue(double);
  void setStartDate(QDate);
  void setStopDate(QDate);
  
  QString getOperator();
  QString getItemType();
  QString getItemName();
  double getMinValue();
  double getMaxValue();
  QDate getStartDate();
  QDate getStopDate();
  QString getSql();
 
private:
  QString op;
  QString itemType;
  QString itemName;
  double minValue;
  double maxValue;
  QDate startDate;
  QDate stopDate;
};
#endif
