#ifndef CALENDERDAY_H
#define CALENDERDAY_H

#include <qtable.h>
#include <qstring.h>

class CalenderDay : public QTableItem
{
 public:
   CalenderDay(QTable *t, EditType et);
   CalenderDay(QTable *t, EditType et, QColor c);
   CalenderDay(QTable *t, EditType et, QColor c, const QString txt);
   ~CalenderDay();

   void setDayNr(int);
   void setNrOfLines(int);

   int getDayNr();
   int getNrOfLines();
   
 private:
   int CalenderDay::alignment() const;
   void CalenderDay::paint( QPainter *p, const QColorGroup &cg,
			       const QRect &cr, bool selected );
   QColor color;
   int dayNr;
   int nrOfLines;
};

#endif
