#ifndef RIDE_H
#define RIDE_H
#include "DbConn.h"

using namespace std;
class Ride 
{
 public:
    //constructors
    Ride();
    Ride(int,QDate,string,string,string,string,float,float,float,float,bool,float,float,string,string,int,int);
    Ride(QDate,string,string,string,string,float,float,float,float,bool,float,float,string,string,int,int);
    int getOid ();
    void setOid (int);
    QDate getDate();
    void setDate(QDate);
    string getStartTime();
    void setStartTime(string);
    string getAmountOfSleep();
    void setAmountOfSleep(string);
    string getTrainingTime();
    void setTrainingTime(string);
    string getElapsedTime();
    void setElapsedTime(string);
    float getOdoBefore();
    void setOdoBefore(float);
    float getOdoAfter();
    void setOdoAfter(float);
    float getAverageSpeed();
    void setAverageSpeed(float);
    float getMaxSpeed();
    void setMaxSpeed(float);
    bool getTempData();
    void setTempData(bool);
    float getMaxTemp();
    void setMaxTemp(float);
    float getMinTemp();
    void setMinTemp(float);
    string getRating();
    void setRating(string);
    string getType ();
    void setType (string);
    int getBike();
    void setBike(int);
    int getTrail();
    void setTrail(int);
    void save();
    void upd();
    void remove();

 private:
    int oid;
    QDate date;
    string startTime;
    string amountOfSleep;
    string trainingTime;
    string elapsedTime;
    float odoBefore;
    float odoAfter;
    float averageSpeed;
    float maxSpeed;
    bool tempData;
    float maxTemp;
    float minTemp;
    string rating;
    string type;
    int bike;
    int trail;

};

#endif
