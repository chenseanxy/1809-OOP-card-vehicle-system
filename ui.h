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

//	ui: 
//	namespace to handle all console events
//	use sub-namespaces to handle modes
namespace ui {
	
	//	read sub-namespace: (decrepated)
	//	handles reading from console
	//	for common data types
	namespace read {
		cRFIDType crfid();
		cIDType cid();
		cBalanceType cbal();
		cTypeT ctype();
		cRideCountType cRideCount();

		vIDType vid();
		vLoadType vload();

		timeType time();

		bool confirm();
	}

	//	ui(): main console logic
	//	input mode to switch between modes
	//	1-cardReader, 2-cardDB
	//	3-vehOps, 4-vehDB
	//	0 to quit
	Status ui();

	//	cardReader(): cardReader mode
	//	actions: reads vehNum from console
	//			 then swipes every card by inputing rfid
	//			 0 as rfid to quit
	Status cardReader();

	//	cardDB: card database operations mode
	namespace cardDB {
		Status main();	
		Status add();
		Status revoke();
		Status issue();
		Status view();
	}

	namespace vehOps {
		Status main();
	}
	Status vehDBOps();
}