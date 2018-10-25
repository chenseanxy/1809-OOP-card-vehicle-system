#ifndef DB_H
#define DB_H

#include <map>
#include "card.h"

using namespace std;

typedef map<rfidType,card> rfCardMap;
typedef pair<rfidType,card> rfCardPair;
typedef pair<rfCardMap::iterator,bool> insertPair;

class db{
    rfCardMap dbMap;

    public:
    Status addCard(rfidType rfid);
    card findCard(rfidType rfid) const;

    Status monthlyUpdate();
};

#endif
