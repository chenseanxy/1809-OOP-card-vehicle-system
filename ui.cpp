#include "ui.h"

cRFIDType ui::read::crfid() {
	cRFIDType r=0;
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
		msg::frontendErr("vid read error");
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
}


Status ui::ui() {
	int mode=0;
	while (mode != -1) {
		msg::inputMsg("Please enter mode, -1 to quit");
		while (scanf("%d", &mode) != 1) {
			msg::inputMsg("Please enter a valid number");
		}

		switch (mode) {
		case -1:
			break;
		case 1:
			ui::cardReader();
			break;
		case 2:
			ui::cardDB::main();
			break;
		case 3:
			ui::vehOps::main();
			break;
		case 4:
			ui::vehDBOps();
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

	cRFIDType rfid;
	while (true) {
		rfid = ui::read::crfid();
		if (rfid == 0) {
			msg::backendInfo("Exiting cardReader");
			break;
		}

		card& c = cdb.find(rfid);
		if (c.getID() == 0) {
			msg::frontendInfo("Invalid card, please retry");
		}

		if (c.swipe(v)) {
			msg::frontendErr("Scan failed, please retry");
		}
	}
	return 0;
}

Status ui::cardDB::main() {
	int mode = 0;
	msg::inputMsg("mode: 1-add, 2-revoke, 3-issue");
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

	return 0;
}

Status ui::cardDB::add() {
	msg::frontendInfo("cardDB-add");
	cRFIDType rfid;
	cIDType cid;
	cTypeT cType;
	cBalanceType cBal;
	cRideCountType cRideCount;
	char nameBuf[BUF_LEN] = { 0 }, genBuf[2] = { 0 }, unitBuf[BUF_LEN] = { 0 };
	int scanCount;

	msg::inputMsg("rfid, ID, Type, Bal, RideCount, Name, Gender, Unit");
	scanCount = scanf("%u %llu %hu %lf %u %s %s %s", &rfid, &cid, &cType, &cBal, &cRideCount, nameBuf, genBuf, unitBuf);
	if (scanCount != 8) {
		msg::frontendErr("Invalid entry");
		return -1;
	}

	string sname(nameBuf), sgender(genBuf), sunit(unitBuf);
	card c(cid, cType, cBal, cRideCount, sname, sgender, sunit);
	cdb.add(rfid, c);
	msg::debug("card add success");

	return 0;
}

Status ui::cardDB::revoke() {
	msg::frontendInfo("cardDB-revoke");
	msg::inputMsg("ID");
	cIDType cid = ui::read::cid();
	cRFIDType rfid = cdb.cidFind(cid);
	if (rfid == 0) {
		msg::frontendErr("ID not found");
		return -1;
	}
	
	return cdb.del(rfid);
}

Status ui::cardDB::issue() {
	msg::frontendInfo("cardDB-issue");
	int revResult = revoke();
	if (revResult != 0) {
		msg::frontendErr("Could not delete old card");
		return -1;
	}
	return add();
}

Status ui::vehOps::main() {
	int mode=0;
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
}
