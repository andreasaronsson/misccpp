#ifndef TRAIL_H
#define TRAIL_H
#include "DbConn.h"

using namespace std;
class Trail 
{
 public:
    //constructors
    Trail();
    Trail(int, string, bool, bool, bool, string, float, float, float, float,  string, string, string);
    Trail(string, bool, bool, bool, string, float, float, float, float,  string, string, string);

    //accessor methods
    int getOid ();
    void setOid (int);
    string getName ();
    void setName (string);
    bool getStationary ();
    void setStationary (bool);
    bool getUseFrontWheel ();
    void setUseFrontWheel (bool);
    bool getUseBackWheel ();
    void setUseBackWheel (bool);
    string getMapReference ();
    void setMapReference (string);
    float getDistance ();
    void setDistance (float);
    float getMaxAltitude ();
    void setMaxAltitude (float);
    float getMinAltitude ();
    void setMinAltitude (float);
    float getAccumAltitude ();
    void setAccumAltitude (float);
    string getRoadCondition ();
    void setRoadCondition (string);
    string getSkillLevel ();
    void setSkillLevel (string);
    string getDescription ();
    void setDescription (string);

    //db
    void save();
    void upd();

 private:
    int oid;
    string name;
    bool stationary;
    bool useFrontWheel;
    bool useBackWheel;
    string mapReference;
    float distance;
    float maxAltitude;
    float minAltitude;
    float accumAltitude;
    string roadCondition;
    string skillLevel;
    string description;

};
#endif

