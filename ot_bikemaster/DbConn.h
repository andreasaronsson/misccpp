#ifndef DBCONN_H
#define DBCONN_H
#include <qapplication.h>
#include <iostream>
#include <qsqldatabase.h>
#include <qsqlquery.h>
#include <qstring.h>
#include <qdatetime.h>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

class DbConn 
{

 public:
    //constructors
    static DbConn* Instance();
    bool con();
    bool close();
    void set(string);
    QSqlQuery  get(string);
    bool changeDb(string);

 protected:
    DbConn();
    DbConn(string,string,string,string);
    DbConn(const DbConn&);
    DbConn& operator= (const DbConn&);
    //methods
    
 private:
    string hostName;
    string dbName;
    string userName;
    string password;
    QSqlDatabase* currDb;
    QSqlDatabase* defaultDb;
    static DbConn* dbConn;// = new DbConn();
};
#endif
