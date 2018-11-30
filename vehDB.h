#pragma once

#include "types.h"
#include "veh.h"
#include <map>

using namespace std;

typedef map<vIDType, veh> vehMapType;

class vehDB {
	vehMapType vehMap;
	veh emptyVeh;

public:
	vehDB();
	~vehDB();

	Status add(vIDType vehNum, veh v);
	veh& find(vIDType vehNum);

	void display();

	Status writeToDisk();
	Status readFromDisk();

	bool isVehFull(vIDType vehNum);
	Status rideVeh(vIDType vid, vLoadType load = 1);
};
