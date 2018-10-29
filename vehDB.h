#pragma once

#include "types.h"
#include "veh.h"
#include <map>

using namespace std;

typedef map<vehNumType, veh> vehMapType;

class vehDB {
	vehMapType vehMap;

public:
	vehDB();
	~vehDB();

	Status add(vehNumType vehNum, veh v);
	veh& find(vehNumType vehNum);

	void display();

	Status writeToDisk();
	Status readFromDisk();
};
