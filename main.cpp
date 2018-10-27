#include "types.h"
#include "db.h"
#include "card.h"
#include "message.h"

db maindb;

rfidType phyRead(){
    rfidType rfid=0;
    return rfid;
}

Status readCard(){
    rfidType rfid=phyRead();
    card c=maindb.findCard(rfid);
    if(c.getID()==0){
        message::cardNotFound();
        return -1;
    }

    return c.swipe();
}
