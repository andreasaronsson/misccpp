#include "Bike.h"

//constructors
Bike::Bike()
{
    oid = 0;
    frame = 0;
    backWheel = 0;
    frontWheel = 0;
    bikeGearing = 0;
    wheelGearing = 0;
    frontTire = 0;
    backTire = 0;
    computer = 0;

}
Bike::Bike (int newOid, 
	    int newFrame, 
	    int newBackWheel, 
	    int newFrontWheel, 
	    int newBikeGearing,
	    int newWheelGearing,
	    int newFrontTire, 
	    int newBackTire,
	    int newComputer,
	    QDate newDate)
{
    oid = newOid;   
    frame = newFrame;
    backWheel = newBackWheel;
    frontWheel = newFrontWheel;
    bikeGearing = newBikeGearing;
    wheelGearing = newWheelGearing;
    frontTire = newFrontTire;
    backTire = newBackTire;
    computer = newComputer;
    date = newDate;
}
Bike::Bike (int newFrame, 
	    int newBackWheel, 
	    int newFrontWheel, 
	    int newBikeGearing,
	    int newWheelGearing,
	    int newFrontTire, 
	    int newBackTire,
	    int newComputer,
	    QDate newDate)
{
    frame = newFrame;
    backWheel = newBackWheel;
    frontWheel = newFrontWheel;
    bikeGearing = newBikeGearing;
    wheelGearing = newWheelGearing;
    frontTire = newFrontTire;
    backTire = newBackTire;
    computer = newComputer;
    date = newDate;
}
int Bike::getOid ()
{
    return oid; 
}
void Bike::setOid (int newOid)
{
        oid = newOid;
}
int Bike::getFrame ()
{
    return frame; 
}
void Bike::setFrame (int newFrame)
{
        frame = newFrame;
}
int Bike::getBackWheel ()
{
    return backWheel; 
}
void Bike::setBackWheel (int newBackWheel)
{
        backWheel = newBackWheel;
}
int Bike::getFrontWheel ()
{
    return frontWheel; 
}
void Bike::setFrontWheel (int newFrontWheel)
{
        frontWheel = newFrontWheel;
}
int Bike::getBikeGearing ()
{
    return bikeGearing; 
}
void Bike::setBikeGearing (int newBikeGearing)
{
        bikeGearing = newBikeGearing;
}
int Bike::getWheelGearing ()
{
    return wheelGearing; 
}
void Bike::setWheelGearing (int newWheelGearing)
{
        wheelGearing = newWheelGearing;
}
int Bike::getFrontTire ()
{
    return frontTire; 
}
void Bike::setFrontTire (int newFrontTire)
{
        frontTire = newFrontTire;
}
int Bike::getBackTire ()
{
    return backTire; 
}
void Bike::setBackTire (int newBackTire)
{
        backTire = newBackTire;
}
int Bike::getComputer ()
{
    return computer; 
}
void Bike::setComputer (int newComputer)
{
        computer = newComputer;
}
QDate Bike::getDate ()
{
    return date; 
}
void Bike::setDate (QDate newDate)
{
        date = newDate;
}
void Bike::save () 
{
    stringstream ss;
    string sqlq;
    DbConn* db = DbConn::Instance();
    QSqlQuery qBikeId = db->get ("SELECT NEXTVAL('bike_id_seq')");
    qBikeId.next();
    this->setOid(qBikeId.value(0).toInt());
    string anfang = "INSERT INTO Bike(id, frame, backwheel, frontwheel, bikegearing, wheelgearing,";
    string bfang = "fronttire, backtire, computer, assemblydate) VALUES(";
    ss << anfang + bfang;
    ss << this->getOid() << ",";
    ss << this->getFrame ();
    ss << ",";
    ss << this->getBackWheel ();
    ss << ",";
    ss << this->getFrontWheel ();
    ss << ",";
    ss << this->getBikeGearing ();
    ss << ",";
    ss << this->getWheelGearing ();
    ss << ",";
    ss << this->getFrontTire ();
    ss << ",";
    ss << this->getBackTire ();
    ss << ",";
    ss << this->getComputer ();
    ss << ",'";
    ss << this->getDate().toString("yyyy-MM-dd");
    ss << "');";
    getline(ss, sqlq);
    db->set (sqlq);
}

void Bike::upd()
{
    stringstream ss;
    ss << "UPDATE Bike SET frame = "  << this->getFrame ();
    ss << ", backwheel = " << this->getBackWheel ();
    ss << ",frontwheel = " << this->getFrontWheel ();
    ss << ",bikegearing = " << this->getBikeGearing ();
    ss << ",wheelgearing = " << this->getWheelGearing ();
    ss << ",fronttire = " << this->getFrontTire ();
    ss << ",backtire = " << this->getBackTire ();
    ss << ",computer = " << this->getComputer ();
    ss << ",assemblydate = '" << this->getDate().toString("yyyy-MM-dd");
    ss << "' WHERE id = " << this->getOid() << ";";

    string sqlq;
    getline(ss, sqlq);
    DbConn::Instance()->set (sqlq);
//     int frame;
//     int backWheel;
//     int frontWheel;
//     int bikeGearing;
//     int wheelGearing;
//     int frontTire;
//     int backTire;
//     int computer;
//     QDate date;

}
