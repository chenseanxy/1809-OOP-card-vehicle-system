#include "types.h"
#include "veh.h"
#include "message.h"

veh::veh(string lic, string driv, vehLoadType maxLo, times schT) {
	license = lic;
	driver = driv;
	load = 0;
	maxLoad = maxLo;
	vehTime = { 0,0,0 };
	schTime = schT;
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

Status veh::getLoad() const {
	return load;
}

string veh::getLicense() const {
	return license;
}

string veh::getDriver() const {
	return driver;
}

times veh::getSch() const {
	return schTime;
}

times veh::getTime() const {
	return vehTime;
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

