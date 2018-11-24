#include "ui.h"

cRFIDType ui::read::crfid() {
	cRFIDType r=0;
	while (!scanf("%u", &r)) {
		msg::frontendErr("crfid read error");
	}
	return r;
}

cIDType ui::read::cid() {
	return cIDType();
}

cBalanceType ui::read::cbal() {
	return cBalanceType();
}

cTypeT ui::read::ctype() {
	return cTypeT();
}

cRideCountType ui::read::cRideCount() {
	return cRideCountType();
}

vIDType ui::read::vid() {
	return vIDType();
}

vLoadType ui::read::vload() {
	return vLoadType();
}


Status ui::ui() {
	int mode=0;
	while (mode != -1) {
		msg::ui_input("Please enter mode");
		while (scanf("%d", &mode) != 1) {
			msg::ui_input("Please enter a valid number");
		}

		switch (mode) {
		case -1:
			break;
		case 1:
			ui::cardReader();
			break;
		case 2:
			ui::cardDBOps();
			break;
		case 3:
			ui::vehOps();
			break;
		case 4:
			ui::cardDBOps();
			break;
		default:
			msg::frontendErr("Selected ui mode is not available");
			break;
		}
		
	}

	return 0;
}


Status ui::cardReader(){
	vIDType v;
	v = ui::read::vid();

	cRFIDType rfid = ui::read::crfid();
	if (rfid == 0) {
		msg::backendInfo("Exiting cardReader");
	}

	card& c = cdb.find(rfid);
	if (c.getID() == 0) {
		msg::frontendInfo("Invalid card, please retry");
	}

	if (c.swipe(v)) {
		msg::frontendErr("Scan failed, please retry");
	}
}

Status ui::cardDBOps() {
	return Status();
}

Status ui::vehOps() {
	return Status();
}

Status ui::vehDBOps() {
	return Status();
}
