#ifndef FRAME_H
#define FRAME_H
#include "DbConn.h"

using namespace std;
class Frame 
{
 public:
    //constructors
    Frame();
    Frame(int, string, string, string, string, string, string);
    Frame(string, string, string, string, string, string);

    //accessor methods
    int getOid ();
    void setOid (int);
    string getName ();
    void setName (string);
    string getModel ();
    void setModel (string);
    string getSerialNumber ();
    void setSerialNumber (string);
    string getSensorPos ();
    void setSensorPos (string);
    string getType ();
    void setType (string);
    string getDescription ();
    void setDescription (string);
    void save();
    void upd();
    
 private:
    int oid;
    string name;
    string model;
    string serialNumber;
    string sensorPos;
    string type;
    string description;

};
#endif

