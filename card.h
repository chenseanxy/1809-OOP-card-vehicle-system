#ifndef CARD_H
#define CARD_H

typedef unsigned int idType;
typedef double balanceType;
typedef unsigned short cardTypeT;
typedef unsigned int rideCountType;
typedef int Status;

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
    Status swipe();

    Status showSwipeInfo() const;
    Status showInfo() const;

    bool getFreeRideAvail() const;
    balanceType getBalance() const;
    idType getID() const;
    cardTypeT getCardType() const;
    rideCountType getRideCount() const;
};

#endif
