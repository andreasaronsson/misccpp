/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you want to add, delete, or rename functions or slots, use
** Qt Designer to update this file, preserving your code.
**
** You should not define a constructor or destructor in this file.
** Instead, write your code in functions called init() and destroy().
** These will automatically be called by the form's constructor and
** destructor.
*****************************************************************************/


void SpecialReportForm::init()
{
    this->setWFlags (Qt::WDestructiveClose);
    toDate->setDate(QDate::currentDate());
    fromDate->setDate(QDate::currentDate().addYears(-1));
    yearBox->setValue(QDate::currentDate().year());
    
    //DbConn* db = DbConn::Instance();
    //db->changeDb("bapptest");
    
   Preferences* pref = Preferences::Instance();
    
    if (pref->getDateOrderMdy()) {
        fromDate->setOrder(QDateEdit::MDY);
        toDate->setOrder(QDateEdit::MDY);
    } else if (pref->getDateOrderDmy()) {
        fromDate->setOrder(QDateEdit::DMY);
        toDate->setOrder(QDateEdit::DMY);
    } else if (pref->getDateOrderYmd()) {
        fromDate->setOrder(QDateEdit::YMD);
        toDate->setOrder(QDateEdit::YMD);
    }
}

void SpecialReportForm::changeReport()
{
    int currentReport = reportList->currentItem ();
    if (currentReport == 0 || currentReport == 3 || currentReport == 6 || currentReport == 7) {
        reportStack->raiseWidget(0);
    } else if (currentReport == 1 || currentReport == 5 || currentReport == 8) {
        reportStack->raiseWidget(1);
    } else {
        reportStack->raiseWidget(2);
    }
}


void SpecialReportForm::createReport()
{
    ReportDisplay* display = new ReportDisplay();
    Report reportInstance = Report(fromDate->date(), toDate->date(), yearBox->value());
    QString fileName, reportResult;
    display->show();
  
    switch(reportList->currentItem()) {
    case 0:
        // Full report
        fileName = QString("FullReport");
        reportInstance.fullRep();
        break;
    case 1:
        // Month report
         fileName = QString("MonthReport");
         reportInstance.monthRep();
        break;
    case 2:
        // Summary report
         fileName = QString("SummaryReport");
         reportInstance.summaryRep();
        break;
    case 3:
         // Tire report 
         fileName = QString("TireReport");
        reportInstance.tireRep();
        break;
    case 4:
        // Trail report
        fileName = QString("TrailReport");
        reportInstance.trailRep(); 
        break;
    case 5:
        // Week report
         fileName = QString("WeekReport");
        reportInstance.weekRep();
        break;
    case 6:
        // Weekday report
         fileName = QString("WeekdayReport");
        reportInstance.weekdayRep();
        break;
    case 7:
        // Wheel report
         fileName = QString("WheelReport");
        reportInstance.wheelRep();
        break;
    case 8:
        // Year report
         fileName = QString("YearReport");
        reportInstance.yearRep();
        break;
    default:
        QMessageBox::information( this, "Error", "No report could be generated" );
        break;
    }    
    reportResult = reportInstance.getResult();
    display->writeReport(reportResult,fileName);
}


void SpecialReportForm::checkFromDate()
{
    if (fromDate->date() > toDate->date() ) {
        fromDate->setDate(toDate->date());
    }
}


void SpecialReportForm::checkToDate()
{
if (toDate->date() < fromDate->date() ) {
        toDate->setDate(fromDate->date());
    }
}



void SpecialReportForm::killBill()
{
 this->close(1);
}
