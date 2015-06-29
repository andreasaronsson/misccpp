#include "DbConn.h"
#include <string>

DbConn* DbConn::dbConn = 0;

DbConn* DbConn::Instance() 
{
    if (dbConn == 0) {  
	dbConn = new DbConn;
    }
    return dbConn;
}

//constructor
DbConn::DbConn()
{
  hostName = "db.informatik.gu.se";
  dbName = "ot04-5";
  userName = "ot04-5";
  password = "mYcXVX6";
  defaultDb = QSqlDatabase::addDatabase("QPSQL7");
  this->defaultDb->setHostName(this->hostName);
  this->defaultDb->setDatabaseName(this->dbName);
  this->defaultDb->setUserName(this->userName);
  this->defaultDb ->setPassword(this->password);
  
  if ( ! this->defaultDb->open() ) {
      cerr << "FAILED CONNECT!!" << endl; 
  }

}

bool DbConn::changeDb(string newDbName)
{

    this->dbName = newDbName;
    QSqlQuery query( "CREATE DATABASE " + QString( newDbName )+ " TEMPLATE \"fjaddmall\"", defaultDb); 

    if ( query.isActive() ) { 
	cerr << "JAWOHL! GETRAG GEFOLGT!!" << endl;
    }
    
    currDb = QSqlDatabase::addDatabase("QPSQL7");
    this->currDb->setHostName(this->hostName);
    this->currDb->setDatabaseName(this->dbName);
    this->currDb->setUserName(this->userName);
    this->currDb ->setPassword(this->password);

    if ( ! this->currDb->open() ) {
	cerr << "FAILED CONNECT!!" << endl;
	return false;
    }
    
    return true;

}

bool DbConn::close()
{

    if(this->currDb->isOpen()){
	this->currDb->close();
	return true;
    }
    else{
	return false;
    }

}

void DbConn::set(string sql)
{
    QSqlQuery query(sql);
    
    if (!query.isActive()) {
	cerr << endl << "ERRATIC QUERY !! !!" << endl;
	exit(0);
    }
    cerr <<  "I queried this:" << endl << query.executedQuery () << endl;
}

QSqlQuery DbConn::get(string sql)
{
    QSqlQuery query(sql);
    cout << sql + "\n";  
    if (!query.isActive()) {
	cerr << endl << "ERRATIC QUERY !! !!" << endl;
	exit(0);
    }
    // test jox
    //while(query.next()){
    // cout << query.value(0).toString()+"\n";
    //}
    return query;

}


