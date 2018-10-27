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
    Status addCard(rfidType rfid, card c);
    card findCard(rfidType rfid) const;

    void displayAllCards();

    Status monthlyUpdate();
};

#endif
