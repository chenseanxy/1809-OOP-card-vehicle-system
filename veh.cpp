#include "types.h"
#include "veh.h"

veh::veh() {
}

veh::~veh() {
}

Status veh::incLoad() {
	load++;
	return 0;
}

Status veh::getLoad() {
	return load;
}
