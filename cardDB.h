#pragma once

#include <map>
#include "card.h"

using namespace std;

typedef map<cRFIDType,card> rfCardMap;
typedef pair<cRFIDType,card> rfCardPair;
typedef pair<rfCardMap::iterator,bool> rfCardIterPair;

class cardDB{
    rfCardMap cardMap;

public:
	card emptyCard;

	cardDB();
	~cardDB();

	Status add(cRFIDType rfid, card c);
	card& find(cRFIDType rfid);

	void display();

	Status monthlyUpdate();
	Status writeToDisk();
	Status readFromDisk();
};
