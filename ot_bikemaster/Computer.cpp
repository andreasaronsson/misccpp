#include "Computer.h"

//constructors
Computer::Computer()
{
    oid = 0;
    name = "";
    brand = "";
    model = "";
    serialNumber = "";
    settings = 0;
    tripDistance = 0;
    tripTime = 0;
    odoMeter = 0;
    averageCadence = 0;
    altiMeter = 0;
    maxSpeed = 0;
    averageSpeed = 0;
    maxOdo = 0;
}
Computer::Computer (int newOid, 
		    string newName,
		    string newBrand, 
		    string newModel, 
		    string newSerialNumber, 
		    float newSettings, 
		    bool newTripDistance, 
		    bool newTripTime, 
		    bool newOdoMeter,
		    bool newAverageCadence, 
		    bool newAltiMeter,
		    bool newMaxSpeed, 
		    bool newAverageSpeed, 
		    float newMaxOdo)
{
    oid = newOid;
    name = newName;
    brand = newBrand;
    model = newModel;
    serialNumber = newSerialNumber;
    settings = newSettings;
    tripDistance = newTripDistance;
    tripTime = newTripTime;
    odoMeter = newOdoMeter;
    averageCadence = newAverageCadence;
    altiMeter = newAltiMeter;
    maxSpeed = newMaxSpeed;
    averageSpeed = newAverageSpeed;
    maxOdo = newMaxOdo;
}
Computer::Computer (string newName,
		    string newBrand, 
		    string newModel, 
		    string newSerialNumber, 
		    float newSettings, 
		    bool newTripDistance, 
		    bool newTripTime, 
		    bool newOdoMeter,
		    bool newAverageCadence, 
		    bool newAltiMeter,
		    bool newMaxSpeed, 
		    bool newAverageSpeed, 
		    float newMaxOdo)
{
    oid = 0;
    name = newName;
    brand = newBrand;
    model = newModel;
    serialNumber = newSerialNumber;
    settings = newSettings;
    tripDistance = newTripDistance;
    tripTime = newTripTime;
    odoMeter = newOdoMeter;
    averageCadence = newAverageCadence;
    altiMeter = newAltiMeter;
    maxSpeed = newMaxSpeed;
    averageSpeed = newAverageSpeed;
    maxOdo = newMaxOdo;
}
int Computer::getOid ()
{
    return oid; 
}
void Computer::setOid (int newOid)
{
        oid = newOid;
}
string Computer::getName ()
{
    return name; 
}
void Computer::setName (string newName)
{
        name = newName;
}
string Computer::getBrand ()
{
    return brand; 
}
void Computer::setBrand (string newBrand)
{
    brand = newBrand;
}
string Computer::getModel ()
{
    return model; 
}
void Computer::setModel (string newModel)
{
    model = newModel;
}
string Computer::getSerialNumber ()
{
    return serialNumber; 
}
void Computer::setSerialNumber (string newSerialNumber)
{
    serialNumber = newSerialNumber;
}
float Computer::getSettings ()
{
    return settings; 
}
void Computer::setSettings (float newSettings)
{
    settings = newSettings;
}
bool Computer::getTripDistance ()
{
    return tripDistance; 
}
void Computer::setTripDistance (bool newTripDistance)
{
    tripDistance = newTripDistance;
}
bool Computer::getTripTime ()
{
    return tripTime; 
}
void Computer::setTripTime (bool newTripTime)
{
    tripTime = newTripTime;
}
bool Computer::getOdoMeter ()
{
    return odoMeter; 
}
void Computer::setOdoMeter (bool newOdoMeter)
{
        odoMeter = newOdoMeter;
}

bool Computer::getAverageCadence ()
{
    return averageCadence; 
}
void Computer::setAverageCadence (bool newAverageCadence)
{
    averageCadence = newAverageCadence;
}

bool Computer::getAltiMeter ()
{
    return altiMeter; 
}
void Computer::setAltiMeter (bool newAltiMeter)
{
    altiMeter = newAltiMeter;
}

bool Computer::getMaxSpeed ()
{
    return maxSpeed; 
}
void Computer::setMaxSpeed (bool newMaxSpeed)
{
    maxSpeed = newMaxSpeed;
}

bool Computer::getAverageSpeed ()
{
    return averageSpeed; 
}
void Computer::setAverageSpeed (bool newAverageSpeed)
{
    averageSpeed = newAverageSpeed;
}
float Computer::getMaxOdo ()
{
    return maxOdo; 
}
void Computer::setMaxOdo (float newMaxOdo)
{
    maxOdo = newMaxOdo;
}
void Computer::save () 
{
    string sqlq;
    stringstream ss;
    string anfang = "INSERT INTO Computer(name,brand,model,serialnumber,settings,tripdistance,";
    string bfang = "triptime,odometer,averagecadence,altimeter,maxspeed,averagespeed,maxodo";
    string dfang = ") VALUES('";

    ss << anfang + bfang + dfang;
    ss << this->getName() << "','";
    ss << this->getBrand () << "','";
    ss << this->getModel () << "','";
    ss << this->getSerialNumber () << "',";
    ss << this->getSettings () << ",'";
    ss << this->getTripDistance () << "','";
    ss << this->getTripTime () << "','";
    ss << this->getOdoMeter() << "','";
    ss << this->getAverageCadence () << "','";
    ss << this->getAltiMeter () << "','";
    ss << this->getMaxSpeed () << "','";
    ss << this->getAverageSpeed () << "',";
    ss << this->getMaxOdo () << ");";
    
    getline(ss, sqlq);
    DbConn::Instance()->set (sqlq);

}
void Computer::upd()
{
    stringstream ss;
    ss << "UPDATE Computer SET name = '" << this->getName() << "',";
    ss << "brand = '" << this->getBrand () << "',";
    ss << "model = '" << this->getModel () << "',";
    ss << "serialnumber = '" << this->getSerialNumber () << "',";
    ss << "settings = " << this->getSettings () << ",";
    ss << "tripdistance = '"  << this->getTripDistance () << "',";
    ss << "triptime = '"  << this->getTripTime () << "',";
    ss << "odometer = '"  << this->getOdoMeter() << "',";
    ss << "averagecadence = '"  << this->getAverageCadence () << "',";
    ss << "altimeter = '"  << this->getAltiMeter () << "',";
    ss << "maxspeed = '" << this->getMaxSpeed () << "',";
    ss << "averagespeed = '" << this->getAverageSpeed () << "',";
    ss << "maxodo =  " << this->getMaxOdo () << " WHERE id = " << this->getOid();

    string sqlq;
    getline(ss, sqlq);
    DbConn::Instance()->set (sqlq);

}
