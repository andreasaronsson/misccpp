#ifndef CHECKPOINT_H
#define CHECKPOINT_H
#include "DbConn.h"

using namespace std;
class CheckPoint 
{
 public:
    //constructors
    CheckPoint();
    CheckPoint(string, float, float, int);
    CheckPoint(int, string, float, float, int);
  
    //member functions
    int getOid ();
    void setOid (int);
    string getLocation ();
    void setLocation (string);
    float getDistance ();
    void setDistance (float);
    float getAltitude ();
    void setAltitude (float);
    int getTrail ();
    void setTrail (int);
    void save();
    void upd();

 private:
    int oid;
    string location;
    float distance;
    float altitude;
    int trail;
};

#endif
