#include "db.h"
#include "message.h"
#include <iostream>

Status db::addCard(rfidType rfid){
    card c;

    if(dbMap.find(rfid) != dbMap.end()){
        message::cardExists();
        return 1;
    }

    insertPair p=dbMap.insert(rfCardPair(rfid, c));
    if(p.second){
        message::cardAddSuccess();
        return 0;
    }

    message::qError(string("Card is not added"));
    return -1;
}

card db::findCard(rfidType rfid) const{
    //TODO
}

