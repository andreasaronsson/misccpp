#include "Trail.h"

//constructors                                                                        
Trail::Trail()
{
    oid = 0;
    name = "";
    stationary = 0;
    useFrontWheel = 0;
    useBackWheel = 0;
    mapReference = "";
    distance = 0;
    maxAltitude = 0;
    minAltitude = 0; 
    accumAltitude = 0;
    roadCondition = "";
    skillLevel = "";
    description = "";
}

// indended for creating objects from db
Trail::Trail(int newOid,
	     string newName,
	     bool newStationary,
	     bool newUseFrontWheel,
	     bool newUseBackWheel,
	     string newMapReference,
	     float newDistance,
	     float newMaxAltitude,
	     float newMinAltitude,
	     float newAccumAltitude,
	     string newRoadCondition,
	     string newSkillLevel,
	     string newDescription)
{
    oid = newOid;
    name = newName;
    stationary=newStationary;
    useFrontWheel=newUseFrontWheel;
    useBackWheel=newUseBackWheel;
    mapReference=newMapReference;
    distance=newDistance;
    maxAltitude=newMaxAltitude;
    minAltitude=newMinAltitude;
    accumAltitude=newAccumAltitude;
    roadCondition=newRoadCondition;
    skillLevel=newSkillLevel;
    description=newDescription;
}
//intended for creating objects by user
Trail::Trail(string newName,
	     bool newStationary,
	     bool newUseFrontWheel,
	     bool newUseBackWheel,
	     string newMapReference,
	     float newDistance,
	     float newMaxAltitude,
	     float newMinAltitude,
	     float newAccumAltitude,
	     string newRoadCondition,
	     string newSkillLevel,
	     string newDescription)
{
    name = newName;
    stationary=newStationary;
    useFrontWheel=newUseFrontWheel;
    useBackWheel=newUseBackWheel;
    mapReference=newMapReference;
    distance=newDistance;
    maxAltitude=newMaxAltitude;
    minAltitude=newMinAltitude;
    accumAltitude=newAccumAltitude;
    roadCondition=newRoadCondition;
    skillLevel=newSkillLevel;
    description=newDescription;
}
int Trail::getOid ()
{
    return oid; 
}
void Trail::setOid (int newOid)
{
        oid = newOid;
}
string Trail::getName ()
{
    return name; 
}
void Trail::setName (string newName)
{
    name = newName;
}
bool Trail::getStationary ()
{
    return stationary; 
}
void Trail::setStationary (bool newStationary)
{
        stationary = newStationary;
}
bool Trail::getUseFrontWheel ()
{
    return useFrontWheel; 
}
void Trail::setUseFrontWheel (bool newUseFrontWheel)
{
        useFrontWheel = newUseFrontWheel;
}
bool Trail::getUseBackWheel ()
{
    return useBackWheel; 
}
void Trail::setUseBackWheel (bool newUseBackWheel)
{
        useBackWheel = newUseBackWheel;
}
string Trail::getMapReference ()
{
    return mapReference; 
}
void Trail::setMapReference (string newMapReference)
{
        mapReference = newMapReference;
}
float Trail::getDistance ()
{
    return distance; 
}
void Trail::setDistance (float newDistance)
{
        distance = newDistance;
}
float Trail::getMaxAltitude ()
{
    return maxAltitude; 
}
void Trail::setMaxAltitude (float newMaxAltitude)
{
        maxAltitude = newMaxAltitude;
}
float Trail::getMinAltitude ()
{
    return minAltitude; 
}
void Trail::setMinAltitude (float newMinAltitude)
{
        minAltitude = newMinAltitude;
}
float Trail::getAccumAltitude ()
{
    return accumAltitude; 
}
void Trail::setAccumAltitude (float newAccumAltitude)
{
        accumAltitude = newAccumAltitude;
}
string Trail::getRoadCondition ()
{
    return roadCondition; 
}
void Trail::setRoadCondition (string newRoadCondition)
{
        roadCondition = newRoadCondition;
}
string Trail::getSkillLevel ()
{
    return skillLevel; 
}
void Trail::setSkillLevel (string newSkillLevel)
{
        skillLevel = newSkillLevel;
}
string Trail::getDescription ()
{
    return description; 
}
void Trail::setDescription (string newDescription)
{
        description = newDescription;
}
void Trail::save () 
{
    string sqlq;
    stringstream ss;
    ss << "INSERT INTO Trail(name,stationary,useFrontWheel,useBackWheel,mapReference,distance";
    ss << ",maxAltitude,minAltitude,accumAltitude,roadCondition,skillLevel,description) VALUES('";
    ss << this-> getName () << "','";
    ss << this->getStationary () << "','";
    ss << this->getUseFrontWheel () << "','";
    ss << this->getUseBackWheel () << "','";
    ss << this-> getMapReference () << "',";
    ss << this->getDistance () << ",";
    ss << this->getMaxAltitude () << ",";
    ss << this->getMinAltitude () << ",";
    ss << this->getAccumAltitude () << ",'";
    ss << this-> getRoadCondition () << "','";
    ss << this-> getSkillLevel () << "','";
    ss << this-> getDescription () << "');";

    getline(ss, sqlq);
    DbConn::Instance()->set (sqlq);
}
void Trail::upd()
{
    stringstream ss;
    ss << "UPDATE Trail SET name = '" << this-> getName () << "',";
    ss << "stationary = '" << this-> getStationary () << "',";
    ss << "useFrontWheel = '" << this-> getUseFrontWheel () << "',";
    ss << "useBackWheel = '" << this-> getUseBackWheel () << "',";
    ss << "mapReference = '" << this-> getMapReference() << "',";
    ss << "distance = " << this-> getDistance () << ",";
    ss << "maxAltitude = " << this-> getMaxAltitude () << ",";
    ss << "minAltitude = " << this-> getMinAltitude () << ",";
    ss << "accumAltitude = " << this-> getAccumAltitude() << ",";
    ss << "roadCondition = '" << this-> getRoadCondition() << "',";
    ss << "skillLevel = '" << this-> getSkillLevel() << "',";
    ss << "description = '" << this-> getDescription() << "' WHERE id =" << this->getOid() << ";";
    string sqlq;
    getline(ss, sqlq);
    DbConn::Instance()->set (sqlq);
//     string name;
//     bool stationary;
//     bool useFrontWheel;
//     bool useBackWheel;
//     string mapReference;
//     float distance;
//     float maxAltitude;
//     float minAltitude;
//     float accumAltitude;
//     string roadCondition;
//     string skillLevel;
//     string description;

}
