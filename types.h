#pragma once
#include <ctime>

#define MAX_DB_LINE_LEN 4096
#define BUF_LEN 128

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

//Sch:
typedef long long timeType;
