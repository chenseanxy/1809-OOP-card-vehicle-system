#pragma once
#include "types.h"
#include <string>

using namespace std;

class veh {
	string license;
	string driver;
	vehLoadType load;
	vehLoadType static maxLoad;
	times schTime;
	times vehTime;

public:
	veh(string lic, string driv, vehLoadType maxLo, times schT);
	~veh();

	bool isArrOnTime(time_t acceptableDelta) const;
	bool isDeptOnTime(time_t acceptableDelta) const;
	bool isDestOnTime(time_t acceptableDelta) const;
	bool isFull() const;
	Status getLoad() const;
	string getLicense() const;
	string getDriver() const;
	times getSch() const;
	times getTime() const;

	Status incLoad();
	Status setLoad(vehLoadType amount);

	Status timeArr(time_t t);
	Status timeDept(time_t t);
	Status timeDest(time_t t);
};
