#include "Ride.h"

//constructors
Ride::Ride() 
{

    QSqlQuery qRideId = DbConn::Instance()->get ("SELECT NEXTVAL('bike_id_seq')");
    qRideId.next();
    this->setOid(qRideId.value(0).toInt());
    cerr <<  endl << "WE CREATED A RIDE AND IT GOT THE VALUE" << this->oid << endl;
    //oid = 0;
    date.setYMD(1900,1,1);
    startTime = "00:00:00";
    amountOfSleep = "00:00:00";
    trainingTime = "00:00:00";
    elapsedTime = "00:00:00";
    odoBefore = 0;
    odoAfter = 0;
    averageSpeed = 0;
    maxSpeed = 0;
    tempData = 0;
    maxTemp = 0;
    minTemp = 0;
    rating = "";
    type = "";
    bike = 0;
    trail = 0;
}
Ride::Ride(QDate newDate, 
	   string newStartTime, 
	   string newAmountOfSleep, 
	   string newTrainingTime, 
	   string newElapsedTime, 
	   float newOdoBefore, 
	   float newOdoAfter, 
	   float newAverageSpeed, 
	   float newMaxSpeed, 
	   bool newTempData, 
	   float newMaxTemp, 
	   float newMinTemp, 
	   string newRating, 
	   string newType,
	   int newBike, 
	   int newTrail)
{
    date = newDate;
    startTime = newStartTime;
    amountOfSleep = newAmountOfSleep;
    trainingTime = newTrainingTime;
    elapsedTime = newElapsedTime;
    odoBefore = newOdoBefore;
    odoAfter = newOdoAfter;
    averageSpeed = newAverageSpeed;
    maxSpeed = newMaxSpeed;
    tempData = newTempData;
    maxTemp = newMaxTemp;
    minTemp = newMinTemp;
    rating = newRating;
    type = newType;
    bike = newBike;
    trail = newTrail;
}
Ride::Ride(int newOid,
	   QDate newDate, 
	   string newStartTime, 
	   string newAmountOfSleep, 
	   string newTrainingTime, 
	   string newElapsedTime, 
	   float newOdoBefore, 
	   float newOdoAfter, 
	   float newAverageSpeed, 
	   float newMaxSpeed, 
	   bool newTempData, 
	   float newMaxTemp, 
	   float newMinTemp, 
	   string newRating, 
	   string newType,
	   int newBike, 
	   int newTrail)
{
    oid = newOid;
    date = newDate;
    startTime = newStartTime;
    amountOfSleep = newAmountOfSleep;
    trainingTime = newTrainingTime;
    elapsedTime = newElapsedTime;
    odoBefore = newOdoBefore;
    odoAfter = newOdoAfter;
    averageSpeed = newAverageSpeed;
    maxSpeed = newMaxSpeed;
    tempData = newTempData;
    maxTemp = newMaxTemp;
    minTemp = newMinTemp;
    rating = newRating;
    type = newType;
    bike = newBike;
    trail = newTrail;
}

//member functions
int Ride::getOid ()
{
    return oid; 
}
void Ride::setOid (int newOid)
{
        oid = newOid;
}
QDate Ride::getDate()
{
    return date; 
}
void Ride::setDate(QDate newDate)
{
    date = newDate;
}
string Ride::getStartTime()
{
    return startTime; 
}
void Ride::setStartTime(string newStartTime)
{
    startTime = newStartTime;
}
string Ride::getAmountOfSleep()
{
    return amountOfSleep; 
}
void Ride::setAmountOfSleep(string newAmountOfSleep)
{
    amountOfSleep = newAmountOfSleep;
}
string Ride::getTrainingTime()
{
    return trainingTime; 
}
void Ride::setTrainingTime(string newTrainingTime)
{
    trainingTime = newTrainingTime;
}
string Ride::getElapsedTime()
{
    return elapsedTime; 
}
void Ride::setElapsedTime(string newElapsedTime)
{
    elapsedTime = newElapsedTime;
}
float Ride::getOdoBefore()
{
    return odoBefore; 
}
void Ride::setOdoBefore(float newOdoBefore)
{
    odoBefore = newOdoBefore;
}
float Ride::getOdoAfter()
{
    return odoAfter; 
}
void Ride::setOdoAfter(float newOdoAfter)
{
    odoAfter = newOdoAfter;
}
float Ride::getAverageSpeed()
{
    return averageSpeed; 
}
void Ride::setAverageSpeed(float newAverageSpeed)
{
    averageSpeed = newAverageSpeed;
}
float Ride::getMaxSpeed()
{
    return maxSpeed; 
}
void Ride::setMaxSpeed(float newMaxSpeed)
{
    maxSpeed = newMaxSpeed;
}
bool Ride::getTempData()
{
    return tempData; 
}
void Ride::setTempData(bool newTempData)
{
    tempData = newTempData;
}
float Ride::getMaxTemp()
{
    return maxTemp; 
}
void Ride::setMaxTemp(float newMaxTemp)
{
    maxTemp = newMaxTemp;
}
float Ride::getMinTemp()
{
    return minTemp; 
}
void Ride::setMinTemp(float newMinTemp)
{
    minTemp = newMinTemp;
}
string Ride::getRating()
{
    return rating; 
}
void Ride::setRating(string newRating)
{
    rating = newRating;
}
string Ride::getType ()
{
    return type; 
}
void Ride::setType (string newType)
{
        type = newType;
}
int Ride::getBike()
{
    return bike; 
}
void Ride::setBike(int newBike)
{
    bike = newBike;
}
int Ride::getTrail()
{
    return trail; 
}
void Ride::setTrail(int newTrail)
{
    trail = newTrail;
}
void Ride::save ()
{
    string sqlq;
    stringstream ss;
    //    QSqlQuery qRideId = DbConn::Instance()->get ("SELECT NEXTVAL('bike_id_seq')");
    //qRideId.next();
    //this->setOid(qRideId.value(0).toInt());
    ss << "INSERT INTO Ride(id,ridedate,startTime,amountOfSleep,trainingTime,elapsedTime,";
    ss << "odoBefore,odoAfter,averageSpeed,maxSpeed,tempData,maxTemp,minTemp,rating";
    ss << ",type,bike,trail) VALUES('";
    ss << this->getOid() << "','";
    ss << this->getDate().toString("yyyy-MM-dd") << "','";
    ss << this->getStartTime() << "','";
    ss << this->getAmountOfSleep() << "','";
    ss << this->getTrainingTime() << "','";
    ss << this->getElapsedTime() << "',";
    ss << this->getOdoBefore() << ",";
    ss << this->getOdoAfter() << ",";
    ss << this->getAverageSpeed() << ",";
    ss << this->getMaxSpeed() << ",'";
    ss << this->getTempData() << "',";
    ss << this->getMaxTemp() << ",";
    ss << this->getMinTemp() << ",'";
    ss << this->getRating() << "','";
    ss << this->getType () << "',";
    ss << this->getBike() << ",";
    ss << this->getTrail() << ");";
    
    getline(ss, sqlq);
    DbConn::Instance()->set (sqlq);
}
void Ride::upd()
{
    stringstream ss;
    ss << "UPDATE Ride SET ridedate = '" <<  this->getDate().toString("yyyy-MM-dd") << "',";
    ss << "startTime = '" << this->getStartTime() << "',";
    ss << "amountOfSleep = '" << this->getAmountOfSleep() << "',";
    ss << "trainingTime = '" << this->getTrainingTime() << "',";
    ss << "elapsedTime = '" << this->getElapsedTime() << "',";
    ss << "odoBefore = " << this->getOdoBefore() << ",";
    ss << "odoAfter = " << this->getOdoAfter() << ",";
    ss << "averageSpeed = " << this->getAverageSpeed() << ",";
    ss << "maxSpeed = " << this->getMaxSpeed() << ",";
    ss << "tempData = '" << this->getTempData() << "',";
    ss << "maxTemp = " << this->getMaxTemp() << ",";
    ss << "minTemp = " << this->getMinTemp() << ",";
    ss << "rating = '" << this->getRating() << "',";
    ss << "type = '" << this->getType () << "',";
    ss << "bike = " << this->getBike() << ",";
    ss << "trail = " << this->getTrail() << " ";
    ss << "WHERE id = " << this->getOid() << ";";
    string sqlq;
    getline(ss, sqlq);
    DbConn::Instance()->set(sqlq);
//     QDate date;
//     string startTime;
//     string amountOfSleep;
//     string trainingTime;
//     string elapsedTime;
//     float odoBefore;
//     float odoAfter;
//     float averageSpeed;
//     float maxSpeed;
//     bool tempData;
//     float maxTemp;
//     float minTemp;
//     string rating;
//     string type;
//     int bike;
//     int trail;
}

void Ride::remove()
{
    stringstream ss;
    ss << "DELETE FROM Ride WHERE id=";
    ss << this->oid << ";";
    string sqlq;
    getline(ss, sqlq);
    DbConn::Instance()->set(sqlq);

}
