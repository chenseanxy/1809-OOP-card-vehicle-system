#pragma once
#include <ctime>

//Core
typedef int Status;

//Card:
typedef unsigned long long idType;
typedef double balanceType;
typedef unsigned short cardTypeT;
typedef unsigned int rideCountType;

//Veh:
typedef unsigned int rfidType;
typedef unsigned short vehNumType;
typedef unsigned short vehLoadType;
typedef struct times {
	time_t tArr;
	time_t tDept;
	time_t tDest;
};