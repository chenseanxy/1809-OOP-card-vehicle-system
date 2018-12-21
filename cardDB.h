/*************************
*	cardDB.h
*	Defines cardDB (card database) class
*	Handles card storage related operations
*************************/

#pragma once

#include <map>
#include "card.h"

using namespace std;

typedef map<cRFIDType,card*> rfCardMap;
typedef pair<cRFIDType,card*> rfCardPair;
typedef pair<rfCardMap::iterator,bool> rfCardIterPair;


//	cardDB: 
//	Wrapper for card database
class cardDB{

	//	cardMap: use STL::Map for low-level storage
	//	key: rfid, value: cardObj
    rfCardMap cardMap;

public:

	//	emptyCard: 
	//	reference of null card to return
	card emptyCard;

	cardDB();
	~cardDB();

	//	add(rfid, card): adds rfid,card pair into db
	//	param: rfid as key, cardObject as value
	//	returns: status code, 0-successful
	//			 1-card already exists
	//			 -1-undefined error, card not added
	Status add(cRFIDType rfid, card *c);

	//	del(rfid): deletes the entry with key rfid
	//	param: rfid - used to find the card entry
	//	returns: status code of map.erase
	//			 0-successful, 1-<rfid,card>pair not found
	Status del(cRFIDType rfid);

	Status del_nofree(cRFIDType rfid);
	
	//	find(rfid): find and returns reference of card
	//	param: rfid - used to find card
	//	returns: reference of found card
	//			 null card if not found;
	card* find(cRFIDType rfid);

	//	cidFind(cardid): find the rfid for a cardID
	//	param: id - card id to find
	//		   id=0 to signal null
	//	returns: rfid for the card
	//			 0 if card not found
	cRFIDType cidFind(cIDType id);

	//	display(): (decrepated) display debug info
	void display();

	//	monthlyUpdate(): performs maintence of database
	//	actions: reset rideCount for every card
	//	returns: status code, always 0
	Status monthlyUpdate();
	
	//	writeToDisk(): overwrite the database to "cardDB.txt"
	//		*called when db is destroyed
	//	returns: status code, 0-successful
	//			 1-dbFile(cardDB.txt) cannot be opened
	Status writeToDisk();

	//	readFromDisk(): read the database from "cardDB.txt"
	//	actions: clear the database, read from dbFile
	//			 create cards using card(dbLine) handler
	//			 ignores line if line start with "#"
	//	returns: status code, 0-successful
	//			 1-dbFile(cardDB.txt) cannot be opened
	Status readFromDisk();

	
	rfCardPair readCardInfo(stringstream &ss);
};
