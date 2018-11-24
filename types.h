#pragma once
#include <ctime>

#define MAX_DB_LINE_LEN 4096
#define BUF_LEN 128

//Core
typedef int Status;

//Card:
typedef unsigned int cRFIDType;
typedef unsigned long long cIDType;
typedef double cBalanceType;
typedef unsigned short cTypeT;
typedef unsigned int cRideCountType;

//Veh:
typedef unsigned short vIDType;
typedef unsigned short vLoadType;

//Sch:
typedef long long timeType;
