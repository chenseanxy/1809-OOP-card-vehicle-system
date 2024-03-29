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
	rfCardMap::iterator it;
	for (it = cardMap.begin(); it != cardMap.end(); it++) {
		free(it->second);
	}
}

Status cardDB::add(cRFIDType rfid, card* c) {
	if (cardMap.find(rfid) != cardMap.end()) {
		msg::cardExists(c->getID());
		return 1;
	}

	rfCardIterPair p = cardMap.insert(rfCardPair(rfid, c));
	if (p.second) {
		msg::backendInfo("Sucessfully added card " + to_string(p.first->second->getID()));
		return 0;
	}

	msg::qError(string("Card not added"));
	return -1;
}

Status cardDB::del(cRFIDType rfid) {
	rfCardMap::iterator it = cardMap.find(rfid);
	if (it == cardMap.end()) {
		msg::backendErr("Cannot delete, card not found");
		return 1;
	}
	msg::backendInfo("Deleting card " + to_string(it->second->getID()));
	delete it->second;
	return cardMap.erase(rfid) - 1;
}

Status cardDB::del_nofree(cRFIDType rfid) {
	rfCardMap::iterator it = cardMap.find(rfid);
	if (it == cardMap.end()) {
		msg::backendErr("Cannot delete, card not found");
		return 1;
	}
	msg::backendInfo("Removing card " + to_string(it->second->getID())+" from database");
	return cardMap.erase(rfid) - 1;
}

card* cardDB::find(cRFIDType rfid) {

	rfCardMap::iterator it = cardMap.find(rfid);
	if (it == cardMap.end()) {
		return NULL;
	}

	return it->second;
}

cRFIDType cardDB::cidFind(cIDType id) {
	if (id == 0) {
		return 0;
	}

	rfCardMap::iterator it;
	for (it = cardMap.begin(); it != cardMap.end(); it++) {
		if (it->second->getID() == id) {
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
		iter->second->debugPrintCard();
		iter++;
	}
}

Status cardDB::monthlyUpdate() {
	rfCardMap::iterator iter;
	for (iter = cardMap.begin(); iter != cardMap.end(); iter++) {
		iter->second->setRideCount(0);
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
			<< iter->second->writeCard() << endl;
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

		rfCardPair p = readCardInfo(ss);

		add(p.first, p.second);
	}
	return 0;
}

rfCardPair cardDB::readCardInfo(stringstream &ss) {
	string cardConstruct;
	card* c = NULL;
	cRFIDType rfid;
	cTypeT cardType;

	ss >> rfid >> cardType;

	getline(ss, cardConstruct); //throw the rest of ss to handler string

	//Switching handlers for different card types
	switch (cardType) {
	case 1:
		c = new studentCard(cardConstruct);
		break;
	case 2:
		c = new teacherCard(cardConstruct);
		break;
	case 3:
		c = new restrictedCard(cardConstruct);
		break;
	case 4:
		c = new tempCard(cardConstruct);
		break;
	default:
		//No match catcher
		msg::backendErr("Card Type not found: " + to_string(cardType));
		break;
	}
	
	return rfCardPair(rfid,c);
}
