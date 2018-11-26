#include "types.h"
#include "veh.h"
#include "msg.h"

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

void veh::print() const {
	msg::debug("License: " + getLicense());
	msg::debug("Driver: " + getDriver());
	msg::debug("Load / MaxLoad: " + to_string(getLoad()) + " / " + to_string(getMaxLoad()));
	msg::debug("isFull: " + to_string(isFull()));
	//TODO: More debug info required
}

Status veh::incLoad() {
	if (isFull()) {
		msg::frontendErr("Sorry, vehicle is full.");
	}
	load++;
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

