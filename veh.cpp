#include "types.h"
#include "veh.h"
#include "message.h"

veh::veh() {
	maxLoad = 0;
}

veh::veh(string lic, string driv, vehLoadType maxLo, sch schT, vehNumType nv) {
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

bool veh::isArrOnTime(time_t acceptableDelta = 120) const {
	return abs(schTime.tArr - vehTime.tArr) < acceptableDelta;
}
bool veh::isDeptOnTime(time_t acceptableDelta = 120) const {
	return abs(schTime.tDept - vehTime.tDept) < acceptableDelta;
}
bool veh::isDestOnTime(time_t acceptableDelta = 120) const {
	return abs(schTime.tDest - vehTime.tDest) < acceptableDelta;
}

bool veh::isFull() const {
	return load >= maxLoad;
}

vehLoadType veh::getLoad() const {
	return load;
}

vehLoadType veh::getMaxLoad() const {
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

vehNumType veh::getNextVeh() const {
	return nextVeh;
}

void veh::print() const {
	message::debug("License: " + getLicense());
	message::debug("Driver: " + getDriver());
	message::debug("Load / MaxLoad: " + to_string(getLoad()) + " / " + to_string(getMaxLoad()));
	message::debug("isFull: " + to_string(isFull()));
	//TODO: More debug info required
}

Status veh::incLoad() {
	if (isFull()) {
		message::frontendErr("Sorry, vehicle is full.");
	}
	load++;
	return 0;
}

Status veh::setLoad(vehLoadType amount) {
	load = amount;
	return 0;
}

Status veh::timeArr(time_t t = time(NULL)) {
	vehTime.tArr = t;
	return 0;
}
Status veh::timeDept(time_t t = time(NULL)) {
	vehTime.tDept = t;
	return 0;
}
Status veh::timeDest(time_t t = time(NULL)) {
	vehTime.tDest = t;
	return 0;
}

