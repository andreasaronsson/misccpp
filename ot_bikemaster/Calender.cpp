#include "Calender.h"

Calender::Calender(QWidget *parent, const char *name, WeekStarts wS, bool dLZ) : QTable(6, 7, parent, name)
{
    QFont serifFont( "Times", 10);
    setLeftMargin(2);
    setDragEnabled(false);
    setFont(serifFont);

    weekStarts = wS;
    dayLeadingZero = dLZ;
    
    int i;
    for (i = 0; i < 7; i++) {
      setColumnStretchable(i, true);
    }

    for (i = 0; i < 6; i++) {
      setRowStretchable(i, true);
    }
    
    QObject::connect(this, 
       SIGNAL(doubleClicked(int, int, int, const QPoint&)), 
       this,
       SLOT(selectedLine(int, int, int, const QPoint&)));
}

Calender::~Calender()
{
}

int Calender::getNrOfDays() 
{
   return nrOfDays;
}

int Calender::getFirstDay() 
{
   return firstDay;
}

void Calender::setYear(int y) 
{
   year = y;
}

void Calender::setMonth(int m) 
{
   month = m;
}

int Calender::getYear() 
{
   return year;
}

int Calender::getMonth() 
{
   return month;
}

void Calender::setWeekStarts(WeekStarts wS)
{
   weekStarts = wS;
}

WeekStarts Calender::getWeekStarts()
{
   return weekStarts;
}

void Calender::setDayLeadingZero(bool dLZ)
{
  dayLeadingZero = dLZ;
}

bool Calender::getDayLeadingZero()
{
  return dayLeadingZero;
}

void Calender::setupView(int y, int m)
{
    CalenderDay *cDay = NULL;
    QColor white(255, 255, 255);
    QColor gray(240, 240, 240);
    QString dayNrStr;
    QDate *date = new QDate(y, m, 1);

    int i, j, k, squareNr, dayNr, row, col;

    char *days[] = {
      "Monday",
      "Tuesday",
      "Wednesday",
      "Thursday",
      "Friday",
      "Saturday",
      "Sunday"
    };

    i = 0;
    k = 0;
    j = 7;
    squareNr = 1;
    dayNr = 1;
    nrOfDays = date->daysInMonth();
    firstDay = date->dayOfWeek();
    year = y;
    month = m;
    
    if (weekStarts == SUNDAY) {
      horizontalHeader()->setLabel(0, tr(days[6]));
      firstDay += 1;
      i = 1;
    }

    for (; i < j; i++, k++) {
      horizontalHeader()->setLabel(i, tr(days[k]));
    }
 
    for (row = 0; row < numRows(); row++) {
      for (col = 0; col < numCols(); col++) {
 if ((squareNr >= firstDay) && (dayNr <= nrOfDays)) {
   if ((dayLeadingZero == true) && (dayNr <= 9)) {
     dayNrStr += "0";
   }
   dayNrStr += QString::number(dayNr);
   cDay = new CalenderDay(this, QTableItem::Never, white, dayNrStr);
   dayNrStr = "";
   cDay->setDayNr(dayNr++);
   
   setItem(row, col, cDay);
 } else {
   cDay = new CalenderDay(this, QTableItem::Never, gray);
   setItem(row, col, cDay);
 }
 //setRowHeight(row, 80);    //Inte nödv. då col och rows är stretchatble
 ++squareNr;
      }
    }
}

void Calender::purgeView()
{
  int row, col;
  
  for (col = 0; col < numCols(); col++) {
      for (row = 0; row < numRows(); row++) {
 delete (CalenderDay *) item(row, col);
      }
  }
}

void Calender::addDayLine(int dayNr, QString s)
{
  QString txtLine;
  CalenderDay *cDay = NULL;
  int row, col;

  assert(dayNr > 0 && dayNr <= nrOfDays);

  s.replace("\n","");  //Ta bort alla newline ur strängen...

  //hitta ROW och COL baserat på dag NR, mycket enkel lösning...
  for (row = 0; row < numRows(); row++) {
    for (col = 0; col < numCols(); col++) {
      cDay = (CalenderDay *) item(row, col);
      if (cDay->getDayNr() == dayNr) {

 txtLine = cDay->text();

 txtLine.append("\n" + s);
 cDay->setText(txtLine);
 cDay->setNrOfLines(cDay->getNrOfLines() + 1);
      }
    }
  }
}

void Calender::addDayLine(int row, int col, QString s)
{
  QString txtLine;
  CalenderDay *cDay = NULL;

  assert((row >= 0 && row < numRows()) &&  (col >= 0 && col < numCols()));

  cDay = (CalenderDay *) item(row, col);
  txtLine = cDay->text();
  txtLine.append("\n" + s);
  cDay->setText(txtLine);
  cDay->setNrOfLines(cDay->getNrOfLines() + 1);
}

void Calender::clearDay(int dayNr)
{
  QString txtLine;
  CalenderDay *cDay = NULL;
  int row, col, pos;

  //hitta ROW och COL baserat på dag NR, mycket enkel lösning...
  for (row = 0; row < numRows(); row++) {
    for (col = 0; col < numCols(); col++) {
      cDay = (CalenderDay *) item(row, col);
      if (cDay->getDayNr() == dayNr) {
 if (cDay->getNrOfLines() != 0) {
   txtLine = cDay->text();
   pos = txtLine.find("\n");
   txtLine.remove(pos, txtLine.length() - pos);
   cDay->setText(txtLine);
   cDay->setNrOfLines(0);
 }
      }
    }
  }
}

CalenderDay* Calender::getDay(int dayNr)
{
  CalenderDay *cDay = NULL;
  int row, col;

  assert(dayNr > 0 && dayNr <= nrOfDays);

  //hitta ROW och COL baserat på dag NR, mycket enkel lösning...
  
  for (row = 0; row < numRows(); row++) {
    for (col = 0; col < numCols(); col++) {
      cDay = (CalenderDay *) item(row, col);
      if (cDay->getDayNr() == dayNr) {
 return cDay;
      }
    }
  }
  return NULL;
}

CalenderDay* Calender::getDay(int row, int col)
{
  CalenderDay *cDay = NULL;

  assert((row >= 0 && row < numRows()) &&  (col >= 0 && col < numCols()));  
  cDay = (CalenderDay *) item(row, col);
  return cDay;
}

void Calender::selectedLine(int row, int col, int button, const QPoint& qP)
{
  CalenderDay *cDay;
  int yPos, btn, dayNr, nrOfLines, rowHeight, lineHeight, lineNr;
  
  btn = button;    //Ta bort...

  cDay = getDay(row, col);
  dayNr = cDay->getDayNr();
  rowHeight = this->rowHeight(row);
  nrOfLines = cDay->getNrOfLines();
  lineHeight = 18;
  
  yPos = qP.y() - (row * rowHeight);
  lineNr = yPos / lineHeight;

  if ( (dayNr != 0) && (lineNr > 0) && (lineNr <= nrOfLines)) {
    emit lineSelected(dayNr, lineNr, nrOfLines);
  } else if ((dayNr != 0) && (nrOfLines == 0)) {
    emit lineSelected(dayNr, lineNr, nrOfLines);
  }
}
