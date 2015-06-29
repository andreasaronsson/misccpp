#ifndef WHEEL_H
#define WHEEL_H
#include "DbConn.h"

using namespace std;
class Wheel 
{
 public:
    //constructors                                                                           
    Wheel();
    Wheel(int, string, string, string, float, string, string);
    Wheel(string, string, string, float, string, string);

    //accessor methods
    string getName();
    void setName(string);
    int getOid ();
    void setOid (int);
    string getBrand ();
    void setBrand (string);
    string getModel ();
    void setModel (string);
    float getCircumference ();
    void setCircumference (float);
    string getType ();
    void setType (string);
    string getDescription ();
    void setDescription (string);
    void save();
    void upd();

 private:
    int oid;
    string name;
    string brand;
    string model;
    float circumference;
    string type;
    string description;

};
#endif

