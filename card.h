#pragma once

#include "msg.h"
#include "types.h"

class card{
    cTypeT cType;
    cIDType cid;
    cBalanceType cBal;
    cRideCountType cRideCount;

	string cName;
	string cGender;
	string cUnit;

    Status charge(cBalanceType amount=2);
    Status ride();
    Status freeRide();
    Status rejectRide();

public:
    card();
    card(cIDType ID, cTypeT cardT, cBalanceType bal, cRideCountType rideC, string name, string gender, string unit);
    ~card();
    bool operator==(card c);

    Status swipe(vIDType vehNum);

	void debugPrintCard() const;
    Status showSwipeInfo() const;
    Status showInfo() const;

    bool getFreeRideAvail() const;
    cBalanceType getBalance() const;
    cIDType getID() const;
    cTypeT getCardType() const;
	string getCardTypeString() const;
    cRideCountType getRideCount() const;

	string getName() const;
	string getGender() const;
	string getUnit() const;

    Status setID(cIDType ID);
    Status setCardType(cTypeT cardT);
    Status setBalance(cBalanceType bal);
    Status setRideCount(cRideCountType rideC);
};
