#include "Gearing.h"

//constructors                                                                        
Gearing::Gearing()
{
    oid = 0;
    name = "";
    noOfCogWheels = 0;
    noOfTeeth = "0";
    type = "bike";
}
// indended for creating objects from db
Gearing::Gearing(int newOid, 
		 string newName,
		 int newNoOfCogWheels,
		 string newNoOfTeeth, 
		 string newType)
{
    oid = newOid;
    name = newName;
    noOfCogWheels = newNoOfCogWheels;
    noOfTeeth = newNoOfTeeth;
    type = newType;
}
Gearing::Gearing(string newName,
		 int newNoOfCogWheels,
		 string newNoOfTeeth, 
		 string newType)
{
    oid = 0; // kanske -1?
    name = newName;
    noOfCogWheels = newNoOfCogWheels;
    noOfTeeth = newNoOfTeeth;
    type = newType;
}
int Gearing::getOid ()
{
    return oid; 
}
void Gearing::setOid (int newOid)
{
    oid = newOid;
}
string Gearing::getName ()
{
    return name; 
}
void Gearing::setName (string newName)
{
        name = newName;
}
int Gearing::getNoOfCogWheels ()
{
    return noOfCogWheels; 
}
void Gearing::setNoOfCogWheels (int newNoOfCogWheels)
{
        noOfCogWheels = newNoOfCogWheels;
}
string Gearing::getNoOfTeeth ()
{
    return noOfTeeth; 
}
void Gearing::setNoOfTeeth (string newNoOfTeeth)
{
    noOfTeeth = newNoOfTeeth;
}
string Gearing::getType ()
{
    return type; 
}
void Gearing::setType (string newType)
{
        type = newType;
}
void Gearing::save () 
{
    stringstream ss;
    string sqlq;
    string anfang = "INSERT INTO Gearing(name,noOfCogWheels, noOfTeeth, type) VALUES('";
    ss << anfang;
    ss << this->getName();
    ss << "',";
    ss << this->getNoOfCogWheels();
    ss << ",ARRAY[";
    ss << this->getNoOfTeeth();
    ss << "],'";
    ss << this->getType();
    ss << "');";
    getline(ss, sqlq);
    DbConn::Instance()->set (sqlq);
}
void Gearing::upd()
{
    stringstream ss;
    string sqlq;
    ss << "UPDATE Gearing SET name = '" + this->getName(); 
    ss << "',noOfCogWheels = " << this->getNoOfCogWheels();
    ss << ",noOfTeeth = ARRAY[" << this->getNoOfTeeth() << "],";
    ss << "type = '" << this->getType() << "' ";
    ss << "WHERE id = " << this->getOid() << ";"; 
    getline(ss, sqlq);
    DbConn::Instance()->set (sqlq);
}
