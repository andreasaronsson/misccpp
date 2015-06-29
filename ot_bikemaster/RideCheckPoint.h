#ifndef RIDECHECKPOINT_H
#define RIDECHECKPOINT_H
#include "DbConn.h"

using namespace std;
class RideCheckPoint {
 public:
    //constructors                                                                                  
    RideCheckPoint();
    RideCheckPoint(int, int, QTime&);

    //methods                                                                                  
    int getRide ();
    void setRide (int);
    int getCheckPoint ();
    void setCheckPoint (int);
    QTime& getCheckTime ();
    void setCheckTime (QTime&);
    void save();
    void upd();

 private:
    int ride;
    int checkPoint;
    QTime checkTime;

};

#endif
