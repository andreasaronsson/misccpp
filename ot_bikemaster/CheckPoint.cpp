#include "CheckPoint.h"

//constructors
CheckPoint::CheckPoint()
{
    oid = 0;
    location = "";
    distance = 0;
    altitude = 0;
    trail = 0;    
}
CheckPoint::CheckPoint (int newOid, 
			string newLocation, 
			float newDistance, 
			float newAltitude, 
			int newTrail)
{
    oid = newOid;
    location = newLocation;
    distance = newDistance;
    altitude = newAltitude;
    trail = newTrail;
}
CheckPoint::CheckPoint (string newLocation, 
			float newDistance, 
			float newAltitude, 
			int newTrail)
{
    oid = 0; //kanske -1
    location = newLocation;
    distance = newDistance;
    altitude = newAltitude;
    trail = newTrail;
}

int CheckPoint::getOid ()
{
    return oid; 
}
void CheckPoint::setOid (int newOid)
{
    oid = newOid;
}
string CheckPoint::getLocation ()
{
    return location; 
}
void CheckPoint::setLocation (string newLocation)
{
    location = newLocation;
}
float CheckPoint::getDistance ()
{
    return distance; 
}
void CheckPoint::setDistance (float newDistance)
{
    distance = newDistance;
}
float CheckPoint::getAltitude ()
{
    return altitude; 
}
void CheckPoint::setAltitude (float newAltitude)
{
    altitude = newAltitude;
}

int CheckPoint::getTrail ()
{
    return trail; 
}
void CheckPoint::setTrail (int newTrail)
{
    trail = newTrail;
}
void CheckPoint::save () 
{

    stringstream ss;
    string sqlq;
    
    ss << "INSERT INTO CheckPoint(location,distance,altitude,trail) VALUES('";
    ss << this->getLocation () << "',";
    ss << this->getDistance () << ",";
    ss << this->getAltitude () << ",";
    ss << this->getTrail () << ");";

    getline(ss, sqlq);
    DbConn::Instance()->set(sqlq);
}
void CheckPoint::upd()
{
    stringstream ss;

    ss << "UPDATE CheckPoint SET location = '" << this->getLocation () << "'";
    ss << ",distance = " << this->getDistance (); 
    ss << ",altitude = " << this->getAltitude ();
    ss << ",trail = " << this->getTrail ();
    ss << " WHERE id = " << this->getOid() << ";"; 
    
    string sqlq;
    getline(ss, sqlq);
    DbConn::Instance()->set (sqlq);

    //     string location;
    //     float distance;
    //     float altitude;
    //     int trail;
}


