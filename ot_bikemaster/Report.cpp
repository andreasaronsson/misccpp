#include "Report.h"

Report::Report(QDate newStart, QDate newStop, int newYear)
{
    start = newStart;
    stop = newStop;
    year = newYear;
}
QDate Report::getStart ()
{
    return start; 
}
void Report::setStart (QDate newStart)
{
    start = newStart;
}
QDate Report::getStop ()
{
    return stop; 
}
void Report::setStop (QDate newStop)
{
    stop = newStop;
}
int Report::getYear ()
{
    return year; 
}
void Report::setYear (int newYear)
{
    year = newYear;
}
QString Report::getResult ()
{
    return result; 
}
void Report::setResult (QString newResult)
{
    result = newResult;
}

void Report::combinedRep(string cond)
{
   DbConn* db = DbConn::Instance();

   stringstream ss;
   string name;
   ss << "Combined";
   getline(ss, name);
   ss.clear();
   head(name);
   
   string sqlq = "SELECT r.ridedate AS date, f.name AS bike, t.name AS trail, EXTRACT(EPOCH";
   sqlq += " FROM r.trainingtime) AS time, ROUND(CAST(r.odoafter-r.odobefore AS";
   sqlq += " NUMERIC),1) AS distance, ROUND(CAST(r.averagespeed AS NUMERIC),1) AS avs";
   sqlq += " FROM ride r, bike b, frame f, trail t WHERE r.bike=b.id AND b.frame=f.id AND";
   sqlq += " r.trail=t.id AND( ";
   sqlq += cond;
   sqlq += " ) ORDER BY r.ridedate;";

   this->result.append(fixLength("Date",11,' ',0));
   this->result.append(fixLength("Bike",16,' ',0));
   this->result.append(fixLength("Trail",30,' ',0));
   this->result.append(fixLength("Time",10,' ',1));
   this->result.append(fixLength("Dst.",7,' ',1));
   this->result.append(fixLength("Avs.",6,' ',1) + "\n");
   
   line80("-");
   
   QSqlQuery qComb = db->get(sqlq);
   
   while (qComb.next()) {
      this->result.append(fixLength(qComb.value(0).toString(),11,' ',0));
      this->result.append(fixLength(qComb.value(1).toString(),16,' ',0));
      this->result.append(fixLength(qComb.value(2).toString(),30,' ',0));
      this->result.append(fixLength(cnv(qComb.value(3).toInt()),10,' ',1));
      this->result.append(fixLength(qComb.value(4).toString(),7,' ',1));
      this->result.append(fixLength(qComb.value(5).toString(),6,' ',1) + "\n");
   }   
   
   line80("-");
}

void Report::fullRep()
{
    DbConn* db = DbConn::Instance();

    stringstream ss;
    string name;
    ss << "Full " << this->start.toString("yyyy-MM-dd").latin1() << " - "<< this->stop.toString("yyyy-MM-dd").latin1() << " ";
    getline(ss, name);
    ss.clear();
    head(name);
   
    string sqlq = "SELECT r.id, TO_CHAR(r.ridedate,'Day') as weekday, EXTRACT(DAY FROM r.ridedate) AS ";
    sqlq += "day, TO_CHAR(r.ridedate, 'Month') AS month, EXTRACT(YEAR FROM r.ridedate) AS ";        
    sqlq += "year, f.name AS bike, t.name AS trail, r.type AS trainingtype, r.rating AS ";       
    sqlq += "rating, ROUND(CAST(t.distance AS NUMERIC),1) AS distance, ROUND(CAST(r.averagespeed ";
    sqlq += "AS NUMERIC),1), ROUND(CAST(r.maxspeed AS NUMERIC),1), ROUND(CAST(r.odobefore AS ";
    sqlq += "NUMERIC),1) AS odobefore, ROUND(CAST(r.odoafter AS NUMERIC),1) AS odobefore, ";
    sqlq += "ROUND(CAST((r.odoafter-r.odobefore) AS NUMERIC),1) AS ododiff, EXTRACT(EPOCH FROM ";
    sqlq += "r.trainingtime) "; 
    sqlq += "AS trainingtime, EXTRACT(EPOCH FROM r.elapsedtime), t.accumaltitude, r.maxtemp, r.mintemp "; 
    sqlq += "FROM ride r, bike b, frame f, trail t "; 
    sqlq += "WHERE r.bike=b.id AND b.frame=f.id AND r.trail=t.id AND r.ridedate>='";
    sqlq += this->start.toString("yyyy-MM-dd").latin1();
    sqlq += "' AND r.ridedate<='";
    sqlq += this->stop.toString("yyyy-MM-dd").latin1();
    sqlq += "' ORDER BY r.ridedate;"; 
      
    QSqlQuery qFull = db->get(sqlq);

    while (qFull.next()) {
        this->result.append("\n");
        line80("-");
        this->result.append(fixLength("Training date", 15, ' ', 0) + ": ");   
	this->result.append(qFull.value(1).toString() + " ");
	this->result.append(qFull.value(2).toString() + ". ");
	this->result.append(qFull.value(3).toString() + " ");
       	this->result.append(qFull.value(4).toString() + "\n");
        
   	this->result.append(fixLength("Bike", 15, ' ', 0) + ": ");   
       	this->result.append(qFull.value(5).toString() + "\n");

        this->result.append(fixLength("Trail", 15, ' ', 0) + ": ");   
       	this->result.append(qFull.value(6).toString() + "\n");

        this->result.append(fixLength("Training type", 15, ' ', 0) + ": ");   
       	this->result.append(qFull.value(7).toString() + "\n");

        this->result.append(fixLength("Rating", 15, ' ', 0) + ": ");   
       	this->result.append(qFull.value(8).toString() + "\n");

        this->result.append(fixLength("Distance", 15, ' ', 0) + ": ");   
       	this->result.append(qFull.value(9).toString() + " km\n");

        this->result.append(fixLength("Average Speed", 15, ' ', 0) + ": ");   
       	this->result.append(qFull.value(10).toString() + " km/h \tMaximum speed: ");
       	this->result.append(qFull.value(11).toString() + " km/h\n");

        this->result.append(fixLength("ODO values", 15, ' ', 0) + ": ");   
       	this->result.append(qFull.value(12).toString() + ", ");
       	this->result.append(qFull.value(13).toString() + " (diff: ");
       	this->result.append(qFull.value(14).toString() + "km)\n");

        this->result.append(fixLength("Exercise time", 15, ' ', 0) + ": ");   
       	this->result.append(cnv(qFull.value(15).toInt()) + " \tTotal time: ");
       	this->result.append(cnv(qFull.value(16).toInt()) + "\n");

        this->result.append(fixLength("Acc. Altitude", 15, ' ', 0) + ": ");   
       	this->result.append(qFull.value(17).toString() + " meter\n");

        this->result.append(fixLength("Temperature", 15, ' ', 0) + ": ");   
       	this->result.append(qFull.value(18).toString() + " / ");
       	this->result.append(qFull.value(19).toString() + " (max - min) deg. C\n");

        QString id(qFull.value(0).toString());

        sqlq = "(SELECT (SELECT COUNT(c2.id) FROM checkpoint c2 WHERE ";
	sqlq += "c2.distance<=c.distance AND c2.trail=c.trail) AS ordernum, c.location, ";
	sqlq += "c.distance, c.altitude::text, EXTRACT(EPOCH FROM rc.checktime) as checktime ";
	sqlq += "FROM ridecheckpoint rc, checkpoint c ";
	sqlq += "WHERE rc.ride=";
        sqlq += id.latin1();
	sqlq += " AND rc.checkpoint=c.id) UNION ";
	sqlq += "(SELECT (SELECT COUNT(c3.id)+1 FROM checkpoint c3 WHERE c3.trail=t.id) ";
	sqlq += "AS ordernum, '** End of trail' AS location, t.distance, '--' AS altitude, ";
	sqlq += "EXTRACT(EPOCH FROM r.trainingtime) as checktime ";
	sqlq += "FROM ride r, trail t WHERE r.id=";
	sqlq += id.latin1();
        sqlq += " AND r.trail=t.id) ";
	sqlq += " ORDER BY ordernum;";
       
        QSqlQuery qWP = db->get(sqlq);

        if (qWP.size() > 0) {
	   this->result.append("\nCheckpoint list:\n");

	   this->result.append(fixLength("",4,' ',1));			       
	   this->result.append(fixLength("Name",30,' ',0));
	   this->result.append(fixLength("Distance",10,' ',1));
	   this->result.append(fixLength("Altitude",10,' ',1));
	   this->result.append(fixLength("Time",10,' ',1) + "\n");
	   //this->result.append(fixLength("Avs.",6,' ',1) + "\n");
	   
	   line80("-");
	   while (qWP.next()) {
	      this->result.append(fixLength("",4,' ',1));			       
	      this->result.append(fixLength(qWP.value(1).toString(),30,' ',0));
	      this->result.append(fixLength(qWP.value(2).toString(),10,' ',1));
	      this->result.append(fixLength(qWP.value(3).toString(),10,' ',1));
	      this->result.append(fixLength(cnv(qWP.value(4).toInt()),10,' ',1) + "\n");
	   }
       	}  
    }
   
   sqlq = "SELECT COUNT(r.id), EXTRACT(EPOCH FROM SUM(r.trainingtime)) AS trainingtime, ";
   sqlq += "EXTRACT(EPOCH FROM SUM(r.elapsedtime)) AS elapsedtime, EXTRACT(EPOCH FROM ";
   sqlq += "MIN(r.trainingtime)) AS \"min trainingtime\", EXTRACT(EPOCH FROM ";
   sqlq += "MAX(r.trainingtime)) AS \"max trainingtime\", AVG(EXTRACT(EPOCH FROM ";
   sqlq += "r.trainingtime)) AS \"avg trainingtime\", SUM(t.distance) AS distance, ";
   sqlq += "SUM(r.odoafter-r.odobefore) AS \"ODO distance\", ";
   sqlq += "ROUND(CAST(SUM(r.odoafter-r.odobefore)/SUM((r.odoafter-r.odobefore)/r.averagespeed) ";
   sqlq += "AS NUMERIC),2) AS \"average speed\" ";
   sqlq += "FROM ride r, trail t ";
   sqlq += "WHERE r.trail=t.id AND r.ridedate>='";
   sqlq += this->start.toString("yyyy-MM-dd").latin1();
   sqlq += "' AND r.ridedate<='";
   sqlq += this->stop.toString("yyyy-MM-dd").latin1();
   sqlq += "';";

   this->result.append("\n");
   line80("-");
   
   QSqlQuery qFullSum = db->get(sqlq);
   
   if (qFullSum.next()) {
      this->result.append("Summary information:\n");
      
      this->result.append(fixLength("  Number of training entries", 30, ' ',0));
      this->result.append(" : ");	   
      this->result.append(qFullSum.value(0).toString() + "\n");
      
      this->result.append(fixLength("  Exercise time", 30, ' ',0));
      this->result.append(" : ");	   
      this->result.append(qFullSum.value(1).toString() + "\n");
      
      this->result.append(fixLength("  Elapsed time", 30, ' ',0));
      this->result.append(" : ");	   
      this->result.append(qFullSum.value(2).toString() + "\n");
      
      this->result.append(fixLength("  Min/Avg/Max Exercise time", 30, ' ',0));
      this->result.append(" : ");	   
      this->result.append(qFullSum.value(3).toString() + " / ");
      this->result.append(qFullSum.value(5).toString() + " / ");
      this->result.append(qFullSum.value(4).toString() + "\n");
      
      this->result.append(fixLength("  Total training distance", 30, ' ',0));
      this->result.append(" : ");	   
      this->result.append(qFullSum.value(6).toString() + " km\n");
      
      this->result.append(fixLength("  Total ODO distance", 30, ' ',0));
      this->result.append(" : ");	   
      this->result.append(qFullSum.value(7).toString() + " km\n");
      
      this->result.append(fixLength("  Average speed", 30, ' ',0));
      this->result.append(" : ");	   
      this->result.append(qFullSum.value(8).toString() + " km/h\n");
      
   }
   
   line80("=");
   
}
void Report::monthRep()
{
    stringstream ss;
    string name, yr;
    DbConn* db = DbConn::Instance();

    ss << "Month " << this->year << " ";
    getline(ss, name);
    head(name);
    ss.clear();
    ss << this->year;
    getline(ss,yr);
    this->result.append("Month\t\tDst\t\tTime\t\tAvs\t\tAvd\tCount\n");
    line80("-");
    string sqlq = "SELECT EXTRACT(MONTH FROM r.ridedate) AS month, TO_CHAR(r.ridedate, 'month')";
    sqlq += " AS monthname, ROUND(CAST(SUM(r.odoafter-r.odobefore) AS NUMERIC),1) AS ";
    sqlq += " distance, SUM (r.trainingtime) AS time,ROUND(CAST(SUM(r.odoafter-r.odobefore)/SUM";
    sqlq += "((r.odoafter-r.odobefore)/averagespeed) AS NUMERIC),1) AS averagespeed, ROUND";
    sqlq += "(CAST(AVG(r.odoafter-r.odobefore) AS NUMERIC),1) AS averagedistance, COUNT";
    sqlq += "(r.ridedate) FROM ride r WHERE EXTRACT(YEAR FROM r.ridedate)=";
    sqlq +=  yr;
    sqlq += " GROUP BY month, monthname ORDER BY month;";
    //cout << endl << result << endl << sqlq << endl;        
    //cout << endl << yr  << endl << sqlq << endl;        
    QSqlQuery qMonLi = db->get(sqlq);
    while (qMonLi.next()) {
	this->result.append(fixLength(qMonLi.value(1).toString(), 10, ' ', 0));
	this->result.append(fixLength(qMonLi.value(2).toString(), 10, ' ', 1));
	this->result.append(fixLength(qMonLi.value(3).toString(), 18, ' ', 1));
	this->result.append(fixLength(qMonLi.value(4).toString(), 13, ' ', 1));
	this->result.append(fixLength(qMonLi.value(5).toString(), 17, ' ', 1));
	this->result.append(fixLength(qMonLi.value(6).toString(), 7, ' ', 1) + "\n");
    }
    
    sqlq = "SELECT 'All' AS monthname, ROUND(CAST(SUM(r.odoafter-r.odobefore) AS ";
    sqlq += "NUMERIC),1) AS distance, SUM (EXTRACT(EPOCH FROM r.trainingtime)) AS time,";
    sqlq += "ROUND(CAST(SUM(r.odoafter-r.odobefore)/SUM((r.odoafter-r.odobefore)/averagespeed)";
    sqlq += " AS NUMERIC),1) AS averagespeed, ROUND(CAST(AVG(r.odoafter-r.odobefore) AS ";
    sqlq += "NUMERIC),1) AS averagedistance, COUNT(r.ridedate) FROM ride r WHERE ";
    sqlq += "EXTRACT(YEAR FROM r.ridedate)=";
    sqlq += yr;
    sqlq += ";";
    line80("-");
    //    cout << endl << sqlq << endl;
    QSqlQuery qMonSum = db->get(sqlq);
    while (qMonSum.next()) {
	this->result.append(fixLength("All", 10, ' ', 0));
	this->result.append(fixLength(qMonSum.value(1).toString(), 10, ' ', 1));
	this->result.append(fixLength(cnv(qMonSum.value(2).toInt()), 18, ' ', 1));
	this->result.append(fixLength(qMonSum.value(3).toString(), 13, ' ', 1));
	this->result.append(fixLength(qMonSum.value(4).toString(), 17, ' ', 1));
	this->result.append(fixLength(qMonSum.value(5).toString(), 7, ' ', 1) + "\n");
    }
    //    cout << endl << result << endl << endl;
}
void Report::summaryRep()
{

   stringstream ss;
   string name;
   
   string sqlq = "SELECT DISTINCT EXTRACT(YEAR FROM r.ridedate) AS year ";
   sqlq += "FROM ride r ORDER BY year;";

   DbConn* db = DbConn::Instance();
   QSqlQuery qSumYears = db->get(sqlq);
      
   while (qSumYears.next()) {
      QString yr(qSumYears.value(0).toString());
      ss << "Summary " << yr;     
      getline(ss, name);
      ss.clear();
      head(name);

//***************************************************************************
// Bike
//***************************************************************************
      
      this->result.append(fixLength("Bike",45,' ',FALSE));
      this->result.append(fixLength("Time",11,' ',TRUE));
      this->result.append(fixLength("Dst.",10,' ',TRUE));
      this->result.append(fixLength("Avs.",7,' ',TRUE));
      this->result.append(fixLength("Count",7,' ',TRUE) + "\n");
      
      line80("-");
            
      sqlq = "SELECT f.name, EXTRACT(EPOCH FROM SUM(r.trainingtime)) AS time, "; 
      sqlq += "ROUND(CAST(SUM(r.odoafter-r.odobefore) AS NUMERIC),1) AS distance, ROUND(CAST(SUM(r.odoafter-";
      sqlq += "r.odobefore)/SUM((r.odoafter-r.odobefore)/r.averagespeed)";
      sqlq += " AS NUMERIC),1) AS \"average speed\", COUNT(f.id) ";
      sqlq += "FROM frame f, bike b, ride r WHERE b.frame=f.id AND "; 
      sqlq += "r.bike=b.id AND EXTRACT(YEAR FROM r.ridedate)=";
      sqlq += yr.latin1();	 
      sqlq += " GROUP BY f.name ORDER BY f.name;";
      
      QSqlQuery qSumBike = db->get(sqlq);
      
      while (qSumBike.next()) {
	 this->result.append(fixLength(qSumBike.value(0).toString(),45,' ',FALSE));
	 this->result.append(fixLength(cnv(qSumBike.value(1).toInt()),11,' ',TRUE));
	 this->result.append(fixLength(qSumBike.value(2).toString(),10,' ',TRUE));
	 this->result.append(fixLength(qSumBike.value(3).toString(),7,' ',TRUE));
	 this->result.append(fixLength(qSumBike.value(4).toString(),7,' ',TRUE) + "\n");	   
      } 
      
      line80("-");
      
      sqlq = "SELECT EXTRACT(EPOCH FROM SUM(r.trainingtime)) AS time, ";
      sqlq += "ROUND(CAST(SUM(r.odoafter-r.odobefore) AS NUMERIC),1) AS distance, ROUND(CAST(SUM(r.odoafter-";
      sqlq += "r.odobefore)/SUM((r.odoafter-r.odobefore)/r.averagespeed)";
      sqlq += " AS NUMERIC),1) AS \"average speed\", COUNT(f.id) ";
      sqlq += "FROM frame f, bike b, ride r WHERE b.frame=f.id AND ";
      sqlq += "r.bike=b.id AND EXTRACT(YEAR FROM r.ridedate)=";
      sqlq += yr.latin1();
      sqlq += ";";
      
      QSqlQuery qSumBikeSum = db->get(sqlq);
      
      if (qSumBikeSum.next()) {	   
	 this->result.append(fixLength("Total(" + yr + ") : ",45,' ',TRUE));
	 this->result.append(fixLength(cnv(qSumBikeSum.value(0).toInt()),11,' ',TRUE));
	 this->result.append(fixLength(qSumBikeSum.value(1).toString(),10,' ',TRUE));
	 this->result.append(fixLength(qSumBikeSum.value(2).toString(),7,' ',TRUE));
	 this->result.append(fixLength(qSumBikeSum.value(3).toString(),7,' ',TRUE) + "\n");
      }
      
      line80("=");
      this->result.append("\n");
      
//***************************************************************************
// Training type
//***************************************************************************

      this->result.append(fixLength("Training type",45,' ',FALSE));
      this->result.append(fixLength("Time",11,' ',TRUE));
      this->result.append(fixLength("Dst.",10,' ',TRUE));
      this->result.append(fixLength("Avs.",7,' ',TRUE));
      this->result.append(fixLength("Count",7,' ',TRUE) + "\n");
      
      line80("-");
      
      sqlq = "SELECT r.type, EXTRACT(EPOCH FROM SUM(r.trainingtime)), SUM(r.odoafter-odobefore) AS ";
      sqlq += "distance, ROUND(CAST(SUM(r.odoafter-r.odobefore)/SUM((r.odoafter-r.odobefore)/";
      sqlq += "r.averagespeed) AS NUMERIC),2) AS \"average speed\", COUNT (r.id)";
      sqlq += " FROM ride r, trail t WHERE r.trail=t.id AND EXTRACT(YEAR FROM r.ridedate)=";
      sqlq += yr.latin1();
      sqlq += " GROUP BY r.type ORDER BY r.type;";
		      
      QSqlQuery qSumTraining = db->get(sqlq);
      
      while (qSumTraining.next()) {
	 this->result.append(fixLength(qSumTraining.value(0).toString(),45,' ',FALSE));
	 this->result.append(fixLength(cnv(qSumTraining.value(1).toInt()),11,' ',TRUE));
	 this->result.append(fixLength(qSumTraining.value(2).toString(),10,' ',TRUE));
	 this->result.append(fixLength(qSumTraining.value(3).toString(),7,' ',TRUE));
	 this->result.append(fixLength(qSumTraining.value(4).toString(),7,' ',TRUE) + "\n");
      }
            
      line80("-");
            
      sqlq = "SELECT EXTRACT(EPOCH FROM SUM(r.trainingtime)), SUM(r.odoafter-odobefore) AS ";
      sqlq += "distance, ROUND(CAST(SUM(r.odoafter-r.odobefore)/SUM((r.odoafter-r.odobefore)/";
      sqlq += "r.averagespeed) AS NUMERIC),2) AS \"average speed\", COUNT (r.id)";
      sqlq += " FROM ride r, trail t WHERE r.trail=t.id AND EXTRACT(YEAR FROM r.ridedate)=";
      sqlq += yr.latin1();
      sqlq += ";";
	      
      QSqlQuery qSumTrainingSum = db->get(sqlq);
      
      if (qSumTrainingSum.next()) {
	 this->result.append(fixLength("Total(" + yr + ") : ",45,' ',TRUE));
	 this->result.append(fixLength(cnv(qSumTrainingSum.value(0).toInt()),11,' ',TRUE));
	 this->result.append(fixLength(qSumTrainingSum.value(1).toString(),10,' ',TRUE));
	 this->result.append(fixLength(qSumTrainingSum.value(2).toString(),7,' ',TRUE));
	 this->result.append(fixLength(qSumTrainingSum.value(3).toString(),7,' ',TRUE) + "\n");
      }
            
      line80("=");
      this->result.append("\n");
      
//***************************************************************************
// Trail type
//***************************************************************************

      this->result.append(fixLength("Trail",45,' ',FALSE));
      this->result.append(fixLength("Time",11,' ',TRUE));
      this->result.append(fixLength("Dst.",10,' ',TRUE));
      this->result.append(fixLength("Avs.",7,' ',TRUE));
      this->result.append(fixLength("Count",7,' ',TRUE) + "\n");
      
      line80("-");
      
      sqlq = "SELECT t.name, EXTRACT(EPOCH FROM SUM(r.trainingtime)), SUM(r.odoafter-odobefore) AS ";
      sqlq += "distance, ROUND(CAST(SUM(r.odoafter-r.odobefore)/SUM((r.odoafter-r.odobefore)/";
      sqlq += "r.averagespeed) AS NUMERIC),2) AS \"average speed\", COUNT (r.id)";
      sqlq += " FROM ride r, trail t WHERE r.trail=t.id AND EXTRACT(YEAR FROM r.ridedate)=";
      sqlq += yr.latin1();
      sqlq += " GROUP BY t.name ORDER BY t.name;";
		      
      QSqlQuery qSumTrail = db->get(sqlq);
      
      while (qSumTrail.next()) {
	 this->result.append(fixLength(qSumTrail.value(0).toString(),45,' ',FALSE));
	 this->result.append(fixLength(cnv(qSumTrail.value(1).toInt()),11,' ',TRUE));
	 this->result.append(fixLength(qSumTrail.value(2).toString(),10,' ',TRUE));
	 this->result.append(fixLength(qSumTrail.value(3).toString(),7,' ',TRUE));
	 this->result.append(fixLength(qSumTrail.value(4).toString(),7,' ',TRUE) + "\n");
      }
            
      line80("-");
            
      sqlq = "SELECT EXTRACT(EPOCH FROM SUM(r.trainingtime)), SUM(r.odoafter-odobefore) AS ";
      sqlq += "distance, ROUND(CAST(SUM(r.odoafter-r.odobefore)/SUM((r.odoafter-r.odobefore)/";
      sqlq += "r.averagespeed) AS NUMERIC),2) AS \"average speed\", COUNT (r.id)";
      sqlq += " FROM ride r, trail t WHERE r.trail=t.id AND EXTRACT(YEAR FROM r.ridedate)=";
      sqlq += yr.latin1();
      sqlq += ";";
	      
      QSqlQuery qSumTrailSum = db->get(sqlq);
      
      if (qSumTrailSum.next()) {
	 this->result.append(fixLength("Total(" + yr + ") : ",45,' ',TRUE));
	 this->result.append(fixLength(cnv(qSumTrailSum.value(0).toInt()),11,' ',TRUE));
	 this->result.append(fixLength(qSumTrailSum.value(1).toString(),10,' ',TRUE));
	 this->result.append(fixLength(qSumTrailSum.value(2).toString(),7,' ',TRUE));
	 this->result.append(fixLength(qSumTrailSum.value(3).toString(),7,' ',TRUE) + "\n");
      }
            
      line80("=");
      this->result.append("\n");
      
//***************************************************************************
// Rating type
//***************************************************************************

      this->result.append(fixLength("Rating",45,' ',FALSE));
      this->result.append(fixLength("Time",11,' ',TRUE));
      this->result.append(fixLength("Dst.",10,' ',TRUE));
      this->result.append(fixLength("Avs.",7,' ',TRUE));
      this->result.append(fixLength("Count",7,' ',TRUE) + "\n");
      
      line80("-");
      
      sqlq = "SELECT r.rating, EXTRACT(EPOCH FROM SUM(r.trainingtime)), SUM(r.odoafter-odobefore) AS ";
      sqlq += "distance, ROUND(CAST(SUM(r.odoafter-r.odobefore)/SUM((r.odoafter-r.odobefore)/";
      sqlq += "r.averagespeed) AS NUMERIC),2) AS \"average speed\", COUNT (r.id)";
      sqlq += " FROM ride r, trail t WHERE r.trail=t.id AND EXTRACT(YEAR FROM r.ridedate)=";
      sqlq += yr.latin1();
      sqlq += " GROUP BY r.rating ORDER BY r.rating;";
		      
      QSqlQuery qSumRating = db->get(sqlq);
      
      while (qSumRating.next()) {
	 this->result.append(fixLength(qSumRating.value(0).toString(),45,' ',FALSE));
	 this->result.append(fixLength(cnv(qSumRating.value(1).toInt()),11,' ',TRUE));
	 this->result.append(fixLength(qSumRating.value(2).toString(),10,' ',TRUE));
	 this->result.append(fixLength(qSumRating.value(3).toString(),7,' ',TRUE));
	 this->result.append(fixLength(qSumRating.value(4).toString(),7,' ',TRUE) + "\n");
      }
            
      line80("-");
            
      sqlq = "SELECT EXTRACT(EPOCH FROM SUM(r.trainingtime)), SUM(r.odoafter-odobefore) AS ";
      sqlq += "distance, ROUND(CAST(SUM(r.odoafter-r.odobefore)/SUM((r.odoafter-r.odobefore)/";
      sqlq += "r.averagespeed) AS NUMERIC),2) AS \"average speed\", COUNT (r.id)";
      sqlq += " FROM ride r, trail t WHERE r.trail=t.id AND EXTRACT(YEAR FROM r.ridedate)=";
      sqlq += yr.latin1();
      sqlq += ";";
	      
      QSqlQuery qSumRatingSum = db->get(sqlq);
      
      if (qSumRatingSum.next()) {
	 this->result.append(fixLength("Total(" + yr + ") : ",45,' ',TRUE));
	 this->result.append(fixLength(cnv(qSumRatingSum.value(0).toInt()),11,' ',TRUE));
	 this->result.append(fixLength(qSumRatingSum.value(1).toString(),10,' ',TRUE));
	 this->result.append(fixLength(qSumRatingSum.value(2).toString(),7,' ',TRUE));
	 this->result.append(fixLength(qSumRatingSum.value(3).toString(),7,' ',TRUE) + "\n");
      }
            
      line80("=");
      this->result.append("\n");
      
   }

//***************************************************************************
// Grand Total!!!
//***************************************************************************
 
   
   ss << "Summary for all years";     
   getline(ss, name);
   ss.clear();
   head(name);

//***************************************************************************
// Bike GT
//***************************************************************************
      
   this->result.append(fixLength("Bike",45,' ',FALSE));
   this->result.append(fixLength("Time",11,' ',TRUE));
   this->result.append(fixLength("Dst.",10,' ',TRUE));
   this->result.append(fixLength("Avs.",7,' ',TRUE));
   this->result.append(fixLength("Count",7,' ',TRUE) + "\n");
      
   line80("-");
   
   sqlq = "SELECT f.name, EXTRACT(EPOCH FROM SUM(r.trainingtime)) AS time, "; 
   sqlq += "ROUND(CAST(SUM(r.odoafter-r.odobefore) AS NUMERIC),1) AS distance, ROUND(CAST(SUM(r.odoafter-";
   sqlq += "r.odobefore)/SUM((r.odoafter-r.odobefore)/r.averagespeed)";
   sqlq += " AS NUMERIC),1) AS \"average speed\", COUNT(f.id) ";
   sqlq += "FROM frame f, bike b, ride r WHERE b.frame=f.id AND "; 
   sqlq += "r.bike=b.id";
   sqlq += " GROUP BY f.name ORDER BY f.name;";
      
   QSqlQuery qSumBike = db->get(sqlq);
      
   while (qSumBike.next()) {
      this->result.append(fixLength(qSumBike.value(0).toString(),45,' ',FALSE));
      this->result.append(fixLength(cnv(qSumBike.value(1).toInt()),11,' ',TRUE));
      this->result.append(fixLength(qSumBike.value(2).toString(),10,' ',TRUE));
      this->result.append(fixLength(qSumBike.value(3).toString(),7,' ',TRUE));
      this->result.append(fixLength(qSumBike.value(4).toString(),7,' ',TRUE) + "\n");	   
   } 
      
   line80("-");
      
   sqlq = "SELECT EXTRACT(EPOCH FROM SUM(r.trainingtime)) AS time, ";
   sqlq += "ROUND(CAST(SUM(r.odoafter-r.odobefore) AS NUMERIC),1) AS distance, ROUND(CAST(SUM(r.odoafter-";
   sqlq += "r.odobefore)/SUM((r.odoafter-r.odobefore)/r.averagespeed)";
   sqlq += " AS NUMERIC),1) AS \"average speed\", COUNT(f.id) ";
   sqlq += "FROM frame f, bike b, ride r WHERE b.frame=f.id AND ";
   sqlq += "r.bike=b.id;";
   
   QSqlQuery qSumBikeSum = db->get(sqlq);
      
   if (qSumBikeSum.next()) {	   
      this->result.append(fixLength("Grand total : ",45,' ',TRUE));
      this->result.append(fixLength(cnv(qSumBikeSum.value(0).toInt()),11,' ',TRUE));
      this->result.append(fixLength(qSumBikeSum.value(1).toString(),10,' ',TRUE));
      this->result.append(fixLength(qSumBikeSum.value(2).toString(),7,' ',TRUE));
      this->result.append(fixLength(qSumBikeSum.value(3).toString(),7,' ',TRUE) + "\n");
   }
   
   line80("=");
   this->result.append("\n");
      
//***************************************************************************
// Training type GT
//***************************************************************************
   
   this->result.append(fixLength("Training type",45,' ',FALSE));
   this->result.append(fixLength("Time",11,' ',TRUE));
   this->result.append(fixLength("Dst.",10,' ',TRUE));
   this->result.append(fixLength("Avs.",7,' ',TRUE));
   this->result.append(fixLength("Count",7,' ',TRUE) + "\n");
   
   line80("-");
   
   sqlq = "SELECT r.type, EXTRACT(EPOCH FROM SUM(r.trainingtime)), SUM(r.odoafter-odobefore) AS ";
   sqlq += "distance, ROUND(CAST(SUM(r.odoafter-r.odobefore)/SUM((r.odoafter-r.odobefore)/";
   sqlq += "r.averagespeed) AS NUMERIC),2) AS \"average speed\", COUNT (r.id)";
   sqlq += " FROM ride r, trail t WHERE r.trail=t.id";
   sqlq += " GROUP BY r.type ORDER BY r.type;";
   
   QSqlQuery qSumTraining = db->get(sqlq);
   
   while (qSumTraining.next()) {
      this->result.append(fixLength(qSumTraining.value(0).toString(),45,' ',FALSE));
      this->result.append(fixLength(cnv(qSumTraining.value(1).toInt()),11,' ',TRUE));
      this->result.append(fixLength(qSumTraining.value(2).toString(),10,' ',TRUE));
      this->result.append(fixLength(qSumTraining.value(3).toString(),7,' ',TRUE));
      this->result.append(fixLength(qSumTraining.value(4).toString(),7,' ',TRUE) + "\n");
   }
   
   line80("-");
            
   sqlq = "SELECT EXTRACT(EPOCH FROM SUM(r.trainingtime)), SUM(r.odoafter-odobefore) AS ";
   sqlq += "distance, ROUND(CAST(SUM(r.odoafter-r.odobefore)/SUM((r.odoafter-r.odobefore)/";
   sqlq += "r.averagespeed) AS NUMERIC),2) AS \"average speed\", COUNT (r.id)";
   sqlq += " FROM ride r, trail t WHERE r.trail=t.id;";
	      
   QSqlQuery qSumTrainingSum = db->get(sqlq);
   
   if (qSumTrainingSum.next()) {
      this->result.append(fixLength("Grand total : ",45,' ',TRUE));
      this->result.append(fixLength(cnv(qSumTrainingSum.value(0).toInt()),11,' ',TRUE));
      this->result.append(fixLength(qSumTrainingSum.value(1).toString(),10,' ',TRUE));
      this->result.append(fixLength(qSumTrainingSum.value(2).toString(),7,' ',TRUE));
      this->result.append(fixLength(qSumTrainingSum.value(3).toString(),7,' ',TRUE) + "\n");
   }
   
   line80("=");
   this->result.append("\n");
      
//***************************************************************************
// Trail type GT
//***************************************************************************

   this->result.append(fixLength("Trail",45,' ',FALSE));
   this->result.append(fixLength("Time",11,' ',TRUE));
   this->result.append(fixLength("Dst.",10,' ',TRUE));
   this->result.append(fixLength("Avs.",7,' ',TRUE));
   this->result.append(fixLength("Count",7,' ',TRUE) + "\n");
      
   line80("-");
      
   sqlq = "SELECT t.name, EXTRACT(EPOCH FROM SUM(r.trainingtime)), SUM(r.odoafter-odobefore) AS ";
   sqlq += "distance, ROUND(CAST(SUM(r.odoafter-r.odobefore)/SUM((r.odoafter-r.odobefore)/";
   sqlq += "r.averagespeed) AS NUMERIC),2) AS \"average speed\", COUNT (r.id)";
   sqlq += " FROM ride r, trail t WHERE r.trail=t.id";
   sqlq += " GROUP BY t.name ORDER BY t.name;";
   
   QSqlQuery qSumTrail = db->get(sqlq);
   
   while (qSumTrail.next()) {
      this->result.append(fixLength(qSumTrail.value(0).toString(),45,' ',FALSE));
      this->result.append(fixLength(cnv(qSumTrail.value(1).toInt()),11,' ',TRUE));
      this->result.append(fixLength(qSumTrail.value(2).toString(),10,' ',TRUE));
      this->result.append(fixLength(qSumTrail.value(3).toString(),7,' ',TRUE));
      this->result.append(fixLength(qSumTrail.value(4).toString(),7,' ',TRUE) + "\n");
   }
   
   line80("-");
            
   sqlq = "SELECT EXTRACT(EPOCH FROM SUM(r.trainingtime)), SUM(r.odoafter-odobefore) AS ";
   sqlq += "distance, ROUND(CAST(SUM(r.odoafter-r.odobefore)/SUM((r.odoafter-r.odobefore)/";
   sqlq += "r.averagespeed) AS NUMERIC),2) AS \"average speed\", COUNT (r.id)";
   sqlq += " FROM ride r, trail t WHERE r.trail=t.id;";
   
   QSqlQuery qSumTrailSum = db->get(sqlq);
      
   if (qSumTrailSum.next()) {
      this->result.append(fixLength("Grand total : ",45,' ',TRUE));
      this->result.append(fixLength(cnv(qSumTrailSum.value(0).toInt()),11,' ',TRUE));
      this->result.append(fixLength(qSumTrailSum.value(1).toString(),10,' ',TRUE));
      this->result.append(fixLength(qSumTrailSum.value(2).toString(),7,' ',TRUE));
      this->result.append(fixLength(qSumTrailSum.value(3).toString(),7,' ',TRUE) + "\n");
   }
   
   line80("=");
   this->result.append("\n");
      
//***************************************************************************
// Rating type GT
//***************************************************************************

   this->result.append(fixLength("Rating",45,' ',FALSE));
   this->result.append(fixLength("Time",11,' ',TRUE));
   this->result.append(fixLength("Dst.",10,' ',TRUE));
   this->result.append(fixLength("Avs.",7,' ',TRUE));
   this->result.append(fixLength("Count",7,' ',TRUE) + "\n");
      
   line80("-");
      
   sqlq = "SELECT r.rating, EXTRACT(EPOCH FROM SUM(r.trainingtime)), SUM(r.odoafter-odobefore) AS ";
   sqlq += "distance, ROUND(CAST(SUM(r.odoafter-r.odobefore)/SUM((r.odoafter-r.odobefore)/";
   sqlq += "r.averagespeed) AS NUMERIC),2) AS \"average speed\", COUNT (r.id)";
   sqlq += " FROM ride r, trail t WHERE r.trail=t.id";
   sqlq += " GROUP BY r.rating ORDER BY r.rating;";
		      
   QSqlQuery qSumRating = db->get(sqlq);
   
   while (qSumRating.next()) {
      this->result.append(fixLength(qSumRating.value(0).toString(),45,' ',FALSE));
      this->result.append(fixLength(cnv(qSumRating.value(1).toInt()),11,' ',TRUE));
      this->result.append(fixLength(qSumRating.value(2).toString(),10,' ',TRUE));
      this->result.append(fixLength(qSumRating.value(3).toString(),7,' ',TRUE));
      this->result.append(fixLength(qSumRating.value(4).toString(),7,' ',TRUE) + "\n");
   }
   
   line80("-");
            
   sqlq = "SELECT EXTRACT(EPOCH FROM SUM(r.trainingtime)), SUM(r.odoafter-odobefore) AS ";
   sqlq += "distance, ROUND(CAST(SUM(r.odoafter-r.odobefore)/SUM((r.odoafter-r.odobefore)/";
   sqlq += "r.averagespeed) AS NUMERIC),2) AS \"average speed\", COUNT (r.id)";
   sqlq += " FROM ride r, trail t WHERE r.trail=t.id;";
   
   QSqlQuery qSumRatingSum = db->get(sqlq);
      
   if (qSumRatingSum.next()) {
      this->result.append(fixLength("Grand total : ",45,' ',TRUE));
      this->result.append(fixLength(cnv(qSumRatingSum.value(0).toInt()),11,' ',TRUE));
      this->result.append(fixLength(qSumRatingSum.value(1).toString(),10,' ',TRUE));
      this->result.append(fixLength(qSumRatingSum.value(2).toString(),7,' ',TRUE));
      this->result.append(fixLength(qSumRatingSum.value(3).toString(),7,' ',TRUE) + "\n");
   }
            
   line80("=");
   this->result.append("\n");
}

void Report::tireRep()
{
    head("Tire");
    string sqlq = "SELECT t.id, t.name, t.brand, t.model FROM tire t ORDER BY t.brand;";
    DbConn* db = DbConn::Instance();
    QSqlQuery qTire = db->get(sqlq);
    while (qTire.next()) {
	QString id(qTire.value(0).toString());
	this->result.append("Tire name\t: " + qTire.value(1).toString() + "\n");
	//     to be added l8r
	// this->result.append("Created\t: " + );
	this->result.append("Tire type\t: " + qTire.value(2).toString() 
			    + " " + qTire.value(3).toString());
	this->result.append("\n\nDate\t\tBike\t\t\tTime\t\tODO distance\tDistance\n");
	line80("-");
	sqlq = "SELECT r.ridedate, f.name AS bike, EXTRACT(EPOCH FROM r.trainingtime) ";
	sqlq += "AS time,tr.distance, ROUND(CAST(r.odoafter-r.odobefore AS NUMERIC), 1)";
	sqlq +=" AS ododistance, (CASE WHEN b.backtire=";
	sqlq += id.latin1();
	sqlq += " THEN 'B' ELSE 'F' END) FROM ride r, bike b, frame f, tire t, trail tr WHERE";
	sqlq += " b.id=r.bike AND f.id=b.frame AND (t.id=b.fronttire OR t.id=b.backtire)";
	sqlq += " AND t.id=";
	sqlq += id.latin1();
	sqlq += " AND r.ridedate>'";
	sqlq += this->start.toString("yyyy-MM-dd").latin1();
	sqlq += "' AND r.ridedate<'";
	sqlq += this->stop.toString().latin1();
	sqlq += "' AND r.trail=tr.id ORDER BY r.ridedate;";
	QSqlQuery qUseTire = db->get(sqlq);
	while(qUseTire.next()) {
	    this->result.append(fixLength(qUseTire.value(5).toString(), 2, ' ', 0));
	    this->result.append(fixLength(qUseTire.value(0).toString(), 14, ' ', 0));
	    this->result.append(fixLength(qUseTire.value(1).toString(), 15, ' ', 0));
	    this->result.append(fixLength(cnv(qUseTire.value(2).toInt()), 15, ' ', 1));
	    this->result.append(fixLength(qUseTire.value(4).toString(), 17, ' ', 1));
	    this->result.append(fixLength(qUseTire.value(3).toString(), 15, ' ', 1) + "\n");
	}
	line80("-");
	sqlq = "(SELECT 'Used as front tire' AS use, SUM(EXTRACT(EPOCH FROM r.trainingtime))"; 
	sqlq += " AS time, SUM(r.odoafter-r.odobefore) AS ododistance,SUM(tr.distance) FROM ride r, bike b, frame f,";
	sqlq += "tire t, trail tr WHERE b.id=r.bike AND f.id=b.frame AND t.id=b.fronttire AND t.id=";
	sqlq += id.latin1();
	sqlq += " AND r.ridedate>'";
	sqlq += this->start.toString("yyyy-MM-dd").latin1();
	sqlq += "' AND r.ridedate<'";
	sqlq += this->stop.toString("yyyy-MM-dd").latin1();
	sqlq += "' AND r.trail=tr.id) UNION (SELECT 'Used as back tire', SUM(EXTRACT(EPOCH";
	sqlq += " FROM r.trainingtime)) AS time,";
	sqlq += "ROUND(CAST(SUM(r.odoafter-r.odobefore) AS NUMERIC), 1) AS ododistance,";
	sqlq += " ROUND(CAST(SUM(tr.distance) AS NUMERIC), 1)  FROM ride r, bike b, frame f, tire t ";
	sqlq += ",trail tr WHERE b.id=r.bike AND f.id=b.frame AND t.id=b.backtire AND t.id=";
	sqlq += id.latin1();
	sqlq += " AND r.ridedate>'";
	sqlq += this->start.toString("yyyy-MM-dd").latin1();
	sqlq += "' AND r.ridedate<'";
	sqlq += this->stop.toString("yyyy-MM-dd").latin1();
	sqlq += "' AND r.trail=tr.id) ORDER BY use DESC;";
	// 	cout << sqlq;
	// 	exit(0);
	QSqlQuery qTirePos = db->get(sqlq);
	// cout << endl << endl << endl << sqlq << endl<< endl<< endl;
	// exit(0);
	while(qTirePos.next()) {
	    result.append(fixLength(qTirePos.value(0).toString(), 32, ' ', 0));
	    result.append(fixLength(cnv(qTirePos.value(1).toInt()), 14, ' ', 1));
	    result.append(fixLength(qTirePos.value(2).toString(), 17, ' ', 1));
	    result.append(fixLength(qTirePos.value(3).toString(), 15, ' ', 1) + "\n");
	}
	line80("=");
	this->result.append("\n\n");
    }
    //    cout << this->result;
}
void Report::trailRep()
{
    head("Trail");

    string sqlq = "SELECT t.id, t.name, t.mapreference, t.distance, t.maxaltitude,"; 
    sqlq += "t.minaltitude, t.accumaltitude, t.skilllevel, t.description, COUNT(r.trail)";
    sqlq += "AS refcount FROM trail t, ride r WHERE r.trail=t.id GROUP BY t.id, t.name,";
    sqlq += "t.mapreference, t.distance, t.maxaltitude, t.minaltitude, t.accumaltitude,";
    sqlq += "t.skilllevel, t.description ORDER BY t.name;";

    DbConn* db = DbConn::Instance();
    QSqlQuery qTrail = db->get(sqlq);

    line80("-");

    while(qTrail.next()) {
	// Get the data on trail one:
	QString id(qTrail.value(0).toString());
	this->result.append("\nTrail\t\t: " + qTrail.value(1).toString() + "\n");
	this->result.append("Map ref.\t: " + qTrail.value(2).toString() + "\n");
	this->result.append("Length\t\t: " + qTrail.value(3).toString() + "\n");
	this->result.append("Altitude\t: " + qTrail.value(5).toString() + "/" + 
			    qTrail.value(4).toString() + "/" + qTrail.value(6).toString()
			    + " meters (min/max/accumulated)" + "\n"); 
	this->result.append("Ref. count.\t: " + qTrail.value(9).toString() + "\n");
	// And on to the checkpoints!
	sqlq = "SELECT cp.location, cp.distance, cp.altitude ";
	sqlq += "FROM checkpoint cp WHERE cp.trail=";
	sqlq += id.latin1();
	sqlq += "ORDER BY cp.distance;";
	QSqlQuery qChPo = db->get(sqlq);
	this->result.append("\nCheckpoint list:\n\tName\t\t\t\tDistance\tAltitude");
	this->result.append("\n\t----------------------------------------------------------\n");
	while(qChPo.next()) {
	    this->result.append("\t" + fixLength(qChPo.value(0).toString(), 20, ' ', 0));
	    this->result.append("\t" + fixLength(qChPo.value(1).toString(), 15, ' ', 1));
	    this->result.append("\t" + fixLength(qChPo.value(2).toString(), 15, ' ', 1) + "\n");
	}
	this->result.append("\n\n" + qTrail.value(8).toString() + "\n\n");
	line80("-");
	this->result.append("\n");
    
    }
    //        cout << this->result;

}
void Report::weekRep()
{
    stringstream ss;
    string name, yr;
    ss << "Weekly " << this->year << " ";
    getline(ss, name);
    ss.clear();
    head(name);
    ss << this->year;
    getline(ss,yr);
 
    string sqlq = "SELECT EXTRACT(WEEK FROM r.ridedate) AS week, ";
    sqlq += "ROUND(CAST(SUM(r.odoafter-r.odobefore) AS NUMERIC),1) ";
    sqlq += "AS distance, SUM (r.trainingtime) AS time, ";
    sqlq += "ROUND(CAST(SUM(r.odoafter-r.odobefore)/SUM((";
    sqlq += "r.odoafter-r.odobefore)/averagespeed)AS NUMERIC),1) "; 
    sqlq += "AS averagespeed, ROUND(CAST(AVG(r.odoafter-r.odobefore) AS ";
    sqlq += "NUMERIC),1) AS averagedistance, COUNT(r.ridedate) FROM ride r ";
    sqlq += "WHERE EXTRACT(YEAR FROM r.ridedate)=";
    sqlq += yr; 
    sqlq += "GROUP BY week ORDER BY week;";
         
    DbConn* db = DbConn::Instance();
    QSqlQuery qWeek = db->get(sqlq);
  
    this->result.append(fixLength("Week range",14,' ',FALSE));
    this->result.append(fixLength("Distance",14,' ',TRUE));
    this->result.append(fixLength("Time",14,' ',TRUE));
    this->result.append(fixLength("Avg. speed",14,' ',TRUE));
    this->result.append(fixLength("Avg dst.",14,' ',TRUE));
    this->result.append(fixLength("Count",9,' ',TRUE) + "\n");

    line80("-");
   
    while (qWeek.next()) {
	this->result.append(fixLength(fixLength("    " + qWeek.value(0).toString(),6,' ',TRUE),14,' ',FALSE));
	this->result.append(fixLength(cnv(qWeek.value(1).toInt()),14,' ',TRUE));
	this->result.append(fixLength(cnv(qWeek.value(2).toInt()),14,' ',TRUE));
	this->result.append(fixLength(qWeek.value(3).toString(),14,' ',TRUE));
	this->result.append(fixLength(qWeek.value(4).toString(),14,' ',TRUE));
	this->result.append(fixLength(qWeek.value(5).toString(),7,' ',TRUE) + "  \n");
    } 
    
    line80("-");
  
    sqlq = "SELECT ROUND(CAST(SUM(r.odoafter-r.odobefore) AS NUMERIC),1) ";
    sqlq += "AS distance, SUM (r.trainingtime) AS time, ";
    sqlq += "ROUND(CAST(SUM(r.odoafter-r.odobefore)/SUM((";
    sqlq += "r.odoafter-r.odobefore)/averagespeed)AS NUMERIC),1) "; 
    sqlq += "AS averagespeed, ROUND(CAST(AVG(r.odoafter-r.odobefore) AS ";
    sqlq += "NUMERIC),1) AS averagedistance, COUNT(r.ridedate) FROM ride r ";
    sqlq += "WHERE EXTRACT(YEAR FROM r.ridedate)=";
    sqlq += yr; 
    sqlq += ";";
         
    QSqlQuery qWeekSum = db->get(sqlq);
  
    if (qWeekSum.next()) {
	this->result.append(fixLength("   All",14,' ',FALSE));
	this->result.append(fixLength(cnv(qWeekSum.value(0).toInt()),14,' ',TRUE));
	this->result.append(fixLength(cnv(qWeekSum.value(1).toInt()),14,' ',TRUE));
	this->result.append(fixLength(qWeekSum.value(2).toString(),14,' ',TRUE));
	this->result.append(fixLength(qWeekSum.value(3).toString(),14,' ',TRUE));
	this->result.append(fixLength(qWeekSum.value(4).toString(),7,' ',TRUE) + "  \n");
    }  
}
void Report::weekdayRep()
{
    stringstream ss;
    string name, yr;
    ss << "Weekday " << this->start.toString("yyyy-MM-dd").latin1() << " - "<< this->stop.toString("yyyy-MM-dd").latin1() << " ";
    getline(ss, name);
    ss.clear();
    head(name);
    
    string sqlq = "SELECT CASE WHEN (SELECT weekstarts FROM dateformat)='monday' ";
    sqlq += " AND EXTRACT(DOW FROM r.ridedate)=0 THEN 7 ELSE EXTRACT ";
    sqlq += "(DOW FROM r.ridedate) END AS \"day of week\", TO_CHAR ";
    sqlq += " (r.ridedate, 'Day') AS weekday, EXTRACT(EPOCH FROM ";
    sqlq += "SUM(r.trainingtime)) AS trainingtime, EXTRACT(EPOCH FROM ";
    sqlq += "SUM(r.elapsedtime)) AS totaltime, ROUND(CAST(SUM(t.distance) AS NUMERIC)";
    sqlq += ",1) AS distance, ROUND(CAST(SUM(r.odoafter-r.odobefore) AS NUMERIC),1) ";
    sqlq += "AS ODOdist, ROUND(CAST(SUM(t.accumaltitude) AS NUMERIC),1) ";
    sqlq += "AS \"acc. alt.\", COUNT(r.ridedate) ";
    sqlq += "FROM ride r, trail t ";
    sqlq += "WHERE r.ridedate>='";
    sqlq += this->start.toString("yyyy-MM-dd").latin1();
    sqlq += "' AND r.ridedate<='";
    sqlq += this->stop.toString("yyyy-MM-dd").latin1();
    sqlq += "' AND ";
    sqlq += "r.trail=t.id ";
    sqlq += "GROUP BY \"day of week\", weekday ";
    sqlq += "ORDER BY \"day of week\"; ";
    
    DbConn* db = DbConn::Instance();
    QSqlQuery qWeekday = db->get(sqlq);
    
    this->result.append(fixLength("Weekday",9,' ',FALSE));
    this->result.append(fixLength("Training time",16,' ',TRUE));
    this->result.append(fixLength("Total time",13,' ',TRUE));
    this->result.append(fixLength("Distance",11,' ',TRUE));
    this->result.append(fixLength("ODO dst.",11,' ',TRUE));
    this->result.append(fixLength("Acc. alt.",12,' ',TRUE));
    this->result.append(fixLength("Count",7,' ',TRUE) + "\n");

    line80("-");
   
    while (qWeekday.next()) {
        this->result.append(fixLength(qWeekday.value(1).toString(),9,' ',FALSE));
        this->result.append(fixLength(cnv(qWeekday.value(2).toInt()),16,' ',TRUE));
        this->result.append(fixLength(cnv(qWeekday.value(3).toInt()),13,' ',TRUE));
        this->result.append(fixLength(qWeekday.value(4).toString(),11,' ',TRUE));
        this->result.append(fixLength(qWeekday.value(5).toString(),11,' ',TRUE));
        this->result.append(fixLength(qWeekday.value(6).toString(),12,' ',TRUE));
        this->result.append(fixLength(qWeekday.value(7).toString(),7,' ',TRUE) + "\n");
    } 
   
    line80("-");
    
    sqlq = "SELECT EXTRACT(EPOCH FROM SUM(r.trainingtime)) AS trainingtime, ";
    sqlq += "EXTRACT(EPOCH FROM SUM(r.elapsedtime)) AS totaltime, ";
    sqlq += "ROUND(CAST(SUM(t.distance) AS NUMERIC),1) AS distance, ";
    sqlq += "ROUND(CAST(SUM(r.odoafter-r.odobefore) AS NUMERIC),1) AS ODOdist, ";
    sqlq += "ROUND(CAST(SUM(t.accumaltitude) AS NUMERIC),1) AS \"acc. alt.\", ";
    sqlq += "COUNT(r.ridedate) ";
    sqlq += "FROM ride r, trail t ";
    sqlq += "WHERE r.ridedate>='";
    sqlq += this->start.toString("yyyy-MM-dd").latin1();
    sqlq +=  "' AND r.ridedate<='";
    sqlq += this->stop.toString("yyyy-MM-dd").latin1();
    sqlq += "' AND r.trail=t.id;";
    
    QSqlQuery qWeekdaySum = db->get(sqlq);
     
    if (qWeekdaySum.next()) { 
	this->result.append(fixLength("",9,' ',FALSE));
	this->result.append(fixLength(cnv(qWeekdaySum.value(0).toInt()),16,' ',TRUE));
	this->result.append(fixLength(cnv(qWeekdaySum.value(1).toInt()),13,' ',TRUE));
	this->result.append(fixLength(qWeekdaySum.value(2).toString(),11,' ',TRUE));
	this->result.append(fixLength(qWeekdaySum.value(3).toString(),11,' ',TRUE));
	this->result.append(fixLength(qWeekdaySum.value(4).toString(),12,' ',TRUE));
	this->result.append(fixLength(qWeekdaySum.value(5).toString(),7,' ',TRUE) + "\n");
    }
   
    line80("=");
    //    cout << this->result;
}
void Report::wheelRep()
{

    head(" Wheel ");
    string sqlq = "SELECT w.id, w.name, w.brand, w.model, w.type FROM wheel w ORDER BY w.brand;";
    DbConn* db = DbConn::Instance();
    QSqlQuery qWheel = db->get(sqlq);
    while (qWheel.next()) {
	QString id(qWheel.value(0).toString());
	this->result.append("Wheel name\t: " + qWheel.value(1).toString() + "\n");
	//     to be added l8r
	// this->result.append("Created\t: " + );
	this->result.append("Wheel type\t: " + qWheel.value(2).toString() 
			    + " " + qWheel.value(3).toString());
	this->result.append("\n\nDate\t\tBike\t\t\tTime\t\tODO distance\tDistance\n");
	line80("-");
	sqlq = "SELECT r.ridedate AS date, f.name AS bike, EXTRACT(EPOCH FROM r.trainingtime) AS";
	sqlq += " time, t.distance,ROUND(CAST(r.odoafter-r.odobefore AS NUMERIC),1) AS";
	sqlq +=" ododistance FROM ride r, bike b, frame f, wheel w, trail t ";
	sqlq += "WHERE b.id=r.bike AND f.id=b.frame AND (w.id=b.frontwheel OR";
	sqlq += " w.id=b.backwheel) AND w.id=";
	sqlq += id.latin1();
	sqlq += " AND r.ridedate>'";
	sqlq += this->start.toString("yyyy-MM-dd").latin1();
	sqlq += "' AND r.ridedate<'";
	sqlq += this->stop.toString().latin1();
	sqlq += "' AND r.trail=t.id ORDER BY r.ridedate;";
	//	cerr << endl << sqlq << endl;
	QSqlQuery qUseTire = db->get(sqlq);
	while(qUseTire.next()) {
	    this->result.append(fixLength(qUseTire.value(0).toString(), 14, ' ', 0));
	    this->result.append(fixLength(qUseTire.value(1).toString(), 15, ' ', 0));
	    this->result.append(fixLength(cnv(qUseTire.value(2).toInt()), 15, ' ', 1));
	    this->result.append(fixLength(qUseTire.value(4).toString(), 17, ' ', 1));
	    this->result.append(fixLength(qUseTire.value(3).toString(), 15, ' ', 1) + "\n");
	}
	line80("-");
	sqlq = "SELECT SUM(EXTRACT(EPOCH FROM r.trainingtime)) as time, "; 
	sqlq += "SUM(r.odoafter-r.odobefore) AS ododistance, SUM(t.distance) AS distance ";
	sqlq += "FROM ride r, bike b, frame f, wheel w, trail t WHERE b.id=r.bike AND ";
	sqlq += "f.id=b.frame AND (w.id=b.backwheel OR w.id=b.frontwheel) AND w.id=";
	sqlq += id.latin1();
	sqlq += " AND r.trail=t.id;";

	//	 	cout << sqlq;
	// 	exit(0);
	QSqlQuery qWheelSum = db->get(sqlq);
	// cout << endl << endl << endl << sqlq << endl<< endl<< endl;
	// exit(0);
	while(qWheelSum.next()) {
	    result.append(fixLength("Total:", 32, ' ', 1));
	    result.append(fixLength(cnv(qWheelSum.value(0).toInt()), 12, ' ', 1));
	    result.append(fixLength(qWheelSum.value(1).toString(), 17, ' ', 1));
	    result.append(fixLength(qWheelSum.value(2).toString(), 15, ' ', 1) + "\n");
	}
	line80("=");
	this->result.append("\n\n");
    }
    //    cout << this->result;


}
void Report::yearRep()
{
    stringstream ss;
    string name, yr;
    int numOfYears = 0;
    ss << " Years " << this->start.year();
    getline(ss, name);
    ss.clear();
    head(name);
    ss << this->year;
    getline(ss,yr);
    ss.clear();

    string yearList[5];
    yearList[0] = yr;
   
    DbConn* db = DbConn::Instance();
    
   
       //    this->year = this->start.year();

    this->result.append(fixLength("Year", 7, ' ', 0));
    this->result.append(fixLength("Training time", 15, ' ', 1));
    this->result.append(fixLength("Total time", 12, ' ', 1));
    this->result.append(fixLength("Distance", 12, ' ', 1));
    this->result.append(fixLength("ODO dst.", 12, ' ', 1));
    this->result.append(fixLength("Acc. alt.", 12, ' ', 1));
    this->result.append(fixLength("Count", 10, ' ', 1) + "\n");

    line80("-");
   
   
    string sqlq = "(SELECT EXTRACT(YEAR FROM r.ridedate) AS year FROM ride r WHERE EXTRACT";
    sqlq += "(YEAR FROM r.ridedate)<";
    sqlq += yr;
    sqlq += " GROUP BY year ORDER BY year DESC LIMIT 4) UNION (SELECT ";
    sqlq += yr;
    sqlq += " AS year) ORDER BY year ASC;";
   
    QSqlQuery qYears = db->get(sqlq);  

   
   
    while (qYears.next()) {
        numOfYears++;
        
        if (qYears.value(0).toInt() != this->year) {
	    yearList[numOfYears] = qYears.value(0).toString().latin1();
	}   
        
	sqlq = "SELECT EXTRACT(YEAR FROM r.ridedate) AS year, SUM(EXTRACT(EPOCH FROM ";
	sqlq += "r.trainingtime)) as trainingtime, SUM(EXTRACT(EPOCH FROM r.elapsedtime)) AS";
	sqlq += "\"total time\", SUM(r.odoafter-r.odobefore) AS \"ODO dist.\", SUM(t.distance) as ";
	sqlq += "distance, SUM(t.accumaltitude) AS \"Acc. alt.\", COUNT(r.ridedate) FROM ride ";
	sqlq += "r, trail t WHERE r.trail=t.id AND EXTRACT(YEAR FROM r.ridedate)<=";
	sqlq += qYears.value(0).toString().latin1();
	sqlq += " AND EXTRACT(YEAR FROM r.ridedate)>=";
	sqlq += qYears.value(0).toString().latin1();
	sqlq += " GROUP BY year;";

	QSqlQuery qYr = db->get(sqlq);

	while (qYr.next()) {
	    this->result.append(fixLength(qYr.value(0).toString(), 7, ' ', 0));
	    this->result.append(fixLength(cnv(qYr.value(1).toInt()), 15, ' ', 1));
	    this->result.append(fixLength(cnv(qYr.value(2).toInt()), 12, ' ', 1));
	    this->result.append(fixLength(qYr.value(4).toString(), 12, ' ', 1));
	    this->result.append(fixLength(qYr.value(3).toString(), 12, ' ', 1));
	    this->result.append(fixLength(qYr.value(5).toString(), 12, ' ', 1));
	    this->result.append(fixLength(qYr.value(4).toString(), 10, ' ', 1) + "\n");
        }
    }
   
   //*******************************************************************
   // Compare time
   // ******************************************************************
   
    line80("=");
    this->result.append("\n\nCompare report: Exercise time.\n");
    this->result.append("------------------------------\n\n");

    sqlq = "SELECT r.ridedate AS date,";
    sqlq += " (SELECT EXTRACT(EPOCH FROM SUM(r1.trainingtime)) FROM ride r1 WHERE ";
    sqlq += " EXTRACT(YEAR FROM r1.ridedate)=";
    sqlq += yearList[0];
    sqlq += " AND r1.ridedate<=r.ridedate) AS \"";
    sqlq += yearList[0];
    sqlq += "\"";
   
    int i;
    for (i=1;i<numOfYears;i++) {
       sqlq += ", (SELECT EXTRACT(EPOCH FROM SUM(r2.trainingtime)) FROM ride r2 WHERE "; 
       sqlq += " EXTRACT(YEAR FROM r2.ridedate)=";
       sqlq += yearList[i];
       sqlq += " AND r2.ridedate<=r.ridedate-"; 
       sqlq += " (1 || 'years')::INTERVAL) AS \"";
       sqlq += yearList[i];
       sqlq+= "\"";
    }
   
    sqlq += " FROM ride r "; 
    sqlq += " WHERE EXTRACT(YEAR FROM r.ridedate)=";
    sqlq += yearList[0];
    sqlq += " ORDER BY r.ridedate; ";


    QSqlQuery qYrCmpTime = db->get(sqlq);

    this->result.append(fixLength("Date", 10, ' ', 1));
    this->result.append("   ");
    this->result.append(fixLength("", 16, ' ', 1));
    for (i=1;i<numOfYears;i++) {
        this->result.append(fixLength(yearList[i], 10, ' ', 1));
    }
    this->result.append("\n");
   
    line80("-");
   
    while ( qYrCmpTime.next() ) {
       this->result.append(fixLength(qYrCmpTime.value(0).toString(), 10, ' ', 1)); 
       this->result.append("   ");
       this->result.append(fixLength(cnv(qYrCmpTime.value(1).toInt()), 10, ' ', 1));
       this->result.append("  :   ");
       for (i=2;i<numOfYears+1;i++) {
	  this->result.append(fixLength(cnv(qYrCmpTime.value(i).toInt()), 10, ' ', 1));
       }
       this->result.append("\n");
    }

   
   //*******************************************************************
   // Compare Distance
   // ******************************************************************
   
    line80("=");
    this->result.append("\n\nCompare report: Distance.\n");
    this->result.append("------------------------------\n\n");

    sqlq = "SELECT r.ridedate AS distance,";
    sqlq += " (SELECT ROUND(CAST(SUM(r1.odoafter-r1.odobefore) AS NUMERIC),1) FROM ride r1 WHERE ";
    sqlq += " EXTRACT(YEAR FROM r1.ridedate)=";
    sqlq += yearList[0];
    sqlq += " AND r1.ridedate<=r.ridedate) AS \"";
    sqlq += yearList[0];
    sqlq += "\"";
   
    for (i=1;i<numOfYears;i++) {
       sqlq += ", (SELECT ROUND(CAST(SUM(r2.odoafter-r2.odobefore) AS NUMERIC),1) FROM ride r2 WHERE "; 
       sqlq += " EXTRACT(YEAR FROM r2.ridedate)=";
       sqlq += yearList[i];
       sqlq += " AND r2.ridedate<=r.ridedate-"; 
       sqlq += " (1 || 'years')::INTERVAL) AS \"";
       sqlq += yearList[i];
       sqlq+= "\"";
    }
   
    sqlq += " FROM ride r "; 
    sqlq += " WHERE EXTRACT(YEAR FROM r.ridedate)=";
    sqlq += yearList[0];
    sqlq += " ORDER BY r.ridedate; ";

    QSqlQuery qYrCmpDst = db->get(sqlq);

    this->result.append(fixLength("Date", 10, ' ', 1));
    this->result.append("   ");
    this->result.append(fixLength("", 16, ' ', 1));
    for (i=1;i<numOfYears;i++) {
        this->result.append(fixLength(yearList[i], 10, ' ', 1));
    }
    this->result.append("\n");
   
    line80("-");
   
    while ( qYrCmpDst.next() ) {
       this->result.append(fixLength(qYrCmpDst.value(0).toString(), 10, ' ', 1)); 
       this->result.append("   ");
       this->result.append(fixLength(qYrCmpDst.value(1).toString(), 10, ' ', 1));
       this->result.append("  :   ");
       for (i=2;i<numOfYears+1;i++) {
	  this->result.append(fixLength(qYrCmpDst.value(i).toString(), 10, ' ', 1));
       }
       this->result.append("\n");
    }

   
   //*******************************************************************
   // Compare Altitude
   // ******************************************************************
   
    line80("=");
    this->result.append("\n\nCompare report: Altitude.\n");
    this->result.append("------------------------------\n\n");

    sqlq = "SELECT r.ridedate AS date,";
    sqlq += " (SELECT ROUND(CAST(SUM(t.accumaltitude) AS NUMERIC),1) FROM ride r1, trail t WHERE ";
    sqlq += " r1.trail=t.id AND EXTRACT(YEAR FROM r1.ridedate)=";
    sqlq += yearList[0];
    sqlq += " AND r1.ridedate<=r.ridedate) AS \"";
    sqlq += yearList[0];
    sqlq += "\"";
   
    for (i=1;i<numOfYears;i++) {
       sqlq += ", (SELECT ROUND(CAST(SUM(t.accumaltitude) AS NUMERIC),1) FROM ride r2, trail t WHERE "; 
       sqlq += " r2.trail=t.id AND EXTRACT(YEAR FROM r2.ridedate)=";
       sqlq += yearList[i];
       sqlq += " AND r2.ridedate<=r.ridedate-"; 
       sqlq += " (1 || 'years')::INTERVAL) AS \"";
       sqlq += yearList[i];
       sqlq+= "\"";
    }
   
    sqlq += " FROM ride r "; 
    sqlq += " WHERE EXTRACT(YEAR FROM r.ridedate)=";
    sqlq += yearList[0];
    sqlq += "ORDER BY r.ridedate; ";

    QSqlQuery qYrCmp = db->get(sqlq);

    this->result.append(fixLength("Date", 10, ' ', 1));
    this->result.append("   ");
    this->result.append(fixLength("", 16, ' ', 1));
    for (i=1;i<numOfYears;i++) {
        this->result.append(fixLength(yearList[i], 10, ' ', 1));
    }
    this->result.append("\n");
   
    line80("-");
   
    while ( qYrCmp.next() ) {
       this->result.append(fixLength(qYrCmp.value(0).toString(), 10, ' ', 1)); 
       this->result.append("   ");
       this->result.append(fixLength(qYrCmp.value(1).toString(), 10, ' ', 1));
       this->result.append("  :   ");
       for (i=2;i<numOfYears+1;i++) {
	  this->result.append(fixLength(qYrCmp.value(i).toString(), 10, ' ', 1));
       }
       this->result.append("\n");
    }

    line80("=");

    
}

string Report::cnv(long tsec)
{
    stringstream ss;
    string time;
    long hrs,min,sec;

    min = tsec / 60;
    sec = tsec - (min * 60);
    hrs = min / 60;
    min = min - (hrs * 60);
    
    ss << hrs << ":";
    if (min < 10) {
	ss << "0";
    }
    ss << min << ":";
    if (sec < 10) {
	ss << "0";
    }
    ss  << sec; 
    
    getline(ss, time);

    return time;
}

QString Report::fixLength(QString string, uint len, char fillChar, bool rightMargin = FALSE )
{    
    QString filler;
    if (string.length()<len && !rightMargin) {
	string += filler.fill(fillChar, (len-string.length()));
    } else if (string.length()<len && rightMargin) {
	string.insert(0, filler.fill(fillChar, (len-string.length())));
    } else {
	string.truncate(len);
    }
    return string;
}


void Report::head(string name)
{


    string pippo = " BikeMaster2000 report ";
    int p = pippo.length(), n = name.length();
    line80("*");

    for (int i = 0; i < (39 - ((p > n) ? p : n)/2) ;i++) {
        this->result.append("*");
    }
    for (int i = 0; i < ((n - p)/2) ;i++) {
        this->result.append(" ");
    }

    this->result.append(pippo);

    for (int i = 0; i < ((n - p)/2) ;i++) {
        this->result.append(" ");
    }
    for (int i = 0; i < (40 - ((p > n) ? p : n)/2) ;i++) {
        this->result.append("*");
    }
    this->result.append("\n");
    for (int i = 0; i < (39 - ((p > n) ? p : n)/2) ;i++) {
        this->result.append("*");
    }
    for (int i = 0; i < ((p - n)/2) ;i++) {
        this->result.append(" ");
    }

    this->result.append(name);

    for (int i = 0; i < ((p - n)/2) ;i++) {
        this->result.append(" ");
    }
    for (int i = 0; i < (40 - ((p > n) ? p : n)/2);i++) {
        this->result.append("*");
    }
    this->result.append("\n");
    line80("*");
    this->result.append("\n");

}

void Report::line80(string token)
{
    for (int i = 0; i < 80; i++) {
	this->result.append(token);
    }
    this->result.append("\n");
}
