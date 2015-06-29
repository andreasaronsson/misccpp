
#include "CalenderDay.h"

CalenderDay::CalenderDay(QTable *t, EditType et) : QTableItem(t, et)
{
    dayNr = 0;
    nrOfLines = 0;
}

CalenderDay::CalenderDay(QTable *t, 
    EditType et, 
    QColor c) : QTableItem( t, et)
{
    color = c;
    dayNr = 0;
    nrOfLines = 0;
}

CalenderDay::CalenderDay(QTable *t, 
    EditType et, 
    QColor c,
    const QString txt) : QTableItem( t, et, txt)
{
    color = c;
    dayNr = 0;
    nrOfLines = 0;
}

CalenderDay::~CalenderDay()
{
}

int CalenderDay::alignment() const
{
    return Qt::AlignLeft | Qt::AlignTop;
}

void CalenderDay::paint( QPainter *p, const QColorGroup &cg, const
       QRect &cr, bool selected )
{
   
   QColorGroup g(cg);
   g.setColor( QColorGroup::Base, color );
   QTableItem::paint(p,g,cr,selected);
}

void CalenderDay::setDayNr(int n) 
{
   dayNr = n;
}

void CalenderDay::setNrOfLines(int n) 
{
   nrOfLines = n;
}

int CalenderDay::getDayNr() 
{
   return dayNr;
}

int CalenderDay::getNrOfLines() 
{
   return nrOfLines;
}


