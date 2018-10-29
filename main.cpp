#include "types.h"
#include "db.h"
#include "card.h"
#include "message.h"

db maindb;

rfidType phyRead(){
    rfidType rfid=0;
	scanf("%u", &rfid);
    return rfid;
}

Status readCard(){
	rfidType rfid = phyRead();
	if (rfid == 0) {
		message::cardCantRead();
		return -1;
	}

	card& c = maindb.findCard(rfid);
	if (c.getID() == 0) {
		message::cardNotFound();
		return -1;
	}

    return c.swipe();
}

int main() {
	readCard();
	readCard();
	readCard();
	return 0;
}


