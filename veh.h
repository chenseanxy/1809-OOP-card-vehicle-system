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

	bool isArrOnTime(time_t acceptableDelta) const;
	bool isDeptOnTime(time_t acceptableDelta) const;
	bool isDestOnTime(time_t acceptableDelta) const;
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

	Status timeArr(time_t t);
	Status timeDept(time_t t);
	Status timeDest(time_t t);
};
