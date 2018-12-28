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
	cBalanceType r = 0;
	while (!scanf("%lf", &r)) {
		msg::frontendErr("cbal read error");
	}
	return r;
}

cTypeT ui::read::ctype() {
	cTypeT r = 0;
	while (!scanf("%hu", &r)) {
		msg::frontendErr("ctype read error");
	}
	return r;
}

cRideCountType ui::read::cRideCount() {
	cRideCountType d = 0;
	while (!scanf("%u", &d)) {
		msg::frontendErr("cridecount read error");
	}
	return d;
}

vIDType ui::read::vid() {
	vIDType v = 0;
	while (!scanf("%hu", &v)) {
		msg::frontendErr("Please enter a valid vehicle ID");
	}
	return v;
}

vLoadType ui::read::vload() {
	vLoadType r = 0;
	while (!scanf("%hu", &r)) {
		msg::frontendErr("vload read error");
	}
	return r;
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
		msg::newLine();
		msg::setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		std::cout << "UI Base:" << endl << endl
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
			system("pause");
			break;
		}
		system("cls");
	}

	return 0;
}


Status ui::cardReader() {
	msg::header("Card Reader:\nUse RFID=0 to quit");

	vIDType v;
	while (true) {
		msg::inputMsg("Please enter vehicle ID");
		v = ui::read::vid();
		if (!vdb.find(v).isNull()) {
			break;
		}
		msg::frontendErr("Vehicle ID invalid, try again");
	}

	cRFIDType rfid;
	while (true) {
		msg::inputMsg("Please enter card RFID");
		rfid = ui::read::crfid();
		if (rfid == 0) {
			msg::frontendInfo("Exiting cardReader");
			break;
		}

		card* c = cdb.find(rfid);
		if (c == nullptr) {
			msg::frontendErr("卡无效，请重试！");
			continue;
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
	msg::header("0 - Quit");
	msg::header("1 - Add card to database");
	msg::header("2 - Revoke card from database");
	msg::header("3 - Issue a new card from old card");
	msg::header("4 - Veiw card information");
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
		case 4:
			view();
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
		if (cdb.add(p.first, p.second) == 0) {
			msg::frontendInfo("Card add success");
		}
		else {
			msg::frontendErr("Cannot add card into db, please retry");
			delete p.second;
		}
		break;
	case false:
		delete p.second;
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
		if (cdb.del(rfid) == 0) {
			msg::frontendInfo("Card revoke success");
		}
		else {
			msg::frontendErr("Cannot remove card from database");
		}
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
		Status remove = cdb.del_nofree(rfid);
		if(remove != 0){
			msg::frontendErr("Cannot remove card from database");
			return 1;
		}
		Status add = cdb.add(newrfid, c);
		if (add == 0 && remove == 0) {
			msg::frontendInfo("Changes commited");
		}
	}
	return 0;
}

Status ui::cardDB::view() {
	msg::newLine();
	msg::header("Card DB Operations: view card information");
	cIDType cid = -1;
	cRFIDType rfid = -1;

	while (cid != 0) {
		msg::newLine();
		msg::inputMsg("Please input card ID, 0 to quit");
		cid = ui::read::cid();
		rfid = cdb.cidFind(cid);
		if (rfid == 0) {
			msg::frontendErr("Card not found");
			return -1;
		}
		card* c = cdb.find(rfid);
		c->showInfo();
	}
	return 0;
}

Status ui::vehOps::main() {
	msg::newLine();
	msg::header("Vehicle Operations:");
	int mode = -1;
	vIDType vid;
	msg::inputMsg("Please input vehicle ID");
	vid = ui::read::vid();
	veh& v = vdb.find(vid);
	if (v.getMaxLoad() == 0) {
		msg::frontendErr("vID invalid");
		system("pause");
		return 1;
	}

	while (mode != 0) {
		msg::newLine();
		msg::header("Modes:");
		msg::header("0 - Quit");
		msg::header("1 - Set arrival time");
		msg::header("2 - Set departure time");
		msg::header("3 - Set destnation time");
		msg::header("4 - View vehicle information");
		msg::header("5 - View vehicle load");

		msg::newLine();

		msg::inputMsg("Please enter mode");
		while (scanf("%d", &mode) != 1) {
			msg::inputMsg("Please enter a valid number");
		}

		switch (mode) {
		case 0:
			msg::frontendInfo("Exiting vehOps");
			break;
		case 1:
		case 2:
		case 3:
		{
			msg::inputMsg("Please enter time, 0 for now");
			timeType t = ui::read::time();
			if (t == 0) {
				t = time(NULL);
			}

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
		case 4:
			v.print();
			break;
		case 5:
			v.printLoadInfo();
			break;
		default:
			msg::frontendErr("Selected vehOps mode is not available");
			break;
		}

	}
	return 0;
}
