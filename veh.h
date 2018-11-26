#pragma once
#include "types.h"
#include "sch.h"
#include <string>

using namespace std;

class veh {
	string license;
	string driver;
	vLoadType load;
	vLoadType maxLoad;
	sch schTime;
	sch vehTime;
	vIDType nextVeh;

public:
	veh();
	veh(string lic, string driv, vLoadType maxLo, sch schT, vIDType nv);
	~veh();

	bool isArrOnTime(timeType acceptableDelta) const;
	bool isDeptOnTime(timeType acceptableDelta) const;
	bool isDestOnTime(timeType acceptableDelta) const;
	bool isFull() const;
	vLoadType getLoad() const;
	vLoadType getMaxLoad() const;
	string getLicense() const;
	string getDriver() const;
	sch getSch() const;
	sch getTime() const;
	vIDType getNextVeh() const;
	void print() const;

	Status incLoad();
	Status setLoad(vLoadType amount);

	Status timeArr(timeType t);
	Status timeDept(timeType t);
	Status timeDest(timeType t);
};
