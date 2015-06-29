/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/

void MainForm::init()
{  
    
    QDate date = QDate::currentDate();
    QVBoxLayout *calLayout = new QVBoxLayout(CalenderFrame);
    int y, m;
    
    //Skapa ny kalender...
    calender = new Calender(CalenderFrame);
    calender->setYear(date.year());
    calender->setMonth(date.month());
    
    //calender->setFixedSize(810, 530);
    calender->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    calLayout->addWidget(calender);
        
    y = calender->getYear();
    m = calender->getMonth();
    spinBoxYear->setValue(y);
    comboBoxMonth->setCurrentItem(m - 1);
    
    QObject::connect(calender, SIGNAL(lineSelected(int, int, int)), this, SLOT(showRide(int, int, int)));
    QObject::connect(this, SIGNAL(updateCalender()), this, SLOT(fillCalender()));
    
    emit updateCalender();
}


void MainForm::destroy()
{
    //delete calender;
    ///dbconn->close();
    //delete dbconn;
    //delete rides;
}

void MainForm::pushButtonRight()
{
    int y, m;
    
    m = calender->getMonth();
    y = calender->getYear();
    
    if (m == 12) {
        m = 1;
        y += 1;
    } else {
        ++m;
    }
    calender->setYear(y);
    calender->setMonth(m);
    
    calender->purgeView();
    calender->setupView(y, m);    
    
    spinBoxYear->setValue(y);
    comboBoxMonth->setCurrentItem(m - 1);
    
    if (m != 1) {
        emit updateCalender();
    }
}

void MainForm::pushButtonLeft()
{
    int y, m;
    
    m = calender->getMonth(); 
    y = calender->getYear();
    if (m == 1) {
        m = 12;
        y -= 1;
    } else {
        --m;
    }
    calender->setYear(y);
    calender->setMonth(m);
    
    calender->purgeView();
    calender->setupView(y, m);    
    
    spinBoxYear->setValue(y);
    comboBoxMonth->setCurrentItem(m - 1);
    
    if (m != 12) {
        emit updateCalender();
    }
}

void MainForm::comboBox(int i)
{
    int y;
    
    y = calender->getYear();
    
    calender->setMonth(i + 1);
    calender->purgeView();
    calender->setupView(y,  i + 1);
    
    emit updateCalender();
}

void MainForm::spinBox(int v)
{
    int m;
    
    m = calender->getMonth();
    
    calender->setYear(v);
    calender->purgeView();
    calender->setupView(v,  m);
    
    emit updateCalender();
}

void MainForm::showRide(int dayNr, int lineNr, int nrOfLines)
{
    Rides *rides = new Rides(QDate(calender->getYear(), calender->getMonth(), dayNr));
    RideDataForm *rDForm = new RideDataForm();
    Ride *ride;
    
    rDForm->setCalender(calender);
    
    if (lineNr <= nrOfLines) {
        rDForm->setRide(rides->getItem(lineNr - 1), dayNr);
    } else {        
        ride = new Ride();
        ride->setDate(QDate(calender->getYear(), calender->getMonth(), dayNr));
cerr <<  ride->getOid();
        rDForm->setRide(ride, dayNr);
    }
    
    QObject::connect(rDForm, SIGNAL(updateCalender()), this, SLOT(fillCalender()) );
    rDForm->show();
}

void MainForm::fillCalender()
{
    Rides *rides;
    int d, i, y, m;
    
    // Hämta inställningar
    preferences = Preferences::Instance();
    
    //Sätt olika presentationsinställningar...
    if (preferences->getWeekStartsSunday()) {
        calender->setWeekStarts(SUNDAY);
    } else  {
        calender->setWeekStarts(MONDAY);        
    }
    calender->setDayLeadingZero(preferences->getDayLeadingZeroes());
    
    y = calender->getYear();
    m = calender->getMonth();
    calender->purgeView();
    calender->setupView(y, m);
      
    for (d = 1; d <= calender->getNrOfDays(); d++) {
        rides = new Rides(QDate(calender->getYear(), calender->getMonth(), d));
        
        for (i = 1; i <= rides->getSize(); i++) {
            if (preferences->getPresentationTime()) {
                calender->addDayLine(d, rides->getItem(i - 1)->getElapsedTime());
            } else if (preferences->getPresentationBikeUsed()) {
                Bikes *bikes = new Bikes(rides->getItem(i - 1)->getBike());
                Frames *frames = new Frames(bikes->getItem(0)->getFrame());
                calender->addDayLine(d, frames->getItem(0)->getName());

            } else if (preferences->getPresentationDistance()) {
                QString s;
                Trails *trails;
                trails = new Trails(rides->getItem(i - 1)->getTrail());
                calender->addDayLine(d, s.setNum( trails->getItem(0)->getDistance()));
                
            } else if (preferences->getPresentationTrail()) {
                Trails *trails;
                trails = new Trails(rides->getItem(i - 1)->getTrail());
                calender->addDayLine(d, trails->getItem(0)->getName());
            }
        }
    }
}


void MainForm::specialReport()
{
    SpecialReportForm *sprForm = new SpecialReportForm();
    sprForm->show();
}


void MainForm::helpHelpMenu()
{
        system("/usr/bin/firefox http://www.skip.informatik.gu.se/~fjadd");
}


void MainForm::cmbOpen()
{
    ReportForm *cbdForm = new ReportForm();
    cbdForm->show();
}


void MainForm::prefsOpen()
{
    prefWindow *pref = new prefWindow();
    pref->show();
}
