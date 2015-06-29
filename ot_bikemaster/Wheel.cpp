#include "Wheel.h"

//constructors                                                                        
Wheel::Wheel()
{
    oid = 0;
    name = "";
    model = "";
    brand = "";
    circumference = 0;
    type = "back";
    description = "";    
}

// indended for creating objects from db
Wheel::Wheel(int newOid, 
	     string newName, 
	     string newBrand, 
	     string newModel, 
	     float newCircumference, 
	     string newType, 
	     string newDescription)
{
    oid = newOid;
    name = newName;
    model = newModel;
    brand = newBrand;
    circumference = newCircumference;
    type = newType;
    description = newDescription;
}
Wheel::Wheel(string newName, 
	     string newBrand, 
	     string newModel, 
	     float newCircumference, 
	     string newType, 
	     string newDescription)
{
    oid = 0; //-1 kanske?
    name = newName;
    model = newModel;
    brand = newBrand;
    circumference = newCircumference;
    type = newType;
    description = newDescription;
}
int Wheel::getOid ()
{
    return oid; 
}
void Wheel::setOid (int newOid)
{
        oid = newOid;
}
string Wheel::getName ()
{
    return name; 
}
void Wheel::setName (string newName)
{
    name = newName;
}
string Wheel::getBrand ()
{
    return brand; 
}
void Wheel::setBrand (string newBrand)
{
    brand = newBrand;
}

string Wheel::getModel ()
{
    return model; 
}

void Wheel::setModel (string newModel)
{
    model = newModel;
}

float Wheel::getCircumference ()
{
    return circumference; 
}

void Wheel::setCircumference (float newCircumference)
{
    circumference = newCircumference;
}

string Wheel::getType ()
{
    return type; 
}

void Wheel::setType (string newType)
{
    type = newType;
}

string Wheel::getDescription ()
{
    return description; 
}

void Wheel::setDescription (string newDescription)
{
    description = newDescription;
}

void Wheel::save () 
{

    stringstream ss;
    string sqlq;
    ss << "INSERT INTO Wheel(name,brand,model,circumference,type,description) VALUES('";
    ss << this->getName() << "','";
    ss << this->getBrand () << "','";
    ss << this->getModel () << "',";
    ss << this->getCircumference () << ",'";
    ss << this->getType () << "','";
    ss << this->getDescription () << "');";

    getline(ss, sqlq);
    DbConn::Instance()->set (sqlq);
}
void Wheel::upd ()
{
    stringstream ss;
    ss << "UPDATE Wheel SET name = '" << this->getName() << "',";
    ss << "brand = '" << this->getBrand () << "',";
    ss << "model = '" << this->getModel () << "',";
    ss << "circumference = " << this->getCircumference () << ",";
    ss << "type = '" << this->getType () << "',";
    ss << "description = '" << this->getBrand () << "' WHERE id = " << this->getOid() << ";";

    string sqlq;
    getline(ss, sqlq);
    DbConn::Instance()->set(sqlq);
//     int oid;
//     string name;
//     string brand;
//     string model;
//     float circumference;
//     string type;
//     string description;
}
