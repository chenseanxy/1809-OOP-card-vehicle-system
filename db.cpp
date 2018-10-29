#include "db.h"
#include "message.h"
#include <iostream>
#include <fstream>

db::db() {
	message::backendInfo("Constructing DB");
	readFromDisk();
}

db::~db() {
	message::backendInfo("Destorying DB");
	writeToDisk();
}

Status db::addCard(rfidType rfid, card c){
    if(dbMap.find(rfid) != dbMap.end()){
        message::cardExists();
        return 1;
    }

    iterPair p=dbMap.insert(rfCardPair(rfid, c));
    if(p.second){
        message::cardAddSuccess();
        return 0;
    }

    message::qError(string("Card not added"));
    return -1;
}

card& db::findCard(rfidType rfid){
    rfCardMap::iterator it = dbMap.find(rfid);
    if(it == dbMap.end()){
        return emptyCard;
    }
    
    return it->second;
}

void db::displayAllCards(){
    rfCardMap::iterator iter=dbMap.begin();
    while(iter != dbMap.end()){
        iter->second.debugPrintCard();
        iter++;
    }
}

Status db::monthlyUpdate(){
    rfCardMap::iterator iter;
    for(iter=dbMap.begin(); iter!=dbMap.end(); iter++){
        iter->second.setRideCount(0);
    }
	return 0;
}

Status db::writeToDisk() {
	fstream dbFile("db.txt");
	if (!dbFile.is_open()) {
		message::dbFileOpenError();
		return 1;
	}

	rfCardMap::iterator iter = dbMap.begin();
	while (iter != dbMap.end()) {
		dbFile << iter->first << " "
			<< iter->second.getID() << " "
			<< iter->second.getCardType() << " "
			<< iter->second.getBalance() << " "
			<< iter->second.getRideCount() << " " << endl;
		iter++;
	}
	dbFile.close();
	return 0;
}

Status db::readFromDisk()
{
	ifstream dbFile("db.txt");
	if (!dbFile.is_open()) {
		message::dbFileOpenError();
		return 1;
	}

	dbMap.clear();
	char buffer[4096];
	rfidType rfid;
	idType id;
	cardTypeT cardType;
	balanceType balance;
	rideCountType rideCount;
	int scanCount;

	while (!dbFile.eof()) {
		dbFile.getline(buffer, 4096);
		scanCount=sscanf(buffer, "%u %llu %hu %lf %u",&rfid, &id, &cardType, &balance, &rideCount);
		if (scanCount != 5) {
			message::dbFileReadError(string(buffer));
			dbMap.clear();
			return -1;
		}

		card c(id, cardType, balance, rideCount);
		addCard(rfid, c);
	}
	return 0;
}
