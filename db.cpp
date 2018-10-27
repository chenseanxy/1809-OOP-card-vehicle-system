#include "db.h"
#include "message.h"
#include <iostream>

Status db::addCard(rfidType rfid, card c){
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

card db::findCard(rfidType rfid) const{
    card emptycard;
    rfCardMap::const_iterator it = dbMap.find(rfid);
    if(it == dbMap.end()){
        return emptycard;
    }
    
    return it->second;
}

void db::displayAllCards(){
    rfCardMap::iterator iter=dbMap.begin();
    while(iter != dbMap.end()){
        iter->second.debugPrintCard();
        iter++;
    }
}

Status db::monthlyUpdate(){
    rfCardMap::iterator iter;
    for(iter=dbMap.begin(); iter!=dbMap.end(); iter++){
        iter->second.setRideCount(0);
    }
	return 1;
}

