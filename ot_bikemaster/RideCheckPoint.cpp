#include "RideCheckPoint.h"

//constructors                                                    
RideCheckPoint::RideCheckPoint()
{
    ride = 0;
    checkPoint = 0;
    checkTime.setHMS(3,2,2);
}
// indended for creating objects from db 
RideCheckPoint::RideCheckPoint(int newRide,
			       int newCheckPoint,
			       QTime& newCheckTime)
{
    ride = newRide;
    checkPoint = newCheckPoint;
    checkTime = newCheckTime;
}
int RideCheckPoint::getRide ()
{
    return ride; 
}
void RideCheckPoint::setRide (int newRide)
{
    ride = newRide;
}
int RideCheckPoint::getCheckPoint ()
{
    return checkPoint; 
}
void RideCheckPoint::setCheckPoint (int newCheckPoint)
{
    checkPoint = newCheckPoint;
}
QTime& RideCheckPoint::getCheckTime ()
{
    return checkTime; 
}
void RideCheckPoint::setCheckTime (QTime& newCheckTime)
{
    checkTime = newCheckTime;
}
void RideCheckPoint::save()
{
    stringstream ss;
    ss << "INSERT INTO Ridecheckpoint(ride,checkpoint,checktime) VALUES(";
    ss << this->getRide() << "," << this->getCheckPoint() << ",";
    ss << "'" << this->getCheckTime().toString("hh:mm:ss") << "');";
    string sqlq;
    getline(ss, sqlq);
    DbConn::Instance()->set(sqlq);
}
void RideCheckPoint::upd()
{
    stringstream ss;
    ss << "UPDATE Ridecheckpoint SET ride = " << this->getRide();
    ss << ",checkpoint = " << this->getCheckPoint();
    ss << ",checktime = '" << this->getCheckTime().toString("hh:mm:ss");
    ss << "'" << " WHERE ride = " << this->getRide();
    ss << " AND checkpoint = " << this->getCheckPoint() << ";";
    string sqlq;
    getline(ss, sqlq);
    DbConn::Instance()->set(sqlq);
}
