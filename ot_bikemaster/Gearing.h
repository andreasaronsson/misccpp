#ifndef GEARING_H
#define GEARING_H
#include "DbConn.h"

using namespace std;
class Gearing {
 public:
    //constructors                                                                           
    Gearing();
    Gearing(int, string, int, string, string);
    Gearing(string, int, string, string);

    //methods
    int getOid ();
    void setOid (int);
    string getName ();
    void setName (string);
    int getNoOfCogWheels ();
    void setNoOfCogWheels (int);
    string getNoOfTeeth ();
    void setNoOfTeeth (string);
    string getType ();
    void setType (string);
    void save();
    void upd();

 private:
    int oid;
    string name;
    int noOfCogWheels;
    string noOfTeeth;
    string type;

};

#endif
