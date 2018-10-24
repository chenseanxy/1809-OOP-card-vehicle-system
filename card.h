#ifndef CARD_H
#define CARD_H

#include "types.h"

class card{
    cardTypeT cardType;
    idType id;
    balanceType balance;
    rideCountType rideCount;

    Status charge(balanceType amount=2);
    Status ride();
    Status freeRide();

    public:
    card();
    ~card();
    bool operator==(card c);

    Status swipe(card c);

    Status showSwipeInfo() const;
    Status showInfo() const;

    bool getFreeRideAvail() const;
    balanceType getBalance() const;
    idType getID() const;
    cardTypeT getCardType() const;
    rideCountType getRideCount() const;
};

#endif
