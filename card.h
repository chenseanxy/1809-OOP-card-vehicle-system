#ifndef CARD_H
#define CARD_H
#define DEBUG

#include "message.h"
#include "types.h"

class card{
    cardTypeT cardType;
    idType id;
    balanceType balance;
    rideCountType rideCount;

    #ifdef DEBUG
    public:
    #endif
    Status charge(balanceType amount=2);
    Status ride();
    Status freeRide();
    Status rejectRide();



    public:
    card();
    card(idType ID, cardTypeT cardT, balanceType bal=0, rideCountType rideC=0);
    ~card();
    bool operator==(card c);

    Status swipe();

	void debugPrintCard() const;
    Status showSwipeInfo() const;
    Status showInfo() const;

    bool getFreeRideAvail() const;
    balanceType getBalance() const;
    idType getID() const;
    cardTypeT getCardType() const;
    rideCountType getRideCount() const;

    Status setID(idType ID);
    Status setCardType(cardTypeT cardT);
    Status setBalance(balanceType bal);
    Status setRideCount(rideCountType rideC);
};

#endif
