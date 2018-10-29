#include "cardDB.h"
#include "message.h"
#include <iostream>
#include <fstream>

cardDB::cardDB() {
	message::backendInfo("Constructing DB");
	readFromDisk();
}

cardDB::~cardDB() {
	message::backendInfo("Destorying DB");
	writeToDisk();
}

Status cardDB::addCard(rfidType rfid, card c){
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

card& cardDB::findCard(rfidType rfid){
    rfCardMap::iterator it = dbMap.find(rfid);
    if(it == dbMap.end()){
        return emptyCard;
    }
    
    return it->second;
}

void cardDB::displayAllCards(){
    rfCardMap::iterator iter=dbMap.begin();
    while(iter != dbMap.end()){
        iter->second.debugPrintCard();
        iter++;
    }
}

Status cardDB::monthlyUpdate(){
    rfCardMap::iterator iter;
    for(iter=dbMap.begin(); iter!=dbMap.end(); iter++){
        iter->second.setRideCount(0);
    }
	return 0;
}

Status cardDB::writeToDisk() {
	fstream dbFile("cardDB.txt");
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

Status cardDB::readFromDisk()
{
	ifstream dbFile("cardDB.txt");
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
