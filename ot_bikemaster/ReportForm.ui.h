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
#include <vector.h>
#include "ReportItem.h"
#include <iostream>
#include <sstream>
#include "DbConn.h"


vector<QString>bikeV;
vector<QString>trailV;
vector<ReportItem*>report; 
QString currentItemType;    
   
void ReportForm::init()
{
    this->setWFlags (Qt::WDestructiveClose); 
    string sqlq;
    DbConn* db = DbConn::Instance();
    
    bikeV.clear();
    sqlq= "SELECT name FROM frame";
    QSqlQuery qBikes = db->get(sqlq);
    while(qBikes.next()) {
        bikeV.push_back(qBikes.value(0).toString());
    }
    
    trailV.clear();
    sqlq= "SELECT name FROM trail";
    QSqlQuery qTrails = db->get(sqlq);
    while(qTrails.next()) {
        trailV.push_back(qTrails.value(0).toString());
    }
    
    Preferences* pref = Preferences::Instance();
    if (pref->getDateOrderMdy()) {
        minDate->setOrder(QDateEdit::MDY);
        maxDate->setOrder(QDateEdit::MDY);
    } else if (pref->getDateOrderDmy()) {
        minDate->setOrder(QDateEdit::DMY);
        maxDate->setOrder(QDateEdit::DMY);
    }  else if (pref->getDateOrderYmd()) {
        minDate->setOrder(QDateEdit::YMD);
        maxDate->setOrder(QDateEdit::YMD);
    }

    itemStack->raiseWidget(2); /*Startar en tom WidgetStackPage*/
}
void ReportForm::destroy(){
    report.clear();
    bikeV.clear();
    trailV.clear();
}

/*lists the avalible items and more*/
void ReportForm::listItemSlot()
{
    currentItemType = itemComboBox->currentText();
    if( operator==(currentItemType,"Bikes") || operator==(currentItemType,"Trails") ){
        listItems(currentItemType);
    }
    else if( operator==(currentItemType,"Altitude") ){
        itemStack->raiseWidget(1);
    } 
    else if( operator==(currentItemType,"Average Speed") ){
        itemStack->raiseWidget(3);
    }
    else if( operator==(currentItemType,"Date") ) {
        itemStack->raiseWidget(4);
    }
    else if( operator==(currentItemType,"") ){
        itemStack->raiseWidget(2);
    }
}

/*triggs the addReportItem function with and operator*/
void ReportForm::addAndItemSlot()
{
    addReportItem("and");
    listReportItems();
    listItems(currentItemType);
}

/*trigges the addReportItem function with or operator */
void ReportForm::addOrItemSlot()
{
    addReportItem("or");
    listReportItems();
    listItems(currentItemType);
}


/*Prints the ReportItems list to the Report View Box*/
void ReportForm::listReportItems()
{
    QString reportItem;
    stringstream ss;
    string bapp;
    
    reportItemListBox->clear();
    reportOpListBox->clear();
    vector<ReportItem*>::iterator index;
    index = report.begin();
    
    while(index !=  report.end()){
        reportItem = (*index)->getItemName();
        if( (*index)->getMinValue() != -1){
            ss  << "(" << (*index)->getMinValue() << " - " << (*index)->getMaxValue() << ")";
            getline(ss,bapp);
            reportItem = reportItem+" "+bapp;
            ss.clear();
        }
        else if( operator==( (*index)->getItemType(),"Date" ) ){
            ss <<"(" << (*index)->getStartDate().toString("yyyyMMdd") <<" - "
                    <<(*index)->getStopDate().toString("yyyyMMdd")<<")";
            getline(ss,bapp);
            reportItem = reportItem+" "+bapp;
            ss.clear();
        }
           
        reportItemListBox->insertItem(reportItem);
        if(reportOpListBox->numRows() > 0){
            reportOpListBox->insertItem((*index)->getOperator());
        }
        else {
            reportOpListBox->insertItem("");
        }
        index++;
    }
}


/*Remove items from the report view box*/
void ReportForm::removeItemSlot(){
    stringstream ss;
    string bapp;
    QString reportItem;
    if(reportItemListBox->currentItem() != -1){    
        vector<ReportItem*>::iterator index; 
        index = report.begin(); 
        while(index !=  report.end()){
            reportItem = (*index)->getItemName();
            if( (*index)->getMinValue() != -1){
                ss  << "(" << (*index)->getMinValue() << " - " << (*index)->getMaxValue() << ")";
                getline(ss,bapp);
                reportItem = reportItem+" "+bapp;
                ss.clear();
            }
            else if( operator==( (*index)->getItemType(),"Date" ) ){
                ss <<"(" << (*index)->getStartDate().toString("yyyyMMdd") <<" - "
                        <<(*index)->getStopDate().toString("yyyyMMdd")<<")";
                getline(ss,bapp);
                reportItem = reportItem+" "+bapp;
                ss.clear();
            }
  
            if( operator==(reportItem,reportItemListBox->currentText() ) ){
                /*if bike or trail item is to put back into it's vector*/
                if(operator==(reportItemListBox->currentText(),(*index)->getItemName())){
                    if( operator==("Bikes",(*index)->getItemType()) ){
                        bikeV.push_back(reportItemListBox->currentText());
                    }
                    if( operator==("Trails",(*index)->getItemType()) ){
                        trailV.push_back(reportItemListBox->currentText());
                    }
                }
                break;
            }
            index++;
        } 
        report.erase(index);
        listReportItems();
        listItems(currentItemType);
    } 
}

/*Prints items to the ListItemView*/
void ReportForm::listItems(QString itemType)
{
    vector<QString>::iterator x;       
    itemListBox->clear();
    if( operator==(itemType,"Bikes") ){
        itemStack->raiseWidget(0);
        x = bikeV.begin();
        while(x != bikeV.end()){
            itemListBox->insertItem(*x); 
            x++;
        }
    }
    else if( operator==(itemType,"Trails") ){
        itemStack->raiseWidget(0);
        x = trailV.begin();
        while(x != trailV.end()){
            itemListBox->insertItem(*x); 
            x++;
        }
    }
}

/* add report item function*/
void ReportForm::addReportItem(QString operatorType)
{
    ReportItem *rItem = new ReportItem();
    QString itemName;
    stringstream ss;
    string bapp;
    
    if( operator==(currentItemType,"Bikes") || operator==(currentItemType,"Trails") ){
        if(itemListBox->currentItem() != -1){
            itemName = itemListBox->currentText();
            rItem = new ReportItem(operatorType,currentItemType,itemName);
        }
        else {
            return ; // no item was highlighted or no item existed in the itemView, function terminates.
        }
    }
    if( operator==(currentItemType,"Date") ){
        rItem = new ReportItem(operatorType,currentItemType,currentItemType,minDate->date(),maxDate->date() );
    } 
    else if( operator==( currentItemType,"Altitude" ) || operator==(currentItemType,"Average Speed") ){
        itemName = currentItemType;
        if( operator==( itemName,"Altitude" ) ){
            rItem = new ReportItem( operatorType, currentItemType, itemName, minTime->value(), maxTime->value() );
        }     
        else if( operator==(itemName,"Average Speed") ){
            rItem = new ReportItem( operatorType, currentItemType, itemName, minSpeed->value(), maxSpeed->value() );
        }
    }
    report.push_back(rItem);

    /*if currentItemType  is Bikes or Trails then the item will be removed from the item current itemlist BikeV or TrailV */
    vector<QString>::iterator index;
    if(operator==(currentItemType,"Bikes") ){
        index = bikeV.begin(); 
        while( index != bikeV.end() ) {
            if( operator==(itemListBox->currentText(),*index) ){
                bikeV.erase(index);
                break;
            } 
            index++;
        }
    }
    if(operator==(currentItemType,"Trails") ){
        index = trailV.begin(); 
        while( index != trailV.end() ) {
            if( operator==(itemListBox->currentText(),*index) ){
                trailV.erase(index);
                break;
            } 
            index++;
        }
    }
}


void ReportForm::genSqlSlot()
{
    QString bapp ="";
    vector<ReportItem*>::iterator index;
    for(index = report.begin(); index != report.end(); index++){
        if(index != report.begin() ){
            bapp += (*index)->getOperator()+" ";
        }
         bapp += (*index)->getSql()+" ";
    }
    
    ReportDisplay* display = new ReportDisplay();
    Report reportInstance = Report(QDate::currentDate(), QDate::currentDate(), 0);
    QString fileName, reportResult;
    
    fileName = QString("CombinedReport");
    reportInstance.combinedRep(bapp);
    reportResult = reportInstance.getResult();
    display->writeReport(reportResult,fileName);
    display->show();
    //cerr << bapp;
}



void ReportForm::KillSlot()
{
    this->close(1);
}
