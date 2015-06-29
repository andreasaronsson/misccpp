#ifndef CALENDER_H
#define CALENDER_H

#include <qtable.h>
#include <qdatetime.h>
#include <qstring.h>
#include <qfont.h>
#include <assert.h>
#include "CalenderDay.h"

typedef enum WeekStarts {
  MONDAY = 0,
  SUNDAY = 1
};

class Calender : public QTable
{
  Q_OBJECT

public:
  Calender(QWidget *parent = 0, const char *name = 0, WeekStarts wS = MONDAY, bool dLZ = false);
  ~Calender();

  void setupView(int y = 2000, int m = 1);
  void purgeView();
  void addDayLine(int, QString);
  void addDayLine(int, int, QString);
  void clearDay(int);

  CalenderDay* getDay(int);
  CalenderDay* getDay(int, int);

  int getNrOfDays();
  int getFirstDay();
  
  void setYear(int);
  void setMonth(int);
  int getYear();
  int getMonth();

  void setDayLeadingZero(bool);
  bool getDayLeadingZero();

  void setWeekStarts(WeekStarts);
  WeekStarts getWeekStarts();
   
 private:
  int nrOfDays;
  int firstDay;
  int year;
  int month;

  WeekStarts weekStarts;
  bool dayLeadingZero;

 public slots:
   void selectedLine(int, int, int, const QPoint&);
   
signals:
    void lineSelected(int, int, int);
};

#endif
