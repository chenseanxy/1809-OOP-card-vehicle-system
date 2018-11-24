#include "cardDB.h"
#include "msg.h"
#include <iostream>
#include <fstream>

cardDB::cardDB() {
	msg::backendInfo("Constructing cardDB");
	readFromDisk();
}

cardDB::~cardDB() {
	msg::backendInfo("Destorying cardDB");
	writeToDisk();
}

Status cardDB::add(cRFIDType rfid, card c){
    if(cardMap.find(rfid) != cardMap.end()){
        msg::cardExists(c.getID());
        return 1;
    }

    rfCardIterPair p=cardMap.insert(rfCardPair(rfid, c));
    if(p.second){
        msg::cardAddSuccess(c.getID());
        return 0;
    }

    msg::qError(string("Card not added"));
    return -1;
}

Status cardDB::del(cRFIDType rfid) {
	rfCardMap::iterator it = cardMap.find(rfid);
	if (it == cardMap.end()) {
		msg::backendErr("Cannot delete, card not found");
		return -1;
	}

	return cardMap.erase(rfid);
}

card& cardDB::find(cRFIDType rfid) {

    rfCardMap::iterator it = cardMap.find(rfid);
    if(it == cardMap.end()){
        return emptyCard;
    }
    
    return it->second;
}

cRFIDType cardDB::cidFind(cIDType id) {
	if (id == 0) {
		return 0;
	}

	rfCardMap::iterator it;
	for (it = cardMap.begin(); it != cardMap.end(); it++) {
		if (it->second.getID() == id) {
			break;
		}
	}
	if (it == cardMap.end()) {
		return 0;
	}
	return it->first;
}

void cardDB::display(){
    rfCardMap::iterator iter=cardMap.begin();
    while(iter != cardMap.end()){
        iter->second.debugPrintCard();
        iter++;
    }
}

Status cardDB::monthlyUpdate(){
    rfCardMap::iterator iter;
    for(iter=cardMap.begin(); iter!=cardMap.end(); iter++){
        iter->second.setRideCount(0);
    }
	return 0;
}

Status cardDB::writeToDisk() {
	fstream dbFile("cardDB.txt");
	if (!dbFile.is_open()) {
		msg::backendErr("Can't open dbFile");
		return 1;
	}

	rfCardMap::iterator iter = cardMap.begin();
	while (iter != cardMap.end()) {
		dbFile << iter->first << " "
			<< iter->second.getID() << " "
			<< iter->second.getCardType() << " "
			<< iter->second.getBalance() << " "
			<< iter->second.getRideCount() << " " 
			<< iter->second.getName() << " "
			<< iter->second.getGender() << " "
			<< iter->second.getUnit() << endl;
		iter++;
	}
	dbFile.close();
	return 0;
}

Status cardDB::readFromDisk()
{
	ifstream dbFile("cardDB.txt");
	if (!dbFile.is_open()) {
		msg::backendErr("Can't open dbFile");
		return 1;
	}

	cardMap.clear();
	char buffer[MAX_DB_LINE_LEN];
	cRFIDType rfid;
	cIDType cid;
	cTypeT cType;
	cBalanceType cBal;
	cRideCountType cRideCount;
	char nameBuf[BUF_LEN] = { 0 }, genBuf[2] = { 0 }, unitBuf[BUF_LEN] = { 0 };
	int scanCount;

	while (!dbFile.eof()) {
		dbFile.getline(buffer, MAX_DB_LINE_LEN);

		if (buffer[0] == 0 || buffer[0] == '#') {
			continue;
		}

		scanCount=sscanf(buffer, "%u %llu %hu %lf %u %s %s %s", &rfid, &cid, &cType, &cBal, &cRideCount, nameBuf, genBuf, unitBuf);
		if (scanCount != 8) {
			msg::dbFileReadError(string(buffer));
			cardMap.clear();
			return -1;
		}

		string sname(nameBuf), sgender(genBuf), sunit(unitBuf);
		card c(cid, cType, cBal, cRideCount, sname, sgender, sunit);
		add(rfid, c);
	}
	return 0;
}
