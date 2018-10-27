#include "card.h"
#include <iostream>
using namespace std;

void testCardGets(card c){
    cout 
    << "[TEST] ID:" << c.getID() << endl
    << "[TEST] Type:" << c.getCardType() << endl
    << "[TEST] Bal:" << c.getBalance() << endl
    << "[TEST] RideC:" << c.getRideCount() << endl
    << "[TEST] FreeAvial:" << c.getFreeRideAvail() << endl;
}

int main(){
    card c=card(17130188019,0);
    c.debugPrintCard();
    testCardGets(c);

    c.setBalance(4);
    c.setCardType(2);
    c.setRideCount(19);
    c.debugPrintCard();

    c.swipe();
    c.debugPrintCard();
    c.swipe();
    c.debugPrintCard();

    system("pause");
}
