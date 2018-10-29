#pragma once
#include "types.h"

class veh {
	vehLoadType load;
	schNumType schNum;

public:
	veh();
	~veh();
	Status getLoad();
	Status incLoad();
};
