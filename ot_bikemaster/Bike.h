#ifndef BIKE_H
#define BIKE_H
#include "DbConn.h"

using namespace std;
class Bike{
 public:
  //constructors
  Bike();
  Bike(int, int, int, int, int, int, int, int, int, QDate);
  Bike(int, int, int, int, int, int, int, int, QDate);
  
  //member functions
  int getOid ();
  void setOid (int);
  int getFrame ();
  void setFrame (int);
  int getBackWheel ();
  void setBackWheel (int);
  int getFrontWheel ();
  void setFrontWheel (int);
  int getBikeGearing ();
  void setBikeGearing (int);
  int getWheelGearing ();
  void setWheelGearing (int);
  int getFrontTire ();
  void setFrontTire (int);
  int getBackTire ();
  void setBackTire (int);
  int getComputer ();
  void setComputer (int);
  QDate getDate ();
  void setDate (QDate);
  void save();
  void upd();

 private:  
  int oid;
  int frame;
  int backWheel;
  int frontWheel;
  int bikeGearing;
  int wheelGearing;
  int frontTire;
  int backTire;
  int computer;
  QDate date;

};

#endif
