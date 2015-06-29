#include "Frame.h"

//constructors                                                                        
Frame::Frame()
{
    oid = 0;
    name = "";
    model = "";
    serialNumber = "";
    sensorPos = "none";
    type = "";
    description = "";    
}
// indended for creating objects from db
Frame::Frame (int newOid, 
	      string newName,
	      string newModel,
	      string newSerialNumber,
	      string newSensorPos,
	      string newType,
	      string newDescription)
{
    oid = newOid;
    name = newName;
    model = newModel;
    serialNumber = newSerialNumber;
    sensorPos = newSensorPos;
    type = newType;
    description = newDescription;
}
//intended for creating objects by user
Frame::Frame(string newName,
	     string newModel,
	     string newSerialNumber,
	     string newSensorPos,
	     string newType,
	     string newDescription)

{
    oid = 0; // kanske -1?
    name = newName;
    model = newModel;
    serialNumber = newSerialNumber;
    sensorPos = newSensorPos;
    type = newType;
    description = newDescription;
}
int Frame::getOid ()
{
    return oid; 
}
void Frame::setOid (int newOid)
{
    oid = newOid;
}
string Frame::getName ()
{
    return name; 
}
void Frame::setName (string newName)
{
    name = newName;
}
string Frame::getModel ()
{
    return model; 
}
void Frame::setModel (string newModel)
{
    model = newModel;
}
string Frame::getSerialNumber ()
{
    return serialNumber; 
}
void Frame::setSerialNumber (string newSerialNumber)
{
    serialNumber = newSerialNumber;
}
string Frame::getSensorPos ()
{
    return sensorPos; 
}
void Frame::setSensorPos (string newSensorPos)
{
    sensorPos = newSensorPos;
}

string Frame::getType ()
{
    return type; 
}

void Frame::setType (string newType)
{
    type = newType;
}

string Frame::getDescription ()
{
    return description; 
}

void Frame::setDescription (string newDescription)
{
    description = newDescription;
}

void Frame::save () 
{

    stringstream ss;

    ss << "INSERT INTO Frame(name, model, serialNumber, sensorPos, type, description) VALUES('";
    ss << this->getName () << "','";
    ss << this->getModel () << "','";
    ss << this->getSerialNumber () << "','";
    ss << this->getSensorPos () << "','";
    ss << this->getType () << "','";
    ss << this->getDescription () << "');";

    string sqlq;
    getline(ss, sqlq);
    DbConn::Instance()->set (sqlq);
}

void Frame::upd()
{
    stringstream ss;
    ss << "UPDATE Frame SET name = '" << this->getName () << "'";;
    ss << ",model = '" << this->getModel () << "'";
    ss << ",serialNumber = '"  << this->getSerialNumber () << "'";
    ss << ",sensorPos = '" << this->getSensorPos () << "'";
    ss << ",type = '" << this->getType () << "'";
    ss << ",description = '" << this->getDescription () << "' ";
    ss << "WHERE id = " << this->getOid() << ";";

    string sqlq;
    getline(ss, sqlq);
    DbConn::Instance()->set (sqlq);
    //     string name;
    //     string model;
    //     string serialNumber;
    //     string sensorPos;
    //     string type;
    //     string description;

}
