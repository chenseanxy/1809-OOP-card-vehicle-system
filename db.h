#ifndef DB_H
#define DB_H

#include <map>
#include "card.h"

using namespace std;

typedef map<rfidType,card> rfCardMap;
typedef pair<rfidType,card> rfCardPair;
typedef pair<rfCardMap::iterator,bool> iterPair;

class db{
    rfCardMap dbMap;

    public:
	card emptyCard;

	db();
	~db();

	Status addCard(rfidType rfid, card c);
	card& findCard(rfidType rfid);

	void displayAllCards();

	Status monthlyUpdate();
	Status writeToDisk();
	Status readFromDisk();
};

#endif
