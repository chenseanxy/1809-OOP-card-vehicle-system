#pragma once
#include "types.h"
#include "sch.h"
#include <string>

using namespace std;

class veh {
	string license;
	string driver;
	vehLoadType load;
	vehLoadType maxLoad;
	sch schTime;
	sch vehTime;
	vehNumType nextVeh;

public:
	veh();
	veh(string lic, string driv, vehLoadType maxLo, sch schT, vehNumType nv);
	~veh();

	bool isArrOnTime(time_t acceptableDelta) const;
	bool isDeptOnTime(time_t acceptableDelta) const;
	bool isDestOnTime(time_t acceptableDelta) const;
	bool isFull() const;
	vehLoadType getLoad() const;
	vehLoadType getMaxLoad() const;
	string getLicense() const;
	string getDriver() const;
	sch getSch() const;
	sch getTime() const;
	vehNumType getNextVeh() const;
	void print() const;

	Status incLoad();
	Status setLoad(vehLoadType amount);

	Status timeArr(time_t t);
	Status timeDept(time_t t);
	Status timeDest(time_t t);
};
