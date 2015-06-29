#ifndef USER_H
#define USER_H
#include <string>
#include "DbConn.h"
using namespace std;
class User 
{
 
 public:
    //constructors
    User();
    User(string, int, int);
    User(int, string, int, int);

    int getOid ();
    void setOid (int);
    string getName ();
    void setName (string);
    int getPrefSet ();
    void setPrefSet (int);
    int getDateSet ();
    void setDateSet (int);
    void save();

 private:
    int oid;
    string name;
    int prefSet;
    int dateSet;
    
};
#endif
