#include "ReportItem.h"
#include <iostream>

ReportItem::ReportItem() {
}

ReportItem::ReportItem(QString newOp, QString newItemType, QString newItemName) {
    op = newOp;
    itemType = newItemType;
    itemName = newItemName;
    minValue = -1;
    maxValue = -1;
}

ReportItem::ReportItem(QString newOp, QString newItemType, QString newItemName, double newMinValue,
                       double newMaxValue) {
    op = newOp;
    itemType = newItemType;
    itemName = newItemName;
    minValue = newMinValue;
    maxValue = newMaxValue;
}
ReportItem::ReportItem(QString newOp, QString newItemType, QString newItemName, QDate newStartDate, QDate newStopDate) {
    op = newOp;
    itemType = newItemType;
    itemName = newItemName;
    startDate = newStartDate;
    stopDate = newStopDate;
    minValue = -1;
    maxValue = -1;
}

void ReportItem::setOperator(QString newOp){
    this->op = newOp;
}
void ReportItem::setItemType(QString newItemType){
    this->itemType = newItemType;
}

void ReportItem::setItemName(QString newItemName){
    this->itemName = newItemName;
}
void ReportItem::setMinValue(double newMinValue){
    this->minValue = newMinValue;
}
void ReportItem::setMaxValue(double newMaxValue){
    this->maxValue = newMaxValue;
}

QString ReportItem::getOperator(){
    return this->op;
}

QString ReportItem::getItemType(){
    return this->itemType;
}
QString ReportItem::getItemName(){
    return this->itemName;
}
double ReportItem::getMinValue(){
    return this->minValue;
}
double ReportItem::getMaxValue(){
    return this->maxValue;
}
QDate ReportItem::getStartDate(){
    return this->startDate;
}
QDate ReportItem::getStopDate(){
    return this->stopDate;
}

QString ReportItem::getSql(){
    stringstream ss;
    string bapp;
    if( operator==(this->itemType,"Bikes") ){
        ss << "(f.name = '" << this->itemName << "')";
        getline(ss,bapp);
        ss.clear();
    }
    if(operator==(this->itemType,"Trails")){
        ss << "(t.name = '" << this->itemName << "')";
        getline(ss,bapp);
        ss.clear();
    }
    if(operator==(this->itemType,"Average Speed")){
        ss << "(r.averagespeed >=" << this->minValue << " AND r.averagespeed <=" << this->maxValue << ")";
        getline(ss,bapp);
        ss.clear();
    }
    if(operator==(this->itemType,"Altitude")){
        ss <<"(t.accumaltitude >=" << this->minValue << " AND t.accumaltitude <=" << this->maxValue <<")";
        getline(ss,bapp);
        ss.clear();
    }
    if(operator==(this->itemType,"Date")){
        ss << "(r.ridedate >= '" << this->startDate.toString("yyyy-MM-dd") << "' AND r.ridedate <= '" 
                << this->stopDate.toString("yyyy-MM-dd") <<"' )";
        getline(ss,bapp);
        ss.clear();
    }
    return bapp;
}
    
    
    
  
