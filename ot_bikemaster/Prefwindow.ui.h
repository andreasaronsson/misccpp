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

void prefWindow::init()
{
    this->setWFlags(Qt::WDestructiveClose);    
    initFrames();
    initFrontWheels();
    initBackWheels();    
    initTires();
    initBikeGearings();
    initWheelGearings();
    initComputers();
    initTrails();
    setup();
    changeUnits();
}

void prefWindow::newBackWheel()
{
    Wheel *wheel = new Wheel();
    wheel->setType("back");
    backWheelNameTextLineEdit->setText("");
    backWheelBrandTextLineEdit->setText("");
    backWheelModelTextLineEdit->setText("");
    backWheelCircumferenceTextLineEdit->setText("");
    backWheelDescriptionTextEdit->setText("");  
    delete(wheel);  
}

void prefWindow::initBackWheels()
{
    Wheels *wheels = new Wheels("back");    
    int antal = wheels->getSize();
    backWheelListBox->clear();
    for (int i = 0; i < antal; i++) {
        backWheelListBox->insertItem(wheels->getItem(i)->getName(), -1);
    } 
    delete(wheels);    
}

void prefWindow::initFrontWheels()
{
    Wheels *wheels = new Wheels("front");    
    int antal = wheels->getSize();
    frontWheelListBox->clear();
    for (int i = 0; i < antal; i++) {
        frontWheelListBox->insertItem(wheels->getItem(i)->getName(), -1);
    } 
    delete(wheels);  
}

void prefWindow::wheelGearingListBoxClicked()
{
    wheelGearingEnable(TRUE);    
    Gearings *gearings = new Gearings("wheel");
    Gearing *gearing = gearings->getItem(wheelGearingListBox->currentItem());
    wheelGearingNameTextLineEdit->setText(gearing->getName());
    int antal = gearing->getNoOfCogWheels();
    wheelGearingChainWheelListBox->clear();
    QString qs = QString(gearing->getNoOfTeeth());    
    QString qs2;
    int lc = 1;
    int nc;    
    wheelGearingChainWheelNewPushButton->setEnabled(TRUE);
    if (antal>0) {
        wheelGearingChainWheelDeletePushButton->setEnabled(TRUE);
        for (int i = 0; i < antal; i++) {
            nc = qs.find(',', lc, FALSE);
            if (nc == -1)nc = qs.find('}', lc, FALSE);
            
            if (qs.mid(lc, nc-lc).toInt()<10) {
                qs2 = " "+qs.mid(lc, nc-lc);
            }
            else {
                qs2 = qs.mid(lc, nc-lc);
            }
            wheelGearingChainWheelListBox->insertItem(qs2, -1);
            lc = nc+1;
        }
    }
    wheelGearingChainWheelListBox->setSelected(0, TRUE);
    wheelGearingChainWheelListBoxClicked();
    delete(gearings);

}

void prefWindow::setupSavePushButtonClicked()
{
    Preferences *preferences = Preferences::Instance();
preferences->setDistanceKm(setupDistanceKmRadioButton->isChecked());
preferences->setDistanceMiles(setupDistanceMileRadioButton->isChecked());
preferences->setHeightMeters(setupHeightMetersRadioButton->isChecked());
preferences->setHeightFeet(setupHeightFeetRadioButton->isChecked());
preferences->setSpeedKmh(setupSpeedKmhRadioButton->isChecked());
preferences->setSpeedMph(setupSpeedMphRadioButton->isChecked());
preferences->setTemperatureDegreesC(setupTemperatureDegreesCRadioButton->isChecked());
preferences->setTemperatureDegreesF(setupTemperatureDegreesFRadioButton->isChecked());
preferences->setWeightKilo(setupWeightKiloRadioButton->isChecked());
preferences->setWeightPound(setupWeightPoundRadioButton->isChecked());
preferences->setWidthCm(setupWidthCmRadioButton->isChecked());
preferences->setWidthInch(setupWidthInchRadioButton->isChecked());
preferences->setPresentationBikeUsed(setupPresentationBikeUsedRadioButton->isChecked());
preferences->setPresentationDistance(setupPresentationDistanceRadioButton->isChecked());
preferences->setPresentationTime(setupPresentationTimeRadioButton->isChecked());
preferences->setPresentationTrail(setupPresentationTrailRadioButton->isChecked());
preferences->setDateOrderMdy(setupDateOrderMdyRadioButton->isChecked());  preferences->setDateOrderDmy(setupDateOrderDmyRadioButton->isChecked());
preferences->setDateOrderYmd(setupDateOrderYmdRadioButton->isChecked());
preferences->setMonthFormatFull(setupMonthFormatFullRadioButton->isChecked());
preferences->setMonthFormatShort(setupMonthFormatShortRadioButton->isChecked());
preferences->setMonthFormatNumber(setupMonthFormatNumberRadioButton->isChecked());
preferences->setWeekStartsMonday(setupWeekStartsMondayRadioButton->isChecked());
preferences->setWeekStartsSunday(setupWeekStartsSundayRadioButton->isChecked());
preferences->setDayLeadingZeroes1(setupDayLeadingZeroes1RadioButton->isChecked());
preferences->setDayLeadingZeroes01(setupDayLeadingZeroes01RadioButton->isChecked());
preferences->setCentury90(setupCentury90RadioButton->isChecked());
preferences->setCentury2000(setupCentury2000RadioButton->isChecked());
preferences->save();
changeUnits();

}

void prefWindow::frontWheelListBoxClicked()
{
    frontWheelEnable(TRUE);    
    Wheels *wheels = new Wheels("front");
    Wheel *wheel = wheels->getItem(frontWheelListBox->currentItem());
    frontWheelNameTextLineEdit->setText(wheel->getName());
    frontWheelBrandTextLineEdit->setText(wheel->getBrand());
    frontWheelModelTextLineEdit->setText(wheel->getModel());
    frontWheelCircumferenceTextLineEdit->setText(QString::number(wheel->getCircumference()));
    frontWheelDescriptionTextEdit->setText(wheel->getDescription());
    delete (wheels);
}



void prefWindow::tireListBoxClicked()
{
    tireEnable(TRUE);    
    Tires *tires = new Tires();
    Tire *tire = tires->getItem(tireListBox->currentItem());
    tireNameTextLineEdit->setText(tire->getName());
    tireBrandTextLineEdit->setText(tire->getBrand());
    tireModelTextLineEdit->setText(tire->getModel());
    delete (tires);  
}



void prefWindow::initTires()
{
    Tires *tires = new Tires();    
    int antal = tires->getSize();
    tireListBox->clear();
    for (int i = 0; i < antal; i++) {
        tireListBox->insertItem(tires->getItem(i)->getName(), -1);
    }
    delete(tires);
}


void prefWindow::initBikeGearings()
{
    Gearings *gearings = new Gearings("bike");    
    int antal = gearings->getSize();
    bikeGearingListBox->clear();
    bikeGearingChainWheelListBox->clear();
    for (int i = 0; i < antal; i++) {
        bikeGearingListBox->insertItem(gearings->getItem(i)->getName(), -1);
    }
  delete(gearings);  
}

void prefWindow::bikeGearingListBoxClicked()
{
    bikeGearingEnable(TRUE);    
    Gearings *gearings = new Gearings("bike");
    Gearing *gearing = gearings->getItem(bikeGearingListBox->currentItem());
    bikeGearingNameTextLineEdit->setText(gearing->getName());
    int antal = gearing->getNoOfCogWheels();
    bikeGearingChainWheelListBox->clear();
    QString qs = QString(gearing->getNoOfTeeth());    
    QString qs2;
    int lc = 1;
    int nc;    
    bikeGearingChainWheelNewPushButton->setEnabled(TRUE);
    if (antal>0) {
        bikeGearingChainWheelDeletePushButton->setEnabled(TRUE);
        for (int i = 0; i < antal; i++) {
            nc = qs.find(',', lc, FALSE);
            if (nc == -1)nc = qs.find('}', lc, FALSE);
            
            if (qs.mid(lc, nc-lc).toInt()<10) {
                qs2 = " "+qs.mid(lc, nc-lc);
            }
            else {
                qs2 = qs.mid(lc, nc-lc);
            }
            bikeGearingChainWheelListBox->insertItem(qs2, -1);
            lc = nc+1;
        }
    }
    bikeGearingChainWheelListBox->setSelected(0, TRUE);
    bikeGearingChainWheelListBoxClicked();
    delete(gearings);
}


void prefWindow::bikeGearingChainWheelListBoxClicked()
{
    bikeGearingNumberOfTeethSpinBox->setValue(bikeGearingChainWheelListBox->currentText().toInt());    
    bikeGearingChainWheelDeletePushButton->setEnabled(TRUE);
    bikeGearingNumberOfTeethSpinBox->setEnabled(TRUE);
}


void prefWindow::bikeGearingNoOfTeethSpinBoxValueChanged()
{
    if(bikeGearingChainWheelListBox->currentText().toInt() == bikeGearingNumberOfTeethSpinBox->value()) return;
      QString qs;
    if (bikeGearingNumberOfTeethSpinBox->value()<10) {
        qs = " "+QString::number(bikeGearingNumberOfTeethSpinBox->value());
    }
    else {
        qs = QString::number(bikeGearingNumberOfTeethSpinBox->value());
    }
    if (bikeGearingChainWheelListBox->currentItem() != -1) {
        bikeGearingChainWheelListBox->changeItem(qs, bikeGearingChainWheelListBox->currentItem());
    }
    else {
        bikeGearingChainWheelListBox->insertItem(qs, -1);
        bikeGearingChainWheelListBox->setSelected(bikeGearingChainWheelListBox->numRows()-1, TRUE);
    }
    bikeGearingChainWheelListBox->sort();

}


void prefWindow::bikeGearingChainWheelNewPushButtonClicked()
{
    //bikeGearingChainWheelListBox->insertItem(" 0", 0);
    //bikeGearingChainWheelListBox->setSelected(1, TRUE);
    bikeGearingNumberOfTeethSpinBox->setFocus();
    bikeGearingChainWheelListBox->clearSelection();
    if (bikeGearingChainWheelListBox->text(0) != " 0") {
        bikeGearingChainWheelListBox->insertItem(" 0", 0);
        bikeGearingChainWheelListBox->setSelected(0, TRUE);
        bikeGearingNumberOfTeethSpinBox->setEnabled(TRUE);
    }
    bikeGearingChainWheelNewPushButton->setEnabled(TRUE);
    
}


void prefWindow::bikeGearingChainWheelDeletePushButtonClicked()
{
    bikeGearingChainWheelListBox->removeItem(bikeGearingChainWheelListBox->currentItem());
    bikeGearingChainWheelListBox->setSelected(0, TRUE);
    if (bikeGearingChainWheelListBox->numRows()<1) {
        bikeGearingNumberOfTeethSpinBox->setEnabled(FALSE);
        bikeGearingChainWheelDeletePushButton->setEnabled(FALSE);
    }
}


void prefWindow::bikeGearingSavePushButtonClicked()
{
    if (bikeGearingNameTextLineEdit->text() == "") return;    
    Gearings *gearings = new Gearings("bike");
    Gearing *gearing;
    QString chainWheels = "";
    int noOfCogWheels = bikeGearingChainWheelListBox->numRows();
    for (int i = 0; i<noOfCogWheels; i++) {
        chainWheels.append(bikeGearingChainWheelListBox->text(i).stripWhiteSpace());
        chainWheels.append(",");
    }
    if (noOfCogWheels == 0) {
        noOfCogWheels =1;
        chainWheels = "0,";
    }
    chainWheels = chainWheels.left(chainWheels.length()-1);


    if (bikeGearingListBox->currentItem()!=-1 && bikeGearingListBox->isSelected(bikeGearingListBox->currentItem())) {
        gearing = gearings->getItem(bikeGearingListBox->currentItem());        
    }
    else {

        gearing = new Gearing();
        gearing->setType("bike");
    }
    gearing->setName(bikeGearingNameTextLineEdit->text());
    gearing->setNoOfCogWheels(noOfCogWheels);
    gearing->setNoOfTeeth(chainWheels);
    if (bikeGearingListBox->currentItem() != -1 && bikeGearingListBox->isSelected(bikeGearingListBox->currentItem())) {
            gearing->upd();
   }
    else {
        gearing->save();
        delete(gearing);
    }
    initBikeGearings();
    bikeGearingEnable(FALSE);    
    //bikeGearings();
    //delete(gearings);  
}


void prefWindow::bikeGearingNewPushButtonClicked()
{
bikeGearingListBox->clearSelection();
bikeGearingNameTextLineEdit->setText("");
bikeGearingNameTextLineEdit->setEnabled(TRUE);
bikeGearingChainWheelListBox->clear();
bikeGearingNumberOfTeethSpinBox->setEnabled(FALSE);
bikeGearingNumberOfTeethSpinBox->setValue(0);
bikeGearingChainWheelDeletePushButton->setEnabled(TRUE);
bikeGearingChainWheelNewPushButton->setEnabled(TRUE);
bikeGearingSavePushButton->setEnabled(TRUE);
 
}


void prefWindow::setupDistanceKmRadioButtonClicked()
{
    if(setupDistanceKmRadioButton->isChecked()) {
        setupDistanceMileRadioButton->setChecked(FALSE);
    }
    else {
      setupDistanceMileRadioButton->setChecked(TRUE);  
  }
}



void prefWindow::setup()
{
    Preferences *preferences = Preferences::Instance();    
    if (preferences->getDistanceKm()) setupDistanceKmRadioButton->setChecked(TRUE);
    if (preferences->getDistanceMiles()) setupDistanceMileRadioButton->setChecked(TRUE);
    if (preferences->getHeightMeters()) setupHeightMetersRadioButton->setChecked(TRUE);
    if (preferences->getHeightFeet()) setupHeightFeetRadioButton->setChecked(TRUE);
    if (preferences->getSpeedKmh()) setupSpeedKmhRadioButton->setChecked(TRUE);
    if (preferences->getSpeedMph()) setupSpeedMphRadioButton->setChecked(TRUE);
    if (preferences->getTemperatureDegreesC()) setupTemperatureDegreesCRadioButton->setChecked(TRUE);
    if (preferences->getTemperatureDegreesF()) setupTemperatureDegreesFRadioButton->setChecked(TRUE);
    if (preferences->getWeightKilo()) setupWeightKiloRadioButton->setChecked(TRUE);
    if (preferences->getWeightPound()) setupWeightPoundRadioButton->setChecked(TRUE);
    if (preferences->getWidthCm()) setupWidthCmRadioButton->setChecked(TRUE);
    if (preferences->getWidthInch()) setupWidthInchRadioButton->setChecked(TRUE);
    if (preferences->getPresentationBikeUsed()) setupPresentationBikeUsedRadioButton->setChecked(TRUE);    
    if (preferences->getPresentationDistance()) setupPresentationDistanceRadioButton->setChecked(TRUE);        
    if (preferences->getPresentationTime()) setupPresentationTimeRadioButton->setChecked(TRUE);    
    if (preferences->getPresentationTrail()) setupPresentationTrailRadioButton->setChecked(TRUE);    
    if (preferences->getDateOrderMdy()) setupDateOrderMdyRadioButton->setChecked(TRUE);
    if (preferences->getDateOrderDmy()) setupDateOrderDmyRadioButton->setChecked(TRUE);
    if (preferences->getDateOrderYmd()) setupDateOrderYmdRadioButton->setChecked(TRUE);
    if (preferences->getMonthFormatFull()) setupMonthFormatFullRadioButton->setChecked(TRUE);
    if (preferences->getMonthFormatShort()) setupMonthFormatShortRadioButton->setChecked(TRUE);
    if (preferences->getMonthFormatNumber()) setupMonthFormatNumberRadioButton->setChecked(TRUE);    
    if (preferences->getWeekStartsMonday()) setupWeekStartsMondayRadioButton->setChecked(TRUE);
    if (preferences->getWeekStartsSunday()) setupWeekStartsSundayRadioButton->setChecked(TRUE);
    if (preferences->getWeekStartsMonday()) setupWeekStartsMondayRadioButton->setChecked(TRUE);
    if (preferences->getDayLeadingZeroes1()) setupDayLeadingZeroes1RadioButton->setChecked(TRUE);
    if (preferences->getDayLeadingZeroes01()) setupDayLeadingZeroes01RadioButton->setChecked(TRUE);
    if (preferences->getCentury90()) setupCentury90RadioButton->setChecked(TRUE);
    if (preferences->getCentury2000()) setupCentury2000RadioButton->setChecked(TRUE);
    setupCentury2000RadioButton->setChecked(TRUE);
    
}


void prefWindow::setupDistanceMileRadioButtonClicked()
{
    if(setupDistanceMileRadioButton->isChecked()) {
        setupDistanceKmRadioButton->setChecked(FALSE);
    }
    else {
        setupDistanceKmRadioButton->setChecked(TRUE);  
  }
}


void prefWindow::setupHeightMetersRadioButtonClicked()
{
    if(setupHeightMetersRadioButton->isChecked()) {
        setupHeightFeetRadioButton->setChecked(FALSE);
    }
    else {
        setupHeightFeetRadioButton->setChecked(TRUE);  
  }
}


void prefWindow::setupHeightFeetRadioButtonClicked()
{
    if(setupHeightFeetRadioButton->isChecked()) {
        setupHeightMetersRadioButton->setChecked(FALSE);
    }
    else {
        setupHeightMetersRadioButton->setChecked(TRUE);  
  }

}


void prefWindow::setupSpeedKmhRadioButtonClicked()
{
    if(setupSpeedKmhRadioButton->isChecked()) {
        setupSpeedMphRadioButton->setChecked(FALSE);
    }
    else {
        setupSpeedMphRadioButton->setChecked(TRUE);  
  }
}


void prefWindow::setupSpeedMphRadioButtonClicked()
{
    if(setupSpeedMphRadioButton->isChecked()) {
        setupSpeedKmhRadioButton->setChecked(FALSE);
    }
    else {
        setupSpeedKmhRadioButton->setChecked(TRUE);  
  }
}

void prefWindow::setupTemperatureDegreesCRadioButtonClicked()
{
    if(setupTemperatureDegreesCRadioButton->isChecked()) {
        setupTemperatureDegreesFRadioButton->setChecked(FALSE);
    }
    else {
        setupTemperatureDegreesFRadioButton->setChecked(TRUE);  
  }
}


void prefWindow::setupTemperatureDegreesFRadioButtonClicked()
{
    if(setupTemperatureDegreesFRadioButton->isChecked()) {
        setupTemperatureDegreesCRadioButton->setChecked(FALSE);
    }
    else {
        setupTemperatureDegreesCRadioButton->setChecked(TRUE);  
  }

}


void prefWindow::setupWeightKiloRadioButtonClicked()
{
    if(setupWeightKiloRadioButton->isChecked()) {
        setupWeightPoundRadioButton->setChecked(FALSE);
    }
    else {
        setupWeightPoundRadioButton->setChecked(TRUE);  
  }
}


void prefWindow::setupWeightPoundRadioButtonClicked()
{
    if(setupWeightPoundRadioButton->isChecked()) {
        setupWeightKiloRadioButton->setChecked(FALSE);
    }
    else {
        setupWeightKiloRadioButton->setChecked(TRUE);  
  }
}


void prefWindow::setupDateOrderMdyRadioButtonClicked()
{
    if(setupDateOrderMdyRadioButton->isChecked()) {
        setupDateOrderDmyRadioButton->setChecked(FALSE);
        setupDateOrderYmdRadioButton->setChecked(FALSE);
    }
    else {
        setupDateOrderDmyRadioButton->setChecked(TRUE);  
  }
}


void prefWindow::setupDateOrderDmyRadioButtonClicked()
{
    if(setupDateOrderDmyRadioButton->isChecked()) {
        setupDateOrderMdyRadioButton->setChecked(FALSE);
        setupDateOrderYmdRadioButton->setChecked(FALSE);
    }
    else {
        setupDateOrderYmdRadioButton->setChecked(TRUE);  
  }
}


void prefWindow::setupDateOrderYmdRadioButtonClicked()
{
    if(setupDateOrderYmdRadioButton->isChecked()) {
        setupDateOrderDmyRadioButton->setChecked(FALSE);
        setupDateOrderMdyRadioButton->setChecked(FALSE);
    }
    else {
        setupDateOrderDmyRadioButton->setChecked(TRUE);  
  }
}


void prefWindow::setupMonthFormatFullRadioButtonClicked()
{
    if(setupMonthFormatFullRadioButton->isChecked()) {
        setupMonthFormatShortRadioButton->setChecked(FALSE);
        setupMonthFormatNumberRadioButton->setChecked(FALSE);
    }
    else {
        setupMonthFormatShortRadioButton->setChecked(TRUE);  
  }
}


void prefWindow::setupMonthFormatShortRadioButtonClicked()
{
    if(setupMonthFormatShortRadioButton->isChecked()) {
        setupMonthFormatFullRadioButton->setChecked(FALSE);
        setupMonthFormatNumberRadioButton->setChecked(FALSE);
    }
    else {
        setupMonthFormatNumberRadioButton->setChecked(TRUE);  
  }
}

void prefWindow::setupMonthFormatNumberRadioButtonClicked()
{
    if(setupMonthFormatNumberRadioButton->isChecked()) {
        setupMonthFormatShortRadioButton->setChecked(FALSE);
        setupMonthFormatFullRadioButton->setChecked(FALSE);
    }
    else {
        setupMonthFormatShortRadioButton->setChecked(TRUE);  
  }
}

void prefWindow::setupWeekStartsMondayRadioButtonClicked()
{
    if(setupWeekStartsMondayRadioButton->isChecked()) {
        setupWeekStartsSundayRadioButton->setChecked(FALSE);
    }
    else {
        setupWeekStartsSundayRadioButton->setChecked(TRUE);  
  }
}

void prefWindow::setupWeekStartsSundayRadioButtonClicked()
{
    if(setupWeekStartsSundayRadioButton->isChecked()) {
        setupWeekStartsMondayRadioButton->setChecked(FALSE);
    }
    else {
        setupWeekStartsMondayRadioButton->setChecked(TRUE);  
  }
}

void prefWindow::setupDayLeadingZeroes1RadioButtonClicked()
{
    if(setupDayLeadingZeroes1RadioButton->isChecked()) {
        setupDayLeadingZeroes01RadioButton->setChecked(FALSE);
    }
    else {
        setupDayLeadingZeroes01RadioButton->setChecked(TRUE);  
  }
}

void prefWindow::setupDayLeadingZeroes01RadioButtonClicked()
{
    if(setupDayLeadingZeroes01RadioButton->isChecked()) {
        setupDayLeadingZeroes1RadioButton->setChecked(FALSE);
    }
    else {
        setupDayLeadingZeroes1RadioButton->setChecked(TRUE);  
  }
}

void prefWindow::setupCentury90RadioButtonClicked()
{
    if(setupCentury90RadioButton->isChecked()) {
        setupCentury2000RadioButton->setChecked(FALSE);
    }
    else {
        setupCentury2000RadioButton->setChecked(TRUE);  
  }
}

void prefWindow::setupCentury2000RadioButtonClicked()
{
    if(setupCentury2000RadioButton->isChecked()) {
        setupCentury90RadioButton->setChecked(FALSE);
    }
    else {
        setupCentury90RadioButton->setChecked(TRUE);  
  }
}

void prefWindow::wheelGearingChainWheelListBoxClicked() {
    wheelGearingNumberOfTeethSpinBox->setValue(wheelGearingChainWheelListBox->currentText().toInt());    
    wheelGearingChainWheelDeletePushButton->setEnabled(TRUE);
    wheelGearingNumberOfTeethSpinBox->setEnabled(TRUE);
}

void prefWindow::wheelGearingChainWheelDeletePushButtonClicked()
{
    wheelGearingChainWheelListBox->removeItem(wheelGearingChainWheelListBox->currentItem());
    wheelGearingChainWheelListBox->setSelected(0, TRUE);
    if (wheelGearingChainWheelListBox->numRows()<1) {
        wheelGearingNumberOfTeethSpinBox->setEnabled(FALSE);
        wheelGearingChainWheelDeletePushButton->setEnabled(FALSE);
    }
}

void prefWindow::setupPresentationBikeUsedRadioButtonClicked()
{
    if(setupPresentationBikeUsedRadioButton->isChecked()) {
        setupPresentationDistanceRadioButton->setChecked(FALSE);
        setupPresentationTimeRadioButton->setChecked(FALSE);
        setupPresentationTrailRadioButton->setChecked(FALSE);
    }
    else {
        setupPresentationDistanceRadioButton->setChecked(TRUE);
  }
}

void prefWindow::setupPresentationDistanceRadioButtonClicked()
{
    if(setupPresentationDistanceRadioButton->isChecked()) {
        setupPresentationBikeUsedRadioButton->setChecked(FALSE);
        setupPresentationTimeRadioButton->setChecked(FALSE);
        setupPresentationTrailRadioButton->setChecked(FALSE);
    }
    else {
        setupPresentationTimeRadioButton->setChecked(TRUE);
  }
}

void prefWindow::setupPresentationTimeRadioButtonClicked()
{
    if(setupPresentationTimeRadioButton->isChecked()) {
        setupPresentationDistanceRadioButton->setChecked(FALSE);
        setupPresentationBikeUsedRadioButton->setChecked(FALSE);
        setupPresentationTrailRadioButton->setChecked(FALSE);
    }
    else {
        setupPresentationTrailRadioButton->setChecked(TRUE);
  }
}

void prefWindow::setupPresentationTrailRadioButtonClicked()
{
    if(setupPresentationTrailRadioButton->isChecked()) {
        setupPresentationDistanceRadioButton->setChecked(FALSE);
        setupPresentationTimeRadioButton->setChecked(FALSE);
        setupPresentationBikeUsedRadioButton->setChecked(FALSE);
    }
    else {
        setupPresentationTimeRadioButton->setChecked(TRUE);
  }
}

void prefWindow::wheelGearingNewPushButtonClicked()
{
    wheelGearingListBox->clearSelection();
    wheelGearingNameTextLineEdit->setText("");
    wheelGearingNameTextLineEdit->setEnabled(TRUE);
    wheelGearingChainWheelListBox->clear();
    wheelGearingNumberOfTeethSpinBox->setEnabled(FALSE);
    wheelGearingNumberOfTeethSpinBox->setValue(0);
    wheelGearingChainWheelDeletePushButton->setEnabled(FALSE);
    wheelGearingChainWheelNewPushButton->setEnabled(TRUE);
    wheelGearingSavePushButton->setEnabled(TRUE);
}


void prefWindow::wheelGearingSavePushButtonClicked()
{
    if (wheelGearingNameTextLineEdit->text() == "") return;    
    Gearings *gearings = new Gearings("wheel");
    Gearing *gearing;
    QString chainWheels = "";
    int noOfCogWheels = wheelGearingChainWheelListBox->numRows();
    for (int i = 0; i<noOfCogWheels; i++) {
        chainWheels.append(wheelGearingChainWheelListBox->text(i).stripWhiteSpace());
        chainWheels.append(",");
    }
    if (noOfCogWheels == 0) {
        noOfCogWheels =1;
        chainWheels = "0,";
    }
    chainWheels = chainWheels.left(chainWheels.length()-1);


    if (wheelGearingListBox->currentItem()!=-1 && wheelGearingListBox->isSelected(wheelGearingListBox->currentItem())) {
        gearing = gearings->getItem(wheelGearingListBox->currentItem());        
    }
    else {

        gearing = new Gearing();
        gearing->setType("wheel");
    }
    gearing->setName(wheelGearingNameTextLineEdit->text());
    gearing->setNoOfCogWheels(noOfCogWheels);
    gearing->setNoOfTeeth(chainWheels);
    if (wheelGearingListBox->currentItem() != -1 && wheelGearingListBox->isSelected(wheelGearingListBox->currentItem())) {
            gearing->upd();
   }
    else {
        gearing->save();
        delete(gearing);
    }
    initWheelGearings();
    wheelGearingEnable(FALSE);    
    //wheelGearings();
    //delete(gearings);  

}
 

void prefWindow::wheelGearingChainWheelNewPushButtonClicked()
{
    //bikeGearingChainWheelListBox->insertItem(" 0", 0);
    //bikeGearingChainWheelListBox->setSelected(1, TRUE);
    wheelGearingNumberOfTeethSpinBox->setFocus();
    wheelGearingChainWheelListBox->clearSelection();
    if (wheelGearingChainWheelListBox->text(0) != " 0") {
        wheelGearingChainWheelListBox->insertItem(" 0", 0);
        wheelGearingChainWheelListBox->setSelected(0, TRUE);
        wheelGearingNumberOfTeethSpinBox->setEnabled(TRUE);
    }
    wheelGearingChainWheelNewPushButton->setEnabled(TRUE);
}


void prefWindow::initWheelGearings()
{
    Gearings *gearings = new Gearings("wheel");    
    int antal = gearings->getSize();
    wheelGearingListBox->clear();
    wheelGearingChainWheelListBox->clear();
    for (int i = 0; i < antal; i++) {
        wheelGearingListBox->insertItem(gearings->getItem(i)->getName(), -1);
    }
    delete(gearings);
}

void prefWindow::initComputers()
{
    Computers *computers = new Computers();
    int antal = computers->getSize();
    computerListBox->clear();
    wheelGearingChainWheelListBox->clear();
    for (int i = 0; i < antal; i++) {
        computerListBox->insertItem(computers->getItem(i)->getName(), -1);
    }
    delete(computers);
}

void prefWindow::initTrails()
{
    Trails *trails = new Trails();
    int antal = trails->getSize();
    trailsListBox->clear();
    for (int i = 0; i < antal; i++) {
        trailsListBox->insertItem(trails->getItem(i)->getName(), -1);
    }
    delete(trails);
    trailsStationaryClicked();
}

void prefWindow::trailsListBoxClicked()
{
    trailsEnable(TRUE);
    checkPointsEnable(FALSE);
    Trails *trails = new Trails();
    Trail *trail = trails->getItem(trailsListBox->currentItem());
    SkillLevels *skillLevels = new SkillLevels();
    int i;
    RoadConditions *roadConditions = new RoadConditions();
    trailsNameTextLineEdit->setText(trail->getName());
    trailsStationaryCheckBox->setChecked(trail->getStationary());
    if (trail->getStationary()) {
        trailsUseFrontWheelCheckBox->setEnabled(TRUE);
        trailsUseBackWheelCheckBox->setEnabled(TRUE);
    }
    trailsUseFrontWheelCheckBox->setChecked(trail->getUseFrontWheel());
    trailsUseBackWheelCheckBox->setChecked(trail->getUseBackWheel());
    trailsMapReferenceTextLineEdit->setText(trail->getMapReference());
    trailsDistanceTextLineEdit->setText(QString::number(trail->getDistance()));
    trailsMaxAltitudeTextLineEdit->setText(QString::number(trail->getMaxAltitude()));
    trailsMinAltitudeTextLineEdit->setText(QString::number(trail->getMinAltitude()));
    trailsAccumAltitudeTextLineEdit->setText(QString::number(trail->getAccumAltitude()));
    trailsDescriptionTextEdit->setText(trail->getDescription());
    trailsSkillLevelComboBox->clear();
    for (i = 0; i < skillLevels->getSize(); i++) {
        trailsSkillLevelComboBox->insertItem(QString(skillLevels->getItem(i)), -1);
        if (skillLevels->getItem(i) == trail->getSkillLevel()) trailsSkillLevelComboBox->setCurrentItem(i);
    }
    
    trailsRoadConditionComboBox->clear();    
    for (i = 0; i < roadConditions->getSize(); i++) {
        trailsRoadConditionComboBox->insertItem(roadConditions->getItem(i), -1);
        if (roadConditions->getItem(i) == trail->getRoadCondition()) trailsRoadConditionComboBox->setCurrentItem(i);
    }
    trailsSavePushButton->setEnabled(TRUE);
    
    initCheckPoints();
                
    delete(trails);
    //delete(skillLevels);
}

void prefWindow::trailsSavePushButtonClicked()
{
    if (trailsNameTextLineEdit->text() == "") return;    
    Trails *trails = new Trails();
    Trail *trail;   
    if (trailsListBox->currentItem() != -1 && trailsListBox->isSelected(trailsListBox->currentItem())) {
        trail = trails->getItem(trailsListBox->currentItem());
    }
    else {
        trail = new Trail();
    }
    trail->setName(trailsNameTextLineEdit->text());
    trail->setStationary(trailsStationaryCheckBox->isChecked());
    trail->setSkillLevel(trailsSkillLevelComboBox->currentText());
    trail->setMapReference(trailsMapReferenceTextLineEdit->text());
    trail->setDistance(trailsDistanceTextLineEdit->text().toFloat());
    trail->setRoadCondition(trailsRoadConditionComboBox->currentText());
    trail->setUseFrontWheel(trailsUseFrontWheelCheckBox->isChecked());
    trail->setUseBackWheel(trailsUseBackWheelCheckBox->isChecked());
    trail->setMaxAltitude(trailsMaxAltitudeTextLineEdit->text().toFloat());
    trail->setMinAltitude(trailsMinAltitudeTextLineEdit->text().toFloat());
    trail->setAccumAltitude(trailsAccumAltitudeTextLineEdit->text().toFloat());
    trail->setDescription(trailsDescriptionTextEdit->text());
    if (trailsListBox->currentItem()!=-1 && trailsListBox->isSelected(trailsListBox->currentItem())) {
        trail->upd();
    }
    else {
        trail->save();
        delete(trail);
    }
    initTrails();
    trailsEnable(FALSE);
    delete(trails);

}

void prefWindow::computerListBoxClicked()
{
    computerEnable(TRUE);    
    Computers *computers = new Computers();
    Computer *computer = computers->getItem(computerListBox->currentItem());
    computerNameTextLineEdit->setText(computer->getName());
    computerBrandTextLineEdit->setText(computer->getBrand());
    computerModelTextLineEdit->setText(computer->getModel());
    computerSettingsTextLineEdit->setText(QString::number(computer->getSettings()));
    computerTripDistanceCheckBox->setChecked(computer->getTripDistance());
    computerTripTimeCheckBox->setChecked(computer->getTripTime());
    computerAverageCadenceCheckBox->setChecked(computer->getAverageCadence());
    computerAltimeterCheckBox->setChecked(computer->getAltiMeter());
    computerAverageSpeedCheckBox->setChecked(computer->getAverageSpeed());
    computerMaximumSpeedCheckBox->setChecked(computer->getMaxSpeed());    
    computerOdoMeterCheckBox->setChecked(computer->getOdoMeter());    
    computerMaximumOdoTextLineEdit->setText(QString::number(computer->getMaxOdo()));      
    delete (computers);    
}

void prefWindow::computerSavePushButtonClicked()
{
    if (computerNameTextLineEdit->text() == "") return;    
    Computers *computers = new Computers();
    Computer *computer;   
    if (computerListBox->currentItem() != -1 && computerListBox->isSelected(computerListBox->currentItem())) {
        computer = computers->getItem(computerListBox->currentItem());
    }
    else {
        computer = new Computer();
    }
    computer->setName(computerNameTextLineEdit->text());
    computer->setBrand(computerBrandTextLineEdit->text());
    computer->setModel(computerModelTextLineEdit->text());    
    computer->setSettings(computerSettingsTextLineEdit->text().toDouble());
    computer->setTripDistance(computerTripDistanceCheckBox->isChecked());     
    computer->setTripTime(computerTripTimeCheckBox->isChecked());
    computer->setAverageCadence(computerAverageCadenceCheckBox->isChecked());
    computer->setAltiMeter(computerAltimeterCheckBox->isChecked());
    computer->setAverageSpeed(computerAverageSpeedCheckBox->isChecked());    
    computer->setMaxSpeed(computerMaximumSpeedCheckBox->isChecked());    
    computer->setOdoMeter(computerOdoMeterCheckBox->isChecked());        
    computer->setMaxOdo(computerMaximumOdoTextLineEdit->text().toDouble());
    if (computerListBox->currentItem() != -1 && computerListBox->isSelected(computerListBox->currentItem())) {
        computer = computers->getItem(computerListBox->currentItem());
        computer->upd();
    }
    else {
        computer->save();
        delete(computer);
    }
    initComputers();
    computerEnable(FALSE);

    delete (computers);    
}

void prefWindow::initFrames()
{
    int i;    
    Frames *frames = new Frames();
    frameListBox->clear();    
    for (i=0; i<frames->getSize(); i++) {
        frameListBox->insertItem(frames->getItem(i)->getName());
    }
    delete(frames);
}

void prefWindow::frameSavePushButtonClicked()
{
    if (frameNameTextLineEdit->text() == "") return;    
    Frames *frames = new Frames();
    Frame *frame;   
    if (frameListBox->currentItem() != -1 && frameListBox->isSelected(frameListBox->currentItem())) {
        frame = frames->getItem(frameListBox->currentItem());
    }
    else {
        frame = new Frame();
    }
    frame->setName(frameNameTextLineEdit->text());
    frame->setModel(frameModelTextLineEdit->text());    
    frame->setSerialNumber(frameSerialNumberTextLineEdit->text());
    frame->setSensorPos(frameSensorPositionComboBox->currentText());    
    frame->setType(frameTypeComboBox->currentText());
    frame->setDescription(frameDescriptionTextEdit->text());    
    if (frameListBox->currentItem() && frameListBox->isSelected(frameListBox->currentItem())) {
        frame->upd();
    }
    else {
        frame->save();
        delete(frame);
    }
    initFrames();
    frameEnable(FALSE);
    delete(frames);    
}


void prefWindow::checkPointsListBoxClicked()
{
    checkPointsEnable(TRUE);    
    Trails *trails = new Trails();
    CheckPoints *checkPoints = new CheckPoints(trails->getItem(trailsListBox->currentItem())->getOid());
    CheckPoint *checkPoint = checkPoints->getItem(checkPointsListBox->currentItem());
    checkPointsLocationTextLineEdit->setText(checkPoint->getLocation());
    checkPointsDistanceTextLineEdit->setText(QString::number(checkPoint->getDistance()));
    checkPointsAltitudeTextLineEdit->setText(QString::number(checkPoint->getAltitude()));
    delete(trails);    
    delete(checkPoints);
    
}


void prefWindow::backWheelListBoxClicked()
{
    backWheelEnable(TRUE);    
    Wheels *wheels = new Wheels("back");
    Wheel *wheel = wheels->getItem(backWheelListBox->currentItem());
    backWheelNameTextLineEdit->setText(wheel->getName());
    backWheelBrandTextLineEdit->setText(wheel->getBrand());
    backWheelModelTextLineEdit->setText(wheel->getModel());
    backWheelCircumferenceTextLineEdit->setText(QString::number(wheel->getCircumference()));
    backWheelDescriptionTextEdit->setText(wheel->getDescription());
    delete (wheels);
    
}




void prefWindow::trailsStationaryClicked()
{
    trailsUseFrontWheelCheckBox->setEnabled(trailsStationaryCheckBox->isChecked());        
    trailsUseBackWheelCheckBox->setEnabled(trailsStationaryCheckBox->isChecked());
}


void prefWindow::trailsNewPushButtonClicked()
{
    trailsListBox->clearSelection();
    trailsEnable(TRUE);
}


void prefWindow::trailsEnable(bool e)
{
    trailsNameTextLineEdit->setEnabled(e);
    trailsNameTextLineEdit->setText("");
    trailsStationaryCheckBox->setEnabled(e);
    trailsStationaryCheckBox->setChecked(FALSE);        
    trailsSkillLevelComboBox->setEnabled(e);
    trailsSkillLevelComboBox->clear();
    trailsMapReferenceTextLineEdit->setEnabled(e);
    trailsMapReferenceTextLineEdit->setText("");
    trailsDistanceTextLineEdit->setEnabled(e);
    trailsDistanceTextLineEdit->setText("");
    trailsRoadConditionComboBox->setEnabled(e);
    trailsRoadConditionComboBox->clear();
    trailsDescriptionTextEdit->setEnabled(e);
    trailsDescriptionTextEdit->setText("");
    trailsUseFrontWheelCheckBox->setEnabled(FALSE);
    trailsUseFrontWheelCheckBox->setChecked(FALSE);
    trailsUseBackWheelCheckBox->setEnabled(FALSE);
    trailsUseBackWheelCheckBox->setChecked(FALSE);    
    trailsMaxAltitudeTextLineEdit->setEnabled(e);
    trailsMaxAltitudeTextLineEdit->setText("");
    trailsMinAltitudeTextLineEdit->setEnabled(e);
    trailsMinAltitudeTextLineEdit->setText("");    
    trailsAccumAltitudeTextLineEdit->setEnabled(e);
    trailsAccumAltitudeTextLineEdit->setText("");
    trailsSavePushButton->setEnabled(e);
    
    SkillLevels *skillLevels = new SkillLevels();
    RoadConditions *roadConditions = new RoadConditions();
    int i;
    for (i = 0; i < skillLevels->getSize(); i++) {
        trailsSkillLevelComboBox->insertItem(QString(skillLevels->getItem(i)), -1);
    }      
    for (i = 0; i < roadConditions->getSize(); i++) {
        trailsRoadConditionComboBox->insertItem(roadConditions->getItem(i), -1);
    }
  
}


void prefWindow::frameNewPushButtonClicked()
{
    frameListBox->clearSelection();
    frameEnable(TRUE);
}


void prefWindow::frameEnable( bool e )
{
    frameNameTextLineEdit->setEnabled(e);
    frameNameTextLineEdit->setText("");
    frameModelTextLineEdit->setEnabled(e);
    frameModelTextLineEdit->setText("");
    frameSerialNumberTextLineEdit->setEnabled(e);
    frameSerialNumberTextLineEdit->setText("");    
    frameSensorPositionComboBox->setEnabled(e);
    frameSensorPositionComboBox->clear();
    frameSensorPositionComboBox->insertItem("front");
    frameSensorPositionComboBox->insertItem("back");
    frameSensorPositionComboBox->insertItem("none");
    frameTypeComboBox->setEnabled(e);
    frameTypeComboBox->clear();
    FrameTypes *frameTypes = new FrameTypes();
    for (int i = 0; i<frameTypes->getSize(); i++) {
        frameTypeComboBox->insertItem(frameTypes->getItem(i), -1);    }
    frameDescriptionTextEdit->setEnabled(e);
    frameDescriptionTextEdit->setText("");
    frameSavePushButton->setEnabled(e);
}



void prefWindow::frontWheelSavePushButtonClicked()
{
    if (frontWheelNameTextLineEdit->text() == "") return;    
    Wheels *frontWheels = new Wheels("front");
    Wheel *frontWheel;
    if (frontWheelListBox->currentItem() != -1 && frontWheelListBox->isSelected(frontWheelListBox->currentItem())) {
        frontWheel = frontWheels->getItem(frontWheelListBox->currentItem());
    }
    else {
        frontWheel = new Wheel();
        frontWheel->setType("front");        
    }

    frontWheel->setName(frontWheelNameTextLineEdit->text());
    frontWheel->setBrand(frontWheelBrandTextLineEdit->text());
    frontWheel->setModel(frontWheelModelTextLineEdit->text());
    frontWheel->setCircumference(frontWheelCircumferenceTextLineEdit->text().toDouble());
    frontWheel->setDescription(frontWheelDescriptionTextEdit->text());
    if (frontWheelListBox->currentItem()!=-1 && frontWheelListBox->isSelected(frontWheelListBox->currentItem())) {
        frontWheel->upd();
    }
    else {
        frontWheel->save();
        delete(frontWheel);
    }
    initFrontWheels();
    frontWheelEnable(FALSE);

    delete(frontWheels);

}


void prefWindow::frontWheelNewPushButtonClicked()
{
    frontWheelEnable(TRUE);
    frontWheelListBox->clearSelection();
    frontWheelListBox->setCurrentItem(-1);
}

void prefWindow::backWheelEnable( bool e )
{
    backWheelNameTextLineEdit->setEnabled(e);
    backWheelNameTextLineEdit->setText("");
    backWheelBrandTextLineEdit->setEnabled(e);
    backWheelBrandTextLineEdit->setText("");
    backWheelModelTextLineEdit->setEnabled(e);
    backWheelModelTextLineEdit->setText("");
    backWheelCircumferenceTextLineEdit->setEnabled(e);
    backWheelCircumferenceTextLineEdit->setText("");
    backWheelDescriptionTextEdit->setEnabled(e);
    backWheelDescriptionTextEdit->setText("");
    backWheelSavePushButton->setEnabled(e);
}

void prefWindow::backWheelSavePushButtonClicked()
{
    if (backWheelNameTextLineEdit->text() == "") return;    
    Wheels *backWheels = new Wheels("back");
    Wheel *backWheel;   
    if (backWheelListBox->currentItem() != -1 && backWheelListBox->isSelected(backWheelListBox->currentItem())) {
        backWheel = backWheels->getItem(backWheelListBox->currentItem());
    }
    else {
        backWheel = new Wheel();
        backWheel->setType("back");        
    }

    backWheel->setName(backWheelNameTextLineEdit->text());
    backWheel->setBrand(backWheelBrandTextLineEdit->text());
    backWheel->setModel(backWheelModelTextLineEdit->text());
    backWheel->setCircumference(backWheelCircumferenceTextLineEdit->text().toDouble());
    backWheel->setDescription(backWheelDescriptionTextEdit->text());
    if (backWheelListBox->currentItem()!=-1 && backWheelListBox->isSelected(backWheelListBox->currentItem())) {
        backWheel->upd();
    }
    else {
        backWheel->save();
        delete(backWheel);
    }
    initBackWheels();
    backWheelEnable(FALSE);
    delete(backWheels);
}


void prefWindow::backWheelNewPushButtonClicked()
{
    backWheelListBox->clearSelection();
    backWheelEnable(TRUE);

}


void prefWindow::tireSavePushButtonClicked()
{
    if (tireNameTextLineEdit->text() == "") return; 
    Tires *tires = new Tires();
    Tire *tire;   
    if (tireListBox->currentItem() != -1 && tireListBox->isSelected(tireListBox->currentItem())) {
        tire = tires->getItem(tireListBox->currentItem());
    }
    else {
        tire = new Tire();
    }

    tire->setName(tireNameTextLineEdit->text());
    tire->setBrand(tireBrandTextLineEdit->text());
    tire->setModel(tireModelTextLineEdit->text());
    if (tireListBox->currentItem()!=-1 && tireListBox->isSelected(tireListBox->currentItem())) {
        tire->upd();
    }
    else {
        tire->save();
        delete(tire);
    }
    initTires();
    tireEnable(FALSE);
    delete(tires);

}


void prefWindow::tireNewPushButtonClicked()
{
    tireListBox->clearSelection();
    tireEnable(TRUE);
}


void prefWindow::tireEnable( bool e )
{
    tireNameTextLineEdit->setEnabled(e);
    tireNameTextLineEdit->setText("");
    tireBrandTextLineEdit->setEnabled(e);
    tireBrandTextLineEdit->setText("");
    tireModelTextLineEdit->setEnabled(e);
    tireModelTextLineEdit->setText("");
   
    tireSavePushButton->setEnabled(e);
    
}


void prefWindow::computerEnable( bool e )
{
    computerNameTextLineEdit->setEnabled(e);
    computerNameTextLineEdit->setText("");
    computerBrandTextLineEdit->setEnabled(e);
    computerBrandTextLineEdit->setText("");
    computerModelTextLineEdit->setEnabled(e);
    computerModelTextLineEdit->setText("");
    computerSettingsTextLineEdit->setEnabled(e);
    computerSettingsTextLineEdit->setText("");
    computerTripDistanceCheckBox->setEnabled(e);
    computerTripDistanceCheckBox->setChecked(FALSE);
    computerTripTimeCheckBox->setEnabled(e);
    computerTripTimeCheckBox->setChecked(FALSE);
    computerAverageCadenceCheckBox->setEnabled(e);
    computerAverageCadenceCheckBox->setChecked(FALSE);
    computerAltimeterCheckBox->setEnabled(e);
    computerAltimeterCheckBox->setChecked(FALSE);
    computerAverageSpeedCheckBox->setEnabled(e);
    computerAverageSpeedCheckBox->setChecked(FALSE);
    computerMaximumSpeedCheckBox->setEnabled(e);
    computerMaximumSpeedCheckBox->setChecked(FALSE);
    computerOdoMeterCheckBox->setEnabled(e);
    computerOdoMeterCheckBox->setChecked(FALSE);
    computerMaximumOdoTextLineEdit->setEnabled(e);
    computerMaximumOdoTextLineEdit->setText("");

    computerSavePushButton->setEnabled(e);
}


void prefWindow::bikeGearingEnable( bool e )
{
    bikeGearingNameTextLineEdit->setEnabled(e);
    bikeGearingNameTextLineEdit->setText("");
    bikeGearingChainWheelListBox->setEnabled(e);
    bikeGearingChainWheelListBox->clear();
    bikeGearingSavePushButton->setEnabled(e);
}


void prefWindow::wheelGearingEnable( bool e )
{
    wheelGearingNameTextLineEdit->setEnabled(e);
    wheelGearingNameTextLineEdit->setText("");
    wheelGearingChainWheelListBox->setEnabled(e);
    wheelGearingChainWheelListBox->clear();
    wheelGearingSavePushButton->setEnabled(e);
}


void prefWindow::checkPointsEnable( bool e )
{
    checkPointsCurrentTrailTextLineEdit->setEnabled(e);
    checkPointsLocationTextLineEdit->setEnabled(e);
    checkPointsLocationTextLineEdit->setText("");
    checkPointsDistanceTextLineEdit->setEnabled(e);
    checkPointsDistanceTextLineEdit->setText("");
    checkPointsAltitudeTextLineEdit->setEnabled(e);
    checkPointsAltitudeTextLineEdit->setText("");

    checkPointsSavePushButton->setEnabled(e);

}


void prefWindow::frameListBoxClicked()
{
    frameEnable(TRUE);
    int i;    
    Frames *frames = new Frames();
    Frame *frame = frames->getItem(frameListBox->currentItem());
    frameNameTextLineEdit->setText(frame->getName());
    frameModelTextLineEdit->setText(frame->getModel());
    frameSerialNumberTextLineEdit->setText(frame->getSerialNumber());
    frameDescriptionTextEdit->setText(frame->getDescription());    
    frameSensorPositionComboBox->clear();
    frameSensorPositionComboBox->insertItem("front");
    frameSensorPositionComboBox->insertItem("back");
    frameSensorPositionComboBox->insertItem("none");
    if (frame->getSensorPos() == "front"){
        frameSensorPositionComboBox->setCurrentItem(0);
    }
    else if (frame->getSensorPos() == "back") {
        frameSensorPositionComboBox->setCurrentItem(1);
    }
    else {
        frameSensorPositionComboBox->setCurrentItem(2);
    }
    FrameTypes *frameTypes = new FrameTypes();
    frameTypeComboBox->clear();    
    for (i = 0; i<frameTypes->getSize(); i++) {
        frameTypeComboBox->insertItem(frameTypes->getItem(i), -1);
        if (frameTypes->getItem(i) == frame->getType()) frameTypeComboBox->setCurrentItem(i);
    }
    frameSavePushButton->setEnabled(TRUE);
    delete(frames);

}


void prefWindow::frontWheelEnable( bool e )
{
    frontWheelNameTextLineEdit->setEnabled(e);
    frontWheelNameTextLineEdit->setText("");
    frontWheelBrandTextLineEdit->setEnabled(e);
    frontWheelBrandTextLineEdit->setText("");
    frontWheelModelTextLineEdit->setEnabled(e);
    frontWheelModelTextLineEdit->setText("");
    frontWheelCircumferenceTextLineEdit->setEnabled(e);
    frontWheelCircumferenceTextLineEdit->setText("");
    frontWheelDescriptionTextEdit->setEnabled(e);
    frontWheelDescriptionTextEdit->setText("");
    frontWheelSavePushButton->setEnabled(e);

}


void prefWindow::checkPointsNewPushButtonClicked()
{
    if (checkPointsCurrentTrailTextLineEdit->text() != "") {
        checkPointsListBox->clearSelection();
        checkPointsEnable(TRUE);
    }
}


void prefWindow::checkPointsSavePushButtonClicked()
{
    if (checkPointsLocationTextLineEdit->text() == "") return;
    Trails *trails = new Trails();    
    CheckPoints *checkPoints = new CheckPoints(trails->getItem(trailsListBox->currentItem())->getOid());
    CheckPoint *checkPoint;   
    if (checkPointsListBox->currentItem() != -1 && checkPointsListBox->isSelected(checkPointsListBox->currentItem())) {
        checkPoint = checkPoints->getItem(checkPointsListBox->currentItem());
    }
    else {
        checkPoint = new CheckPoint();
        checkPoint->setTrail(trails->getItem(trailsListBox->currentItem())->getOid());
    }

    checkPoint->setLocation(checkPointsLocationTextLineEdit->text());
    checkPoint->setDistance(checkPointsDistanceTextLineEdit->text().toDouble());
    checkPoint->setAltitude(checkPointsAltitudeTextLineEdit->text().toDouble());
    if (checkPointsListBox->currentItem()!=-1 && checkPointsListBox->isSelected(checkPointsListBox->currentItem())) {
        checkPoint->upd();
    }
    else {
        checkPoint->save();
        delete(checkPoint);
    }
    initCheckPoints();
    checkPointsEnable(FALSE);
    delete(checkPoints); 
}


void prefWindow::initCheckPoints()
{
    Trails *trails = new Trails();    
    Trail *trail;
    int i;
    if (trailsListBox->currentItem() != -1 && trailsListBox->isSelected(trailsListBox->currentItem())) {
        trail = trails->getItem(trailsListBox->currentItem());
        checkPointsCurrentTrailTextLineEdit->setText(trail->getName());
        CheckPoints *checkPoints = new CheckPoints(trail->getOid());
        checkPointsListBox->clear();
        for (i = 0; i<checkPoints->getSize(); i++) {
            checkPointsListBox->insertItem(checkPoints->getItem(i)->getLocation());
        } 
        if (checkPoints->getSize()) {
            checkPointsListBox->setEnabled(TRUE);
        }
        else {
            checkPointsListBox->setEnabled(FALSE);
        }
        delete(checkPoints);
    }
    delete(trails);

}

void prefWindow::wheelGearingNoOfTeethSpinBoxValueChanged()
{
    if(wheelGearingChainWheelListBox->currentText().toInt() == wheelGearingNumberOfTeethSpinBox->value()) return;
      QString qs;
    if (wheelGearingNumberOfTeethSpinBox->value()<10) {
        qs = " "+QString::number(wheelGearingNumberOfTeethSpinBox->value());
    }
    else {
        qs = QString::number(wheelGearingNumberOfTeethSpinBox->value());
    }
    if (wheelGearingChainWheelListBox->currentItem() != -1) {
        wheelGearingChainWheelListBox->changeItem(qs, wheelGearingChainWheelListBox->currentItem());
    }
    else {
        wheelGearingChainWheelListBox->insertItem(qs, -1);
        wheelGearingChainWheelListBox->setSelected(wheelGearingChainWheelListBox->numRows()-1, TRUE);
    }
    wheelGearingChainWheelListBox->sort();
}


void prefWindow::changeUnits()
{
    Preferences *preferences = Preferences::Instance();
    frontWheelCircumferenceUnitTextLabel->setText(preferences->getWidth());
    backWheelCircumferenceUnitTextLabel->setText(preferences->getWidth());
    computerSettingsUnitTextLabel->setText(preferences->getWidth());
    computerMaximumODOUnitTextLabel->setText(preferences->getDistance());
    trailsDistanceKmTextLabel->setText(preferences->getDistance());
    checkpointsDistanceKmTextLabel->setText(preferences->getDistance());
    checkpointsAltitudeMTextLabel->setText(preferences->getHeight());
    if (preferences->getHeightMeters())    {
        trailsMaxAltitudeMTextLabel->setText("m");
        trailsMinAltitudeMTextLabel->setText("m");
        trailsAccumAltitudeMTextLabel->setText("m");
    }
    else {
        trailsMaxAltitudeMTextLabel->setText("ft");
        trailsMinAltitudeMTextLabel->setText("ft");
        trailsAccumAltitudeMTextLabel->setText("ft");
    }
}



void prefWindow::killBill2()
{
    this->close(1);
}


void prefWindow::computerNewPushButtonClicked()
{
    computerListBox->clearSelection();
    computerEnable(TRUE);
}
