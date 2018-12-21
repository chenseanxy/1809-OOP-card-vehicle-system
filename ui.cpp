#include "ui.h"
#include <iostream>
#include <sstream>

cRFIDType ui::read::crfid() {
	cRFIDType r = 0;
	while (!scanf("%u", &r)) {
		msg::frontendErr("crfid read error");
	}
	return r;
}

cIDType ui::read::cid() {
	cIDType r = 0;
	if (!scanf("%llu", &r)) {
		msg::frontendErr("cid read error");
	}
	return r;
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
	vIDType v = 0;
	while (!scanf("%hu", &v)) {
		msg::frontendErr("Please enter a valid vehicle ID");
	}
	return v;
}

vLoadType ui::read::vload() {
	return vLoadType();
}

timeType ui::read::time() {
	timeType t = 0;
	while (!scanf("%lld", &t)) {
		msg::frontendErr("time read error");
	}
	return t;
}

bool ui::read::confirm() {
	string input;
	std::cin >> input;
	if (input == "Y" || input == "y") {
		return true;
	}
	return false;
}


Status ui::ui() {
	int mode = -1;
	while (mode != 0) {
		msg::setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << "UI Base:" << endl
			<< "0 - Quit" << endl
			<< "1 - Card Reader" << endl
			<< "2 - Card Database Operations" << endl
			<< "3 - Vehicle Operations" << endl
			<< "4 - Vehicle Database Operations" << endl << endl;
		msg::resetColor();
		msg::inputMsg("Please enter mode");
		while (scanf("%d", &mode) != 1) {
			msg::inputMsg("Please enter a valid number");
		}

		switch (mode) {
		case 0:
			break;
		case 1:
			system("cls");
			ui::cardReader();
			break;
		case 2:
			system("cls");
			ui::cardDB::main();
			break;
		case 3:
			system("cls");
			ui::vehOps::main();
			break;
		case 4:
			system("cls");			
			//ui::vehDBOps();
			break;
		default:
			msg::frontendErr("Selected ui mode is not available");
			break;
		}

		system("cls");

	}

	return 0;
}


Status ui::cardReader() {
	msg::header("Card Reader:\nUse RFID=0 to quit");

	vIDType v;
	msg::inputMsg("Please enter vehicle ID");
	v = ui::read::vid();

	cRFIDType rfid;
	while (true) {
		msg::inputMsg("Please enter card RFID");
		rfid = ui::read::crfid();
		if (rfid == 0) {
			msg::frontendInfo("Exiting cardReader");
			break;
		}

		card* c = cdb.find(rfid);
		if (c == NULL) {
			msg::frontendErr("Invalid card, please retry");
		}

		if (c->swipe(v)) {
			//msg::frontendErr("Error in swipe:");
		}
	}
	return 0;
}

Status ui::cardDB::main() {
	int mode = 0;
	msg::header("Card DB Operations:");
	msg::header("Modes:");
	msg::header("1 - Add card to database");
	msg::header("2 - Revoke card from database");
	msg::header("3 - Issue a new card from old card");
	msg::newLine();
	msg::inputMsg("Please enter mode");
	if (scanf("%d", &mode)) {
		switch (mode) {
		case 1:
			add();
			break;
		case 2:
			revoke();
			break;
		case 3:
			issue();
			break;
		default:
			break;
		}
	}

	system("pause");
	return 0;
}

Status ui::cardDB::add() {
	msg::newLine();
	msg::header("Card DB Operations: Add card to database");

	msg::frontendInfo("For input format please look up the manual");
	msg::inputMsg("Please enter the new card information");

	char lineC[BUF_LEN] = { 0 };
	stringstream ss;
	cin.clear();
	cin.ignore();
	cin.getline(lineC, BUF_LEN, '\n');
	string line(lineC);
	ss << line;

	rfCardPair p = cdb.readCardInfo(ss);

	msg::inputMsg("Information of entered card");
	msg::newLine();
	msg::frontendInfo("RFID: " + to_string(p.first));
	p.second->showInfo();
	msg::inputMsg("Add to the database? (Y/N)");
	switch (read::confirm()) {
	case true:
		cdb.add(p.first, p.second);
		msg::frontendInfo("Card add success");
		break;
	case false:
		free(p.second);
		break;
	}

	return 0;
}

Status ui::cardDB::revoke() {
	msg::newLine();
	msg::header("Card DB Operations: Revoke card from database");
	msg::inputMsg("Please input card ID");
	cIDType cid = ui::read::cid();
	cRFIDType rfid = cdb.cidFind(cid);
	if (rfid == 0) {
		msg::frontendErr("Card not found");
		return -1;
	}

	card* c = cdb.find(rfid);
	msg::inputMsg("Information of selected card");
	msg::newLine();
	msg::frontendInfo("RFID: " + to_string(rfid));
	c->showInfo();
	msg::inputMsg("Revoke card from database? (Y/N)");
	if (read::confirm()) {
		msg::frontendInfo("Card revoke success");
		cdb.del(rfid);
	}
	return 0;
}

Status ui::cardDB::issue() {
	msg::newLine();
	msg::header("Card DB Operations: issue new card from old one");
	msg::inputMsg("Please input card ID");
	cIDType cid = ui::read::cid();
	cRFIDType rfid = cdb.cidFind(cid);
	if (rfid == 0) {
		msg::frontendErr("Card not found");
		return -1;
	}
	card* c = cdb.find(rfid);

	msg::inputMsg("Please input new rfid");
	cRFIDType newrfid = read::crfid();

	msg::inputMsg("Changes:");
	msg::newLine();
	msg::frontendInfo("RFID: " + to_string(rfid) + " -> " +to_string(newrfid));
	c->showInfo();
	msg::inputMsg("Commit changes? (Y/N)");
	if (read::confirm()) {
		cdb.del_nofree(rfid);
		cdb.add(newrfid, c);
		msg::frontendInfo("Changes commited");
	}
	return 0;
}

Status ui::vehOps::main() {
	int mode = 0;
	vIDType vid;
	vid = ui::read::vid();
	veh& v = vdb.find(vid);
	if (v.getMaxLoad() == 0) {
		msg::frontendErr("vID invalid");
		return 1;
	}

	while (mode != -1) {
		msg::inputMsg("Please enter mode, -1 to quit");
		while (scanf("%d", &mode) != 1) {
			msg::inputMsg("Please enter a valid number");
		}

		switch (mode) {
		case -1:
			msg::frontendInfo("Exiting vehOps");
			break;
		case 1:
		case 2:
		case 3:
		{
			msg::inputMsg("Please enter time");
			timeType t = ui::read::time();
			switch (mode) {
			case 1:
				v.timeArr(t);
				break;
			case 2:
				v.timeDept(t);
				break;
			case 3:
				v.timeDest(t);
				break;
			default:
				break;
			}
			break;
		}
		default:
			msg::frontendErr("Selected vehOps mode is not available");
			break;
		}

	}
	return 0;
}
