#ifndef COMPUTER_H
#define COMPUTER_H
#include "DbConn.h"

using namespace std;
class Computer
{
 public:
    //constructors
    Computer();
    Computer(string,string,string,string,float,bool,bool,bool,bool,bool,bool,bool,float);
    Computer(int,string,string,string,string,float,bool,bool,bool,bool,bool,bool,bool,float);
    
    //member functions
    int getOid ();
    void setOid (int);
    string getName ();
    void setName (string);
    string getBrand ();
    void setBrand (string);
    string getModel ();
    void setModel (string);
    string getSerialNumber ();
    void setSerialNumber (string);
    float getSettings ();
    void setSettings (float);
    bool getTripDistance ();
    void setTripDistance (bool);
    bool getTripTime ();
    void setTripTime (bool);
    bool getOdoMeter ();
    void setOdoMeter (bool);
    bool getAverageCadence ();
    void setAverageCadence (bool);
    bool getAltiMeter ();
    void setAltiMeter (bool);
    bool getMaxSpeed ();
    void setMaxSpeed (bool);
    bool getAverageSpeed ();
    void setAverageSpeed (bool);
    float getMaxOdo ();
    void setMaxOdo (float);
    void save();
    void upd();
 private:
    int oid;
    string name;
    string brand;
    string model;
    string serialNumber;
    float settings;
    bool tripDistance;
    bool tripTime;
    bool odoMeter;
    bool averageCadence;
    bool altiMeter;
    bool maxSpeed;
    bool averageSpeed;
    float maxOdo;
};

#endif
