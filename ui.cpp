#include "ui.h"

Status ui::ui() {
	int mode=0;
	while (mode != -1) {
		message::ui_input("Please enter mode");
		while (scanf("%d", &mode) != 1) {
			message::ui_input("Please enter a valid number");
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
			message::frontendErr("Selected ui mode is not available");
			break;
		}
		
	}

	return 0;
}

rfidType phyRead() {
	rfidType rfid = 0;
	scanf("%u", &rfid);
	return rfid;
}

Status readCard() {
	rfidType rfid = phyRead();
	if (rfid == 0) {
		message::frontendErr("Cannot read card");
		return -1;
	}

	card& c = cdb.find(rfid);
	if (c.getID() == 0) {
		message::frontendInfo("Invalid card");
		return -1;
	}

	return c.swipe();
}

Status ui::cardReader() {
	return readCard();
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
