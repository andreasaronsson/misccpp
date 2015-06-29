/****************************************************************************
** ui.h extension file, included from the uic-generated form implementation.
**
** If you wish to add, delete or rename functions or slots use
** Qt Designer which will update this file, preserving your code. Create an
** init() function in place of a constructor, and a destroy() function in
** place of a destructor.
*****************************************************************************/
#include <iostream>

void RideDataForm::init()
{
    this->setWFlags (Qt::WDestructiveClose);
}

void RideDataForm::setRide( Ride *r, int dayNr )
{
    QString s, str, strHour, strMin, strSec, strBikeName, strTrailName;
    Preferences *preferences = Preferences::Instance();
    
    ride = r;
    
    bikes = new Bikes(ride->getBike());
    if (bikes->getSize() == 0) {
        bike = new Bike();
    } else {
        bike = bikes->getItem(0);
    }  
    ride->setBike(bike->getOid());  

    trails = new Trails();
    bikes = new Bikes();
    frames = new Frames();
    frontWheels = new Wheels("front");
    backWheels = new Wheels("back");
    tires = new Tires();
    computers = new Computers();
    bikeGearings = new Gearings("bike");
    wheelGearings = new Gearings("wheel");    


    if (preferences->getDateOrderMdy()) {
        dateEdit->setOrder(QDateEdit::MDY);
    } else if (preferences->getDateOrderDmy()) {
        dateEdit->setOrder(QDateEdit::DMY);
    } else if (preferences->getDateOrderYmd()) {
        dateEdit->setOrder(QDateEdit::YMD);
    }

    dateEdit->setDate(QDate(calender->getYear(), calender->getMonth(), dayNr));
   
    str = ride->getStartTime();
    strHour = str.section( ':', 0, 0 );
    strMin = str.section( ':', 1, 1 );
    strSec = str.section( ':', 2, 2 );
    startTimeEdit->setTime(QTime(strHour.toInt(), strMin.toInt(), strSec.toInt()));
    
    str = ride->getAmountOfSleep();
    strHour = str.section( ':', 0, 0 );
    strMin = str.section( ':', 1, 1 );
    strSec = str.section( ':', 2, 2 ); 
    amountOfSleepTimeEdit->setTime(QTime(strHour.toInt(), strMin.toInt(), strSec.toInt()));
    
    str = ride->getTrainingTime();
    strHour = str.section( ':', 0, 0 );
    strMin = str.section( ':', 1, 1 );
    strSec = str.section( ':', 2, 2 );     
    trainingTimeEdit->setTime(QTime(strHour.toInt(), strMin.toInt(), strSec.toInt()));
    
    str = ride->getElapsedTime();
    strHour = str.section( ':', 0, 0 );
    strMin = str.section( ':', 1, 1 );
    strSec = str.section( ':', 2, 2 );      
    elapsedTimeEdit->setTime(QTime(strHour.toInt(), strMin.toInt(), strSec.toInt()));
    
    odoBeforeLineEdit->setText(str.number(ride->getOdoBefore()));
    odoAfterLineEdit->setText(str.number(ride->getOdoAfter()));
    avgSpeedLineEdit->setText(str.number(ride->getAverageSpeed()));
    maxSpeedLineEdit->setText(str.number(ride->getMaxSpeed()));
  
    minTemperatureLineEdit->setText(str.number(ride->getMinTemp()));
    maxTemperatureLineEdit->setText(str.number(ride->getMaxTemp()));
      
    if (ride->getTempData() == TRUE) {
        tempCheckBox->setChecked(TRUE);
    } else {
        tempCheckBox->setChecked(FALSE); 
    }
      
    ratingComboBox->insertItem("Easy");
    ratingComboBox->insertItem("Hard");
    ratingComboBox->insertItem("Very hard");
    ratingComboBox->insertItem("Extreme");
      
    trainingTypeComboBox->insertItem("Down hill");
    trainingTypeComboBox->insertItem("Offroad");
    trainingTypeComboBox->insertItem("Sandy beach");
    trainingTypeComboBox->insertItem("Mountain terrain");
      
    int i;
    for (i = 0; i < trails->getSize(); i++) {
        strTrailName = trails->getItem(i)->getName();
        trailComboBox->insertItem(strTrailName);
      
        if (ride->getTrail() == trails->getItem(i)->getOid()) {
            trailComboBox->setCurrentItem(i);   
        }        
    }
    
    for (i = 0; i < ratingComboBox->count(); i++ ) {
        s = ride->getRating();
        ratingComboBox->setCurrentItem(i); 
        if (s.compare(ratingComboBox->currentText()) == 0) {
            break;
        }
    }
    for (i = 0; i < trainingTypeComboBox->count(); i++ ) {
        s = ride->getType();
        trainingTypeComboBox->setCurrentItem(i); 
        if (s.compare(trainingTypeComboBox->currentText()) == 0) {
            break;
        }
    }

    
    // Bike tab...    
    for (i = 0; i < frames->getSize(); i++) {
        frameComboBox->insertItem(frames->getItem(i)->getName());
        
        if (bike->getFrame() == frames->getItem(i)->getOid()) {
            frameComboBox->setCurrentItem(i);        
        }
    }
    for (i = 0; i < frontWheels->getSize(); i++) {
        frontWheelComboBox->insertItem(frontWheels->getItem(i)->getName());
        
        if (bike->getFrontWheel() == frontWheels->getItem(i)->getOid()) {
            frontWheelComboBox->setCurrentItem(i);        
        } 
    } 
    
    for (i = 0; i < backWheels->getSize(); i++) {
        backWheelComboBox->insertItem(backWheels->getItem(i)->getName());
        
        if (bike->getBackWheel() == backWheels->getItem(i)->getOid()) {
            backWheelComboBox->setCurrentItem(i);        
        } 
    }
    
    for (i = 0; i < tires->getSize(); i++) {
        frontTireComboBox->insertItem(tires->getItem(i)->getName());
        backTireComboBox->insertItem(tires->getItem(i)->getName());
        
        if (bike->getFrontTire() == tires->getItem(i)->getOid()) {
            frontTireComboBox->setCurrentItem(i);        
        }         
        
        if (bike->getBackTire() == tires->getItem(i)->getOid()) {
            backTireComboBox->setCurrentItem(i);        
        }  
    }    
    
    for (i = 0; i < computers->getSize(); i++) {
        computerComboBox->insertItem(computers->getItem(i)->getName());
        
        if (bike->getComputer() == computers->getItem(i)->getOid()) {
            computerComboBox->setCurrentItem(i);        
        } 
    }
    
    for (i = 0; i < bikeGearings->getSize(); i++) {
        bikeGearingComboBox->insertItem(bikeGearings->getItem(i)->getName());

        if (bike->getBikeGearing() == bikeGearings->getItem(i)->getOid()) {
            bikeGearingComboBox->setCurrentItem(i);        
        } 
    }
    
    for (i = 0; i < wheelGearings->getSize(); i++) {
        wheelGearingComboBox->insertItem(wheelGearings->getItem(i)->getName());
 
        if (bike->getWheelGearing() == wheelGearings->getItem(i)->getOid()) {
            wheelGearingComboBox->setCurrentItem(i);        
        } 
    }   
              updateCheckPoints(trailComboBox->currentItem());
   updateStationaryWheel(trailComboBox->currentItem());
   checkTire(frontTireComboBox->currentItem());
}

void RideDataForm::setCalender( Calender *c )
{
    calender = c;
}

void RideDataForm::pushButtonOk()
{
    bool bFlag = true;
    QDate currentDate = QDate::currentDate();
    QDate chosenDate;
    QString s;
    Frame *frame = NULL;
    Trail *trail = NULL;
    Wheel *wheel = NULL;
    Tire *tire = NULL;
    Computer *computer = NULL;
    Gearing *bikeGearing = NULL;
    Gearing *wheelGearing = NULL;
    
    chosenDate = dateEdit->date();
    ride->setDate(chosenDate);
    ride->setStartTime(startTimeEdit->time().toString());
    ride->setAmountOfSleep(amountOfSleepTimeEdit->time().toString());
    ride->setTrainingTime(trainingTimeEdit->time().toString());
    ride->setElapsedTime(elapsedTimeEdit->time().toString());
    
    ride->setOdoBefore(odoBeforeLineEdit->text().toFloat());
    ride->setOdoAfter(odoAfterLineEdit->text().toFloat());
    ride->setAverageSpeed(avgSpeedLineEdit->text().toFloat());
    ride->setMaxSpeed( maxSpeedLineEdit->text().toFloat());
    ride->setTempData(tempCheckBox->isChecked());
    ride->setMaxTemp(maxTemperatureLineEdit->text().toFloat());
    ride->setMinTemp(minTemperatureLineEdit->text().toFloat());

    ride->setRating(ratingComboBox->currentText());
    ride->setType(trainingTypeComboBox->currentText());
    
    trails = new Trails();
       
    if ( (trails->getSize() == 0) || (frames->getSize()== 0 || bikeGearings->getSize() == 0) ) {
        QMessageBox::information( this, "Bike Master 2000",
                                     "If you wanna play, you gotta pay... \n",
                                     "Ok", 0, 0, 0, 1 );
    }
    else {  
    
    
    int i;
    for (i = 0; i < trails->getSize(); i++ ) {     
        trail = trails->getItem(i); 
        s = trail->getName();
        if (s.compare(trailComboBox->currentText()) == 0) {
            break;
        } 
    }
    ride->setTrail(trail->getOid());    
    
    
    // Bike tab...
    for (i = 0; i < frames->getSize(); i++ ) {
        frame = frames->getItem(i);
        s =  frame->getName();
        if (s.compare(frameComboBox->currentText()) == 0) {
            break;
        } 
    }
    bike->setFrame(frame->getOid());
      
    frontWheels = new Wheels("front");
    for (i = 0; i < frontWheels->getSize(); i++ ) {     
        wheel = frontWheels->getItem(i); 
        s = wheel->getName();
        if (s.compare(frontWheelComboBox->currentText()) == 0) {
            break;
        } 
    }
    bike->setFrontWheel(wheel->getOid());   
    
    backWheels = new Wheels("back");
    for (i = 0; i < backWheels->getSize(); i++ ) {     
        wheel = backWheels->getItem(i); 
        s = wheel->getName();
        if (s.compare(backWheelComboBox->currentText()) == 0) {
            break;
        } 
    }
    bike->setBackWheel(wheel->getOid());
    
    tires = new Tires();
    for (i = 0; i < tires->getSize(); i++ ) {     
        tire = tires->getItem(i); 
        s = tire->getName();
        if (s.compare(frontTireComboBox->currentText()) == 0) {
            break;
        } 
    }
    bike->setFrontTire(tire->getOid());
    
    for (i = 0; i < tires->getSize(); i++ ) {     
        tire = tires->getItem(i); 
        s = tire->getName();
        if (s.compare(backTireComboBox->currentText()) == 0) {
            break;
        } 
    }
    bike->setBackTire(tire->getOid());    
    
    computers = new Computers();
    for (i = 0; i < computers->getSize(); i++ ) {     
        computer = computers->getItem(i); 
        s = computer->getName();
        if (s.compare(computerComboBox->currentText()) == 0) {
            break;
        } 
    }
    bike->setComputer(computer->getOid());
    
    bikeGearings = new Gearings("bike");
    for (i = 0; i < bikeGearings->getSize(); i++ ) {     
        bikeGearing = bikeGearings->getItem(i); 
        s = bikeGearing->getName();
        if (s.compare(bikeGearingComboBox->currentText()) == 0) {
            break;
        } 
    }
    bike->setBikeGearing(bikeGearing->getOid());    
    
    wheelGearings = new Gearings("wheel");
    for (i = 0; i < wheelGearings->getSize(); i++ ) {     
        wheelGearing = wheelGearings->getItem(i); 
        s = wheelGearing->getName();
        if (s.compare(wheelGearingComboBox->currentText()) == 0) {
            break;
        } 
    }
    bike->setWheelGearing(wheelGearing->getOid());       
    
    
    if (chosenDate > currentDate) {
        switch(QMessageBox::warning( this, "Bike Master 2000",
                                     "You are about to register a ride for a date in the future.\n",
                                     "Ok",
                                     "Cancel", 0, 0, 1 ) ) {
        case 0: // The user clicked the Ok button
            bFlag = true;
            break;
        case 1: // The user clicked the Cancel button
            bFlag = false;
            break;
        }
    }
    
    if (frontWheelComboBox->isEnabled() == false) {
        bike->setFrontWheel(0);
        bike->setFrontWheel(0);
    }
    
    if (backWheelComboBox->isEnabled() == false) {
        bike->setBackWheel(0);
        bike->setBackTire(0);
    }
        
    QSqlQuery id = DbConn::Instance()->get("SELECT MAX(id) FROM Ride;");
    id.next();
    int maxRideId = id.value(0).toInt();
        
    if (bFlag) {
        if (ride->getOid() == maxRideId) {
            bike->save();
            ride->setBike(bike->getOid());
            ride->save();
        } else {
            bike->upd();
            ride->setBike(bike->getOid());
            ride->upd();
        }
    } 
}
    emit updateCalender();
    this->close();
}

void RideDataForm::setTempDataAvailable()
{
    if (!tempCheckBox->isChecked()) {
        maxTemperatureLineEdit->setEnabled(false);
        minTemperatureLineEdit->setEnabled(false);    
    } else {
        maxTemperatureLineEdit->setEnabled(true);
        minTemperatureLineEdit->setEnabled(true);   
    }
}

void RideDataForm::pushButtonHelp()
{

    system("/usr/bin/firefox http://www.skip.informatik.gu.se/~fjadd");
}


void RideDataForm::updateStationaryWheel( int n )
{
    Trail *trail;
    
    trails = new Trails();
    
    if (0 == trails->getSize()) {
        return; 
    } 
    trail = trails->getItem(0);           
    frontWheelComboBox->setEnabled(true);
    backWheelComboBox->setEnabled(true);
    frontTireComboBox->setEnabled(true);
    backTireComboBox->setEnabled(true);
        
    if (trail->getStationary() == true) {
        if (trail->getUseFrontWheel() == false) {
            frontWheelComboBox->setEnabled(false);
            frontTireComboBox->setEnabled(false);
        }
        if (trail->getUseBackWheel() == false) {
            backWheelComboBox->setEnabled(false);
            backTireComboBox->setEnabled(false);
        }
    }
}        


void RideDataForm::selectedCheckpoint( int n )
{
    RideCheckPoint *rideCheckPoint;
            
    if (!(ride->getOid() == 0)) {

        rideCheckPoints = new RideCheckPoints (ride->getOid());    
        rideCheckPoint = rideCheckPoints->getItem(n);
        
         checkPoints = new CheckPoints(rideCheckPoint->getCheckPoint(), true);
        rideCheckPointNameLineEdit->setText(checkPoints->getItem(0)->getLocation());
        rideCheckPointTimeEdit->setTime(rideCheckPoint->getCheckTime());
    } else {
         Trail *trail;
         trails = new Trails();
         trail = trails->getItem(n);
         
         rideCheckPoints = new RideCheckPoints (trail->getOid());    
         rideCheckPoint = rideCheckPoints->getItem(n);
        
         checkPoints = new CheckPoints(rideCheckPoint->getCheckPoint(), true);
         rideCheckPointNameLineEdit->setText(checkPoints->getItem(0)->getLocation());
         rideCheckPointTimeEdit->setTime(rideCheckPoint->getCheckTime());
    }
}


void RideDataForm::saveCheckPoint()
{
    QTime time;
    RideCheckPoint *rideCheckPoint;
    rideCheckPoints = new RideCheckPoints (ride->getOid());
    rideCheckPoint = rideCheckPoints->getItem(rideCheckPointListBox->currentItem());
    
    time = rideCheckPointTimeEdit->time();
    if (time != QTime(0,0,0)) {
        if (rideCheckPoint->getCheckTime() == QTime(0,0,0)) {
            rideCheckPoint->setCheckTime(time);
            rideCheckPoint->save();
        } else {
            rideCheckPoint->setCheckTime(time);
            rideCheckPoint->upd();
        } 
    }
}


void RideDataForm::checkTire( int n )
{
    int nf, nb;
    nf = frontTireComboBox->currentItem();
    nb = backTireComboBox->currentItem();
    
    if (nf == nb) {
        frontTireComboBox->setCurrentItem(0);
        if (n > 0) {
            backTireComboBox->setCurrentItem(1);
        }
    }
} 


void RideDataForm::updateCheckPoints(int n)
{
   Trail *trail;
   
   trails = new Trails();
   
   if (trails->getSize() != 0) {
   
       trail = trails->getItem(n);
   } 
   else {
       trail = new Trail();
   }
//   if (ride->getOid() == 0) {
//      rideCheckPointSavePushButton->setEnabled(false);
// }
   
   rideCheckPoints = new RideCheckPoints(trail->getOid());
   rideCheckPointListBox->clear();    
    
   int i;
   for (i = 0; i < rideCheckPoints->getSize(); i++) {
       checkPoints = new CheckPoints(rideCheckPoints->getItem(i)->getCheckPoint(), true);
       rideCheckPointListBox->insertItem(checkPoints->getItem(0)->getLocation());
   }
   
   rideCheckPointNameLineEdit->setReadOnly(true);
    
   if (rideCheckPointListBox->count() == 0) {
       rideCheckPointSavePushButton->setEnabled(false);
       rideCheckPointTimeEdit->setEnabled(false);     
   }
}


void RideDataForm::killButtonSlot()
{
    ride->remove();
    emit updateCalender(); 
    this->close();
}
