#include "types.h"
#include "veh.h"
#include "msg.h"
#include <iostream>

veh::veh() {
	maxLoad = 0;
}

veh::veh(string lic, string driv, vLoadType maxLo, sch schT, vIDType nv) {
	license = lic;
	driver = driv;
	load = 0;
	vehTime = { 0,0,0 };
	schTime = schT;
	nextVeh = nv;
	maxLoad = maxLo;
}

veh::~veh() {
}

bool veh::isArrOnTime(timeType acceptableDelta = 120) const {
	return abs(schTime.tArr - vehTime.tArr) < acceptableDelta;
}
bool veh::isDeptOnTime(timeType acceptableDelta = 120) const {
	return abs(schTime.tDept - vehTime.tDept) < acceptableDelta;
}
bool veh::isDestOnTime(timeType acceptableDelta = 120) const {
	return abs(schTime.tDest - vehTime.tDest) < acceptableDelta;
}

bool veh::isFull() const {
	return load >= maxLoad;
}

vLoadType veh::getLoad() const {
	return load;
}

vLoadType veh::getMaxLoad() const {
	return maxLoad;
}

string veh::getLicense() const {
	return license;
}

string veh::getDriver() const {
	return driver;
}

sch veh::getSch() const {
	return schTime;
}

sch veh::getTime() const {
	return vehTime;
}

vIDType veh::getNextVeh() const {
	return nextVeh;
}

bool veh::isNull() const {
	return (maxLoad == 0);
}

void veh::print() const {
	msg::setColor(10);
	std::cout << "--------------------Vehicle Info--------------------" << endl
		<< "License: " << getLicense() << endl
		<< "Driver: " << getDriver() << endl
		<< "Current Load / Max Load: " << getLoad() << " / " << getMaxLoad() << endl
		<< "Scheduled Time: " << getSch() << endl
		<< "Vehicle Time: " << getTime() << endl << endl;
	msg::resetColor();
}

void veh::printLoadInfo() const {
	double rate = getLoad() / getMaxLoad();
	
	msg::setColor(10);
	std::cout << "Current Load / Max Load: " << getLoad() << " / " << getMaxLoad() << endl
		<< "Load Rate: " << rate << endl;
	msg::resetColor();
}

Status veh::incLoad(vLoadType amount=1) {
	if (isFull()) {
		msg::frontendErr("Sorry, vehicle is full.");
	}
	load+=amount;
	return 0;
}

Status veh::setLoad(vLoadType amount) {
	load = amount;
	return 0;
}

Status veh::timeArr(timeType t = timeType(time(NULL))) {
	vehTime.tArr = t;
	return 0;
}
Status veh::timeDept(timeType t = timeType(time(NULL))) {
	vehTime.tDept = t;
	return 0;
}
Status veh::timeDest(timeType t = timeType(time(NULL))) {
	vehTime.tDest = t;
	return 0;
}

