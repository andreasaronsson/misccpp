#ifndef TIRE_H
#define TIRE_H
#include "DbConn.h"

using namespace std;
class Tire{
 public:
  //constructors
  Tire();
  Tire(string, string, string);
  Tire(int,string, string, string);
  
  //member functions
  int getOid ();
  void setOid (int);
  string getName ();
  void setName (string);
  void setBrand(string);
  string getBrand();
  string getModel ();
  void setModel (string);
  void save();
  void upd();

 private:
  int oid;
  string name;
  string brand;
  string model;

};
#endif
