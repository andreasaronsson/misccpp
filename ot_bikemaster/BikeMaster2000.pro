TEMPLATE	= app
LANGUAGE	= C++

CONFIG	+= qt warn_on release

HEADERS	+= Calender.h \
	CalenderDay.h \
	Container.h \
	DbConn.h \
	Ride.h \
	Rides.h \
	Preferences.h \
	Trails.h \
	Bikes.h \
	Frames.h \
	Wheels.h \
	Wheel.h \
	Tire.h \
	Tires.h \
	Computer.h \
	Computers.h \
	Gearing.h \
	Gearings.h \
	Report.h \
	RideCheckPoints.h \
	RideCheckPoint.h \
	CheckPoint.h \
	CheckPoints.h \
	ReportItem.h \
	FrameTypes.h \
	RoadConditions.h \
	SkillLevels.h

SOURCES	+= main.cpp \
	CalenderDay.cpp \
	Calender.cpp \
	Container.cpp \
	DbConn.cpp \
	Ride.cpp \
	Rides.cpp \
	Trails.cpp \
	Trail.cpp \
	Bikes.cpp \
	Bike.cpp \
	Frames.cpp \
	Frame.cpp \
	Preferences.cpp \
	Wheels.cpp \
	Wheel.cpp \
	Tire.cpp \
	Tires.cpp \
	Computer.cpp \
	Computers.cpp \
	Gearing.cpp \
	Gearings.cpp \
	Report.cpp \
	RideCheckPoints.cpp \
	RideCheckPoint.cpp \
	CheckPoint.cpp \
	CheckPoints.cpp \
	ReportItem.cpp \
	FrameTypes.cpp \
	RoadConditions.cpp \
	SkillLevels.cpp

FORMS	= mainform.ui \
	RideDataForm.ui \
	reportdisplay.ui \
	specialreportform.ui \
	ReportForm.ui \
	Prefwindow.ui

IMAGES	= images/filenew \
	images/fileopen \
	images/filesave \
	images/print \
	images/undo \
	images/redo \
	images/editcut \
	images/editcopy \
	images/editpaste \
	images/searchfind

	
unix {
  UI_DIR = .ui
  MOC_DIR = .moc
  OBJECTS_DIR = .obj
}
