#pragma once

#include <map>
#include "card.h"

using namespace std;

typedef map<rfidType,card> rfCardMap;
typedef pair<rfidType,card> rfCardPair;
typedef pair<rfCardMap::iterator,bool> rfCardIterPair;

class cardDB{
    rfCardMap cardMap;

public:
	card emptyCard;

	cardDB();
	~cardDB();

	Status add(rfidType rfid, card c);
	card& find(rfidType rfid);

	void display();

	Status monthlyUpdate();
	Status writeToDisk();
	Status readFromDisk();
};
