#include "Tire.h"
#include <iostream>

//constructors
Tire::Tire()
{
    oid = 0;
    name = "";
    brand = "";
    model = "";
}
Tire::Tire (int newOid, string _name, string b, string m)
{
    oid = newOid;   
    name = _name;
    brand = b;
    model = m;
}
Tire::Tire(string b, string _name, string m)
{
    name = _name;
    brand = b;
    model = m;
}
int Tire::getOid ()
{
    return oid; 
}
void Tire::setOid (int newOid)
{
        oid = newOid;
}
string Tire::getName ()
{
    return name; 
}
void Tire::setName (string newName)
{
        name = newName;
}
string Tire::getBrand()
{
	return brand; 
}
void Tire::setBrand(string newbrand)
{
	brand = newbrand;
}
string Tire::getModel()
{
	return model; 
}
void Tire::setModel(string newmodel)
{
	model = newmodel;
}
void Tire::save () 
{
    stringstream ss;
    string sqlq;
    ss << "INSERT INTO Tire(name,brand,model) VALUES('";
    ss << this->getName() << "','";
    ss << this->getBrand () << "','";
    ss << this->getModel () << "');";

    getline(ss, sqlq);
    DbConn::Instance()->set (sqlq);
//     int oid;
//     string brand;
//     string model;
}
void Tire::upd()
{
    stringstream ss;
    ss << "UPDATE Tire SET name = '" << this->getName() << "',";
    ss << "brand = '" << this->getBrand () << "',";
    ss << "model = '" << this->getModel () << "' WHERE ";
    ss << "id = " << getOid() << ";";
    string sqlq;
    getline(ss, sqlq);
    DbConn::Instance()->set(sqlq);
}
