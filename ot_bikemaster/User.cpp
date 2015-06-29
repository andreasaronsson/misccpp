#include <sstream>
#include <vector>
#include "User.h"

//constructors                                                                            
User::User ()
{
}
// indended for creating objects from db                                                 
User::User (int newOid,
            string newName,
            int newPrefSet,
	    int newDateSet)
{
    oid = newOid;
    name = newName;
    prefSet = newPrefSet;
    newDateSet = dateSet;

}
//intended for creating objects by user
User::User(string newName,
	   int newPrefSet,
	   int newDateSet)
{
    oid = 0; // kanske -1?
    name = newName;
    prefSet = newPrefSet;
    dateSet = newDateSet;
}
int User::getOid ()
{
    return oid; 
}
void User::setOid (int newOid)
{
        oid = newOid;
}
string User::getName()
{
    return name; 
}
void User::setName(string newname)
{
    name = newname;
}
int User::getPrefSet ()
{
    return prefSet; 
}
void User::setPrefSet (int newPrefSet)
{
    prefSet = newPrefSet;
}
int User::getDateSet ()
{
    return dateSet; 
}
void User::setDateSet (int newDateSet)
{
    dateSet = newDateSet;
}
void User::save () 
{
//     string sqlq;
//     DbConn db;
//     db.set(sqlq);
}
