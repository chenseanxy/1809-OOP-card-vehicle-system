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

Status cardDB::add(rfidType rfid, card c){
    if(cardMap.find(rfid) != cardMap.end()){
        message::cardExists(c.getID());
        return 1;
    }

    rfCardIterPair p=cardMap.insert(rfCardPair(rfid, c));
    if(p.second){
        message::cardAddSuccess(c.getID());
        return 0;
    }

    message::qError(string("Card not added"));
    return -1;
}

card& cardDB::find(rfidType rfid){
    rfCardMap::iterator it = cardMap.find(rfid);
    if(it == cardMap.end()){
        return emptyCard;
    }
    
    return it->second;
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
		message::dbFileOpenError();
		return 1;
	}

	rfCardMap::iterator iter = cardMap.begin();
	while (iter != cardMap.end()) {
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

	cardMap.clear();
	char buffer[4096];
	rfidType rfid;
	idType id;
	cardTypeT cardType;
	balanceType balance;
	rideCountType rideCount;
	int scanCount;

	while (!dbFile.eof()) {
		dbFile.getline(buffer, 4096);

		if (buffer[0] == 0 || buffer[0] == '#') {
			continue;
		}

		scanCount=sscanf(buffer, "%u %llu %hu %lf %u",&rfid, &id, &cardType, &balance, &rideCount);
		if (scanCount != 5) {
			message::dbFileReadError(string(buffer));
			cardMap.clear();
			return -1;
		}

		card c(id, cardType, balance, rideCount);
		add(rfid, c);
	}
	return 0;
}
