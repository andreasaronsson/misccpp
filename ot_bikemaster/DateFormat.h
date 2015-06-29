#ifndef DATEFORMAT_H
#define DATEFORMAT_H
#include <string>
#include "DbConn.h"
using namespace std;
class DateFormat
{
 public:
  //constructors
  DateFormat();
  DateFormat(string, string, string, bool, int);
  DateFormat(int, string, string, string, bool, int);
  
  //member functions
  int getOid ();
  void setOid (int);
  string getOrder ();
  void setOrder (string);
  string getMonthFormat ();
  void setMonthFormat (string);
  string getWeekStarts ();
  void setWeekStarts (string);
  bool getDayLeadingZeros ();
  void setDayLeadingZeros (bool);
  int getCentury ();
  void setCentury (int);
  void save();

 private:
  int oid;
  string order;
  string monthFormat;
  string weekStarts;
  bool dayLeadingZeros;
  int century;
};

#endif
