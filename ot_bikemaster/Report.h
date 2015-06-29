#ifndef REPORT_H
#define REPORT_H
#include "DbConn.h"

using namespace std;
class Report
{
 public:
    //constructors
    Report(QDate, QDate, int);

    // accessors
    QDate getStart ();
    void setStart (QDate);
    QDate getStop ();
    void setStop (QDate);
    int getYear ();
    void setYear (int);
    QString getResult ();

    // "stamp" methods fills member result with sql results
    void fullRep();
    void monthRep();
    void summaryRep();
    void tireRep();
    void trailRep();
    void weekRep();
    void weekdayRep();
    void wheelRep();
    void yearRep();
    void combinedRep(string);
    string cnv(long);
    void head(string);
    void line80(string);
    QString fixLength(QString, uint, char, bool);

 private:
    void setResult (QString);
    QDate start;
    QDate stop;
    int year;
    QString result;
};
#endif
