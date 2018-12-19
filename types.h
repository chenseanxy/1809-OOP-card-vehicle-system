/*************************
*	types.h
*	Defines useful types for the project
*************************/


#pragma once
#include <ctime>

//	MAX_DB_LINE_LEN: defines the size of DB Line-reading buffer
//	Decrepated: now changed to stringStream impl
//	#define MAX_DB_LINE_LEN 4096

//	BUF_LEN: defines the size of one buffer for one value, used in string reading
//	Decrepated: now changed to stringStream impl
//	#define BUF_LEN 128


/************
*	Core
************/

//	Status: indicates the status of function return
typedef int Status;


/************
*	Card
* card and cardOwner information
************/

//	cRFIDType: stores card RFID data, used as key for cardDB
typedef unsigned int cRFIDType;

//	cIDType: stores cardID (studentID or teacherID)
typedef unsigned long long cIDType;

//	cBalanceType: stores card balance
typedef double cBalanceType;

//	cTypeT: used to store cardType, now using subclasses
typedef unsigned short cTypeT;

//	cRideCountType: stores ride count
typedef unsigned int cRideCountType;


/************
*	Veh
* vehicle information
************/

//	vIDType: stores vehicle unique id, used as key for vehDB
typedef unsigned short vIDType;

//	vLoadType: stores the load of a vehicle, as how many person are in the vehicle
typedef unsigned short vLoadType;


/************
*	Sch
* schedule information
************/

//	timeType: time handling in schedules
typedef long long timeType;
