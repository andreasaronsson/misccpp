#include "Preferences.h"
using namespace std;

Preferences* Preferences::prefInstance = 0;

//constructors                                                                        
// indended for creating objects from db
Preferences::Preferences()
{
    QSqlQuery query;
    query = DbConn::Instance()->get("SELECT distance, height, speed, temp, weight, width, presentation FROM preferences;");
    QSqlQuery query2;
    query2 = DbConn::Instance()->get("SELECT dateorder, monthformat, weekstarts, dayleadingzeroes, century FROM dateformat;");
    if (query.next() && query2.next())
    {
      //Skapa nytt objekt
        this->distance = query.value(0).toString();
        this->height = query.value(1).toString();
        this->speed = query.value(2).toString();
        this->temperature = query.value(3).toString();
        this->weight = query.value(4).toString();
        this->width = query.value(5).toString();
        this->presentation = query.value(6).toString();
        
        this->dateOrder = query2.value(0).toString();
        this->monthFormat = query2.value(1).toString();
        this->weekStarts = query2.value(2).toString();
        this->dayLeadingZeroes = query2.value(3).toBool();
        this->century = query2.value(4).toInt();
       // Preferences::Preferences(query.value(0).toString(), query.value(1).toString(), query.value(2).toString(), query.value(3).toString(), query.value(4).toString(), query.value(5).toString(), query2.value(0).toString(), query2.value(1).toString(), query2.value(2).toString(), query2.value(3).toBool(), query2.value(4).toInt());
    }
}

Preferences* Preferences::Instance()
{
  if (prefInstance==0) {
    prefInstance =  new Preferences;
  }
  return prefInstance;
}

QString Preferences::getDistance ()
{
    return distance; 
}

void Preferences::setDistance (QString newDistance)
{
    this->distance = newDistance;
}

bool Preferences::getDistanceKm()
{

    if (this->distance == "km") return true;
    return false;
}

void Preferences::setDistanceKm (bool newDistanceKm)
{
    if (newDistanceKm) this->distance = "km";    
}

bool Preferences::getDistanceMiles()
{
    if (this->distance == "miles") return true;
    return false;
}

void Preferences::setDistanceMiles (bool newDistanceMiles)
{
    if (newDistanceMiles) this->distance = "miles";
}


QString Preferences::getHeight ()
{
    return height; 
}

void Preferences::setHeight (QString newHeight)
{
    this->height = newHeight;
}

bool Preferences::getHeightMeters()
{
    if (this->height == "meters") return true;
    return false;
}

void Preferences::setHeightMeters (bool newHeightMeters)
{
    if (newHeightMeters) this->height = "meters";
}

bool Preferences::getHeightFeet()
{
    if (this->height == "feet") return true;
    return false;
}

void Preferences::setHeightFeet (bool newHeightFeet)
{
    if (newHeightFeet) this->height = "feet";
}


QString Preferences::getSpeed ()
{
    return speed; 
}

void Preferences::setSpeed (QString newSpeed)
{
    this->speed = newSpeed;
}

bool Preferences::getSpeedKmh()
{
    if (this->speed == "km/h") return true;
    return false;
}

void Preferences::setSpeedKmh (bool newSpeedKmh)
{
    if (newSpeedKmh) this->speed = "km/h";
}

bool Preferences::getSpeedMph()
{
    if (this->speed == "mph") return true;
    return false;
}

void Preferences::setSpeedMph (bool newSpeedMph)
{
    if (newSpeedMph) this->speed = "mph";
}


QString Preferences::getTemperature ()
{
    return temperature; 
}

void Preferences::setTemperature (QString newTemperature)
{
    this->temperature = newTemperature;
}

bool Preferences::getTemperatureDegreesC()
{
    if (this->temperature == "C") return true;
    return false;
}

void Preferences::setTemperatureDegreesC (bool newTemperatureDegreesC)
{
    if (newTemperatureDegreesC) this->temperature = "C";
}

bool Preferences::getTemperatureDegreesF()
{
    if (this->temperature == "F") return true;
    return false;
}

void Preferences::setTemperatureDegreesF (bool newTemperatureDegreesF)
{
    if (newTemperatureDegreesF) this->temperature = "F";
}


QString Preferences::getWeight ()
{
    return this->weight; 
}

void Preferences::setWeight (QString newWeight)
{
    this->weight = newWeight;
}

bool Preferences::getWeightKilo()
{
    if (this->weight == "kilo") return true;
    return false;
}

void Preferences::setWeightKilo (bool newWeightKg)
{
    if (newWeightKg) this->weight = "kilo";
}

bool Preferences::getWeightPound()
{
    if (this->weight == "pounds") return true;
    return false;
}

void Preferences::setWeightPound (bool newWeightPound)
{
    if (newWeightPound) this->weight = "pounds";
}



QString Preferences::getWidth ()
{
    return this->width; 
}

void Preferences::setWidth (QString newWidth)
{
    this->width = newWidth;
}

bool Preferences::getWidthCm()
{
    if (this->width == "cm") return true;
    return false;
}

void Preferences::setWidthCm (bool newWidthCm)
{
    if (newWidthCm) this->width = "cm";
}

bool Preferences::getWidthInch()
{
    if (this->width == "inch") return true;
    return false;
}

void Preferences::setWidthInch (bool newWidthInch)
{
    if (newWidthInch) this->width = "inch";
}

QString Preferences::getPresentation ()
{
    return this->presentation; 
}

void Preferences::setPresentation (QString newPresentation)
{
    this->presentation = newPresentation;
}

bool Preferences::getPresentationBikeUsed()
{
    if (this->presentation == "bikeused") return true;
    return false;
}

void Preferences::setPresentationBikeUsed (bool newPresentationBikeUsed)
{
    if (newPresentationBikeUsed) this->presentation = "bikeused";
}

bool Preferences::getPresentationDistance()
{
    if (this->presentation == "distance") return true;
    return false;
}

void Preferences::setPresentationDistance (bool newPresentationDistance)
{
    if (newPresentationDistance) this->presentation = "distance";
}

bool Preferences::getPresentationTime()
{
    if (this->presentation == "time") return true;
    return false;
}

void Preferences::setPresentationTime (bool newPresentationTime)
{
    if (newPresentationTime) this->presentation = "time";
}

bool Preferences::getPresentationTrail()
{
    if (this->presentation == "trail") return true;
    return false;
}

void Preferences::setPresentationTrail (bool newPresentationTrail)
{
    if (newPresentationTrail) this->presentation = "trail";
}

QString Preferences::getDateOrder ()
{
    return dateOrder; 
}

void Preferences::setDateOrder (QString newDateOrder)
{
    this->dateOrder = newDateOrder;
}

bool Preferences::getDateOrderMdy()
{
    if (this->dateOrder == "MDY") return true;
    return false;
}

void Preferences::setDateOrderMdy (bool newDateOrderMdy)
{
    if (newDateOrderMdy) this->dateOrder = "MDY";
}

bool Preferences::getDateOrderDmy()
{
    if (this->dateOrder == "DMY") return true;
    return false;
}

void Preferences::setDateOrderDmy (bool newDateOrderDmy )
{
    if (newDateOrderDmy ) this->dateOrder = "DMY";
}

bool Preferences::getDateOrderYmd()
{
    if (this->dateOrder == "YMD") return true;
    return false;
}

void Preferences::setDateOrderYmd (bool newDateOrderYmd )
{
    if (newDateOrderYmd ) this->dateOrder = "YMD";
}


QString Preferences::getMonthFormat ()
{
    return this->monthFormat; 
}

void Preferences::setMonthFormat (QString newMonthFormat)
{
    this->monthFormat = newMonthFormat;
}

bool Preferences::getMonthFormatFull()
{
    if (this->monthFormat == "full") return true;
    else return false;
}

void Preferences::setMonthFormatFull (bool newMonthFormatFull)
{
    if (newMonthFormatFull) this->monthFormat = "full";
}

bool Preferences::getMonthFormatShort()
{
    if (this->monthFormat == "short") return true;
    else return false;
}

void Preferences::setMonthFormatShort (bool newMonthFormatShort)
{
    if (newMonthFormatShort) this->monthFormat = "short";
}

bool Preferences::getMonthFormatNumber()
{
    if (this->monthFormat == "number") return true;
    return false;
}

void Preferences::setMonthFormatNumber (bool newMonthFormatNumber)
{
    if (newMonthFormatNumber) this->monthFormat = "number";
}


QString Preferences::getWeekStarts ()
{
    return this->weekStarts; 
}

void Preferences::setWeekStarts (QString newWeekStarts)
{
    this->weekStarts = newWeekStarts;
}

bool Preferences::getWeekStartsMonday()
{
    if (this->weekStarts == "monday") return true;
    return false;
}

void Preferences::setWeekStartsMonday (bool newWeekStartsMonday)
{
    if (newWeekStartsMonday) this->weekStarts = "monday";
}

bool Preferences::getWeekStartsSunday()
{
    if (this->weekStarts == "sunday") return true;
    return false;
}

void Preferences::setWeekStartsSunday (bool newWeekStartsSunday)
{
    if (newWeekStartsSunday) this->weekStarts = "sunday";
}

bool Preferences::getDayLeadingZeroes ()
{
    return this->dayLeadingZeroes; 
}

void Preferences::setDayLeadingZeroes (bool newDayLeadingZeroes)
{
    this->dayLeadingZeroes = newDayLeadingZeroes;
}

bool Preferences::getDayLeadingZeroes1()
{
    if (this->dayLeadingZeroes) return true;
    return false;
}

void Preferences::setDayLeadingZeroes1 (bool newDayLeadingZeroes1)
{
    if (newDayLeadingZeroes1) this->dayLeadingZeroes = TRUE;
}

bool Preferences::getDayLeadingZeroes01()
{
    if (!this->dayLeadingZeroes) return true;
    return false;
}

void Preferences::setDayLeadingZeroes01 (bool newDayLeadingZeroes01)
{
    if (newDayLeadingZeroes01) this->dayLeadingZeroes = FALSE;
}


int Preferences::getCentury ()
{
    return this->century; 
}

void Preferences::setCentury (int newCentury)
{
    this->century = newCentury;
}

bool Preferences::getCentury90()
{
    if (this->century == 2) return true;
    return false;
}

void Preferences::setCentury90 (bool newCentury90)
{
    if (newCentury90) this->century = 2;
}

bool Preferences::getCentury2000()
{
    if (this->century == 4) return true;
    return false;
}

void Preferences::setCentury2000 (bool newCentury2000)
{
    if (newCentury2000) this->century = 4;
}

void Preferences::save()
{
    DbConn::Instance()->set("DELETE FROM preferences;");
    DbConn::Instance()->set("DELETE FROM dateformat;");
    DbConn::Instance()->set("INSERT INTO preferences(distance, height, speed, temp, weight, width, presentation) VALUES('"+this->distance+"', '"+this->height+"', '"+this->speed+"', '"+this->temperature+"', '"+this->weight+"', '"+this->width+"', '"+this->presentation+"');");
    
    QString zeroResult;
    if ( this->dayLeadingZeroes ) zeroResult = "True";
    else zeroResult = "False";    
    
    DbConn::Instance()->set("INSERT INTO dateformat(dateorder, monthformat, weekstarts, dayleadingzeroes, century) VALUES('"+this->dateOrder+"', '"+this->monthFormat+"', '"+this->weekStarts+"', "+zeroResult+", "+QString::number(this->century)+");");
    //DBConn *db = new DBConn();
  //db->set (this);
}

