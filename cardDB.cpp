#include "cardDB.h"
#include "msg.h"
#include <iostream>
#include <fstream>
#include <sstream>

cardDB::cardDB() {
	msg::backendInfo("Constructing cardDB");
	readFromDisk();
}

cardDB::~cardDB() {
	msg::backendInfo("Destorying cardDB");
	writeToDisk();
}

Status cardDB::add(cRFIDType rfid, card c) {
	if (cardMap.find(rfid) != cardMap.end()) {
		msg::cardExists(c.getID());
		return 1;
	}

	rfCardIterPair p = cardMap.insert(rfCardPair(rfid, c));
	if (p.second) {
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
	if (it == cardMap.end()) {
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

void cardDB::display() {
	rfCardMap::iterator iter = cardMap.begin();
	while (iter != cardMap.end()) {
		iter->second.debugPrintCard();
		iter++;
	}
}

Status cardDB::monthlyUpdate() {
	rfCardMap::iterator iter;
	for (iter = cardMap.begin(); iter != cardMap.end(); iter++) {
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
			//Use card's own write handler
			<< iter->second.writeCard() << endl;
		iter++;
	}
	dbFile.close();
	return 0;
}

Status cardDB::readFromDisk() {
	ifstream dbFile("cardDB.txt");
	if (!dbFile.is_open()) {
		msg::backendErr("Can't open dbFile");
		return 1;
	}

	//Start the map at a clean state
	cardMap.clear();

	while (!dbFile.eof()) {
		string dbLine, cardConstruct;
		stringstream ss;
		getline(dbFile, dbLine);
		ss << dbLine;

		if (dbLine[0] == 0 || dbLine[0] == '#') {
			//Ignore if line start as null or #
			continue;
		}

		card* c = &card();
		cRFIDType rfid;
		cTypeT cardType;

		ss >> rfid >> cardType;
		getline(ss, cardConstruct); //throw the rest of ss to handler string

		//Switching handlers for different card types
		switch (cardType) {
		case 1:
			c = &studentCard(cardConstruct);
			break;
		case 2:
			c = &teacherCard(cardConstruct);
			break;
		case 3:
			c = &restrictedCard(cardConstruct);
			break;
		default:
			//No match catcher
			msg::backendErr("Card Type not found: " + to_string(cardType));
			break;
		}

		add(rfid, *c);
	}
	return 0;
}
