/*************************
*	ui.h
*	Defines ui namespace and its handler subspaces
*	Handles console interface related operations
*************************/

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

		timeType time();
	}

	Status ui();
	Status cardReader();

	namespace cardDB {
		Status main();	
		Status add();
		Status revoke();
		Status issue();
	}

	namespace vehOps {
		Status main();
	}
	Status vehDBOps();
}