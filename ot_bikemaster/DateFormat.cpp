#include "DateFormat.h"
#include <iostream>

//constructors
DateFormat::DateFormat(){}
DateFormat::DateFormat (int newOid, 
			string newOrder, 
			string newMonthFormat, 
			string newWeekStarts, 
			bool newDayLeadingZeros, 
			int newCentury)
{
    oid = newOid;   
    order = newOrder;
    monthFormat = newMonthFormat;
    weekStarts = newWeekStarts;
    dayLeadingZeros = newDayLeadingZeros;
    century = newCentury;
}
DateFormat::DateFormat (string newOrder, 
			string newMonthFormat, 
			string newWeekStarts, 
			bool newDayLeadingZeros, 
			int newCentury)
{
    oid = 0; // -1 illi   
    order = newOrder;
    monthFormat = newMonthFormat;
    weekStarts = newWeekStarts;
    dayLeadingZeros = newDayLeadingZeros;
    century = newCentury;
}
int DateFormat::getOid ()
{
    return oid; 
}
void DateFormat::setOid (int newOid)
{
    oid = newOid;
}
string DateFormat::getOrder ()
{
    return order; 
}
void DateFormat::setOrder (string newOrder)
{
    order = newOrder;
}
string DateFormat::getMonthFormat ()
{
    return monthFormat; 
}
void DateFormat::setMonthFormat (string newMonthFormat)
{
    monthFormat = newMonthFormat;
}
string DateFormat::getWeekStarts ()
{
    return weekStarts; 
}
void DateFormat::setWeekStarts (string newWeekStarts)
{
    weekStarts = newWeekStarts;
}
bool DateFormat::getDayLeadingZeros ()
{
    return dayLeadingZeros; 
}
void DateFormat::setDayLeadingZeros (bool newDayLeadingZeros)
{
    dayLeadingZeros = newDayLeadingZeros;
}
int DateFormat::getCentury ()
{
    return century; 
}
void DateFormat::setCentury (int newCentury)
{
    century = newCentury;
}
void DateFormat::save () 
{
    string sqlq;
    DbConn db;
    db.set (sqlq);
}
