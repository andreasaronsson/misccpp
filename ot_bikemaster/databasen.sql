DROP TABLE Bike;
DROP TABLE Frame;
DROP TABLE Wheel;
DROP TABLE Gearing;
DROP TABLE Tire;
DROP TABLE Computer;
DROP TABLE Checkpoint;
DROP TABLE Ride;
DROP TABLE Trail;
DROP TABLE Preferences;
DROP TABLE DateFormat;
DROP TABLE RideCheckpoint;

CREATE TABLE Frame(
	id SERIAL PRIMARY KEY,
	name VARCHAR(50),	
	model VARCHAR(50),
	serialNumber VARCHAR(50),
	sensorPos VARCHAR(5) CHECK (sensorPos IN ('front','back','none')),
	type VARCHAR(50), 
	description TEXT
);

CREATE TABLE Bike(
	id SERIAL PRIMARY KEY,
	frame INTEGER NOT NULL,
	backWheel INTEGER,
	frontWheel INTEGER,
	bikeGearing INTEGER NOT NULL,
	wheelGearing INTEGER,
	frontTire INTEGER,
	backTire INTEGER,
	computer INTEGER,
	assemblyDate DATE
);


CREATE TABLE Wheel (
	id SERIAL PRIMARY KEY,
	name VARCHAR(50),	
	brand VARCHAR(50),
	model VARCHAR(50),
	circumference FLOAT(2) CHECK (circumference >= 0.00 OR circumference <= 9999.99),
	type VARCHAR(5) CHECK (type IN ('front', 'back')),
	description TEXT 
);

CREATE TABLE Gearing(
	id SERIAL PRIMARY KEY,
	name VARCHAR(50)
	noOfCogWheels SMALLINT,
	noOfTeeth SMALLINT[],
	type VARCHAR(5) CHECK (type IN ('bike', 'wheel'))	
);

CREATE TABLE Computer (
	id SERIAL PRIMARY KEY,
	name VARCHAR(50),
	brand VARCHAR(50),
	model VARCHAR(50),
	serialNumber VARCHAR(50),
	settings FLOAT(2) CHECK (settings >= 0 OR settings <= 9999.99),
	tripDistance BOOLEAN,
	tripTime BOOLEAN,
	odometer BOOLEAN,
	averageCadence BOOLEAN,
	altiMeter BOOLEAN,
	maxSpeed BOOLEAN,
	averageSpeed BOOLEAN,
	maxOdo FLOAT(2) CHECK (maxOdo >= 0 OR maxOdo <= 9999.99),
);

CREATE TABLE Checkpoint(
	id SERIAL PRIMARY KEY,
	name VARCHAR(50),
	location TEXT,
	distance FLOAT(2),
	altitude FLOAT(2),
	trail INTEGER NOT NULL
);

CREATE TABLE Ride (
        id SERIAL PRIMARY KEY,
        rideDate DATE,
	startTime TIME,
	amountOfSleep TIME,
	trainingTime TIME,
	elapsedTime TIME,
	odoBefore FLOAT(2),
	odoAfter FLOAT(2),
	averageSpeed FLOAT(2),
	maxSpeed FLOAT(2),
	tempData BOOLEAN,
	maxTemp FLOAT(2),
	minTemp FLOAT(2),
	rating VARCHAR(50),
	type VARCHAR(50),
	bike INTEGER NOT NULL,
	trail INTEGER NOT NULL
);

CREATE TABLE Trail (
	id SERIAL PRIMARY KEY,
	name VARCHAR(50),
	stationary BOOLEAN,
	useFrontWheel BOOLEAN,
	useBackWheel BOOLEAN,
	mapReference TEXT,
	distance FLOAT(2),
	maxAltitude FLOAT(2),
	minAltitude FLOAT(2),
	accumAltitude FLOAT(2),
	roadCondition VARCHAR(50),
	skillLevel VARCHAR(50),
	description TEXT
);


CREATE TABLE Tire(
	id SERIAL PRIMARY KEY,
	name VARCHAR(50),
	brand VARCHAR(50),
	model VARCHAR(50)
);

CREATE TABLE Preferences(
	distance VARCHAR(5) CHECK (distance IN ('km', 'miles')),
	height VARCHAR(6) CHECK (height IN ('meters','feet')),
	speed VARCHAR(4) CHECK (speed IN ('km/h','mph')),
	temp VARCHAR(1) CHECK (temp IN ('C','F')),
	weight VARCHAR(6) CHECK (weight IN ('kilo','pounds')),
	width VARCHAR(4) CHECK (width IN ('cm','inch')),
	presentation VARCHAR(8) CHECK (presentation IN ('bikeused', 'distance', 'time', 'trail'))
);

CREATE TABLE DateFormat(
	dateOrder VARCHAR(3) CHECK (dateOrder IN ('MDY','DMY','YMD')),
	monthFormat VARCHAR(6) CHECK (monthFormat IN ('full','short','number')),
	weekStarts VARCHAR(6) CHECK (weekStarts IN ('monday','sunday')),
	dayLeadingZeroes BOOLEAN,
	century SMALLINT CHECK (century = 2 OR century = 4)
);

CREATE TABLE RideCheckpoint(
       ride INTEGER,
       checkpoint INTEGER,
       checkTime TIME,
       PRIMARY KEY(ride, checkpoint)
);
