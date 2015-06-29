#ifndef PREFERENCES_H
#define PREFERENCES_H
#include <string>
#include "DbConn.h"
//#include "DbConn.h"
using namespace std;
class Preferences{
    public:
        //constructors

        static Preferences* Instance();
  
        //member functions

	void setDistance(QString);
	void setDistanceKm(bool);
	void setDistanceMiles(bool);
	void setHeight(QString);
	void setHeightMeters(bool);
	void setHeightFeet(bool);
	void setSpeed(QString);
	void setSpeedKmh(bool);
	void setSpeedMph(bool);
	void setTemperature(QString);
	void setTemperatureDegreesC(bool);
	void setTemperatureDegreesF(bool);
	void setWeight(QString);
	void setWeightKilo(bool);
	void setWeightPound(bool);
	void setWidth(QString);
	void setWidthCm(bool);
	void setWidthInch(bool);
	void setPresentation(QString);
	void setPresentationBikeUsed(bool); 
	void setPresentationDistance(bool);
	void setPresentationTime(bool);
	void setPresentationTrail(bool);

	void setDateOrder(QString);
	void setDateOrderMdy(bool);
	void setDateOrderDmy(bool);
	void setDateOrderYmd(bool);
	void setMonthFormat(QString);
	void setMonthFormatFull(bool);
	void setMonthFormatShort(bool);
	void setMonthFormatNumber(bool);
	void setWeekStarts(QString);
	void setWeekStartsMonday(bool);
	void setWeekStartsSunday(bool);
	void setDayLeadingZeroes(bool);
	void setDayLeadingZeroes1(bool);
	void setDayLeadingZeroes01(bool);
	void setCentury(int);
	void setCentury90(bool);
	void setCentury2000(bool);
	void save();

	QString getDistance();
	bool getDistanceKm();
	bool getDistanceMiles();
	QString getHeight();
	bool getHeightMeters();
	bool getHeightFeet();  
	QString getSpeed();
	bool getSpeedKmh();
	bool getSpeedMph();
	QString getTemperature();
	bool getTemperatureDegreesC();
	bool getTemperatureDegreesF();
	QString getWeight();
	bool getWeightKilo();
	bool getWeightPound();
	QString getWidth();
	bool getWidthCm();
	bool getWidthInch();
	QString getPresentation();
	bool getPresentationBikeUsed(); 
	bool getPresentationDistance(); 
	bool getPresentationTime(); 
	bool getPresentationTrail(); 
 
	QString getDateOrder();
	bool getDateOrderMdy();
	bool getDateOrderDmy();
	bool getDateOrderYmd();
	QString getMonthFormat();
	bool getMonthFormatFull();
	bool getMonthFormatShort();
	bool getMonthFormatNumber();
	QString getWeekStarts();
	bool getWeekStartsMonday();
	bool getWeekStartsSunday();
	bool getDayLeadingZeroes();
	bool getDayLeadingZeroes1();
	bool getDayLeadingZeroes01();
	int getCentury();
	bool getCentury90();
	bool getCentury2000();

    protected:
    
	Preferences();

    private:

	static Preferences* prefInstance;
        QString distance;
        QString height;
        QString speed;
        QString temperature;
        QString weight;
        QString width;
        QString presentation;

        QString dateOrder;
        QString monthFormat;
        QString weekStarts;
        bool dayLeadingZeroes;
        int century;
};

#endif
