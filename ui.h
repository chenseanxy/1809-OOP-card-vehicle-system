#pragma once

#include "types.h"
#include "cardDB.h"
#include "vehDB.h"
#include "msg.h"
#include "main.h"

namespace ui {
	namespace read {
		cRFIDType crfid();
		cIDType cid();
		cBalanceType cbal();
		cTypeT ctype();
		cRideCountType cRideCount();

		vIDType vid();
		vLoadType vload();
	}

	Status ui();
	Status cardReader();
	namespace cardDB {
		Status main();	
		Status add();
		Status revoke();
		Status issue();
	}
	Status vehOps();
	Status vehDBOps();
}