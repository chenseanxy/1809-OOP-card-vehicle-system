#pragma once

#include "msg.h"
#include "types.h"

class card{
protected:
    const cTypeT _cType;
    cIDType cid;
    cBalanceType cBal;
    cRideCountType cRideCount;

	string cName;
	string cGender;
	string cUnit;

    Status charge(cBalanceType amount=2);
    Status ride(vIDType vid);
    Status freeRide();
    Status rejectRide();

public:
    card();
	card(cTypeT cType);
    card(cIDType ID, cTypeT cardT, cBalanceType bal, cRideCountType rideC, string name, string gender, string unit);
	card(string dbLine);
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
    Status setBalance(cBalanceType bal);
    Status setRideCount(cRideCountType rideC);
};


class studentCard : public card {
public:
	studentCard(string dbLine);
	Status swipe(vIDType vehNum);

};

class teacherCard : public card {
public:
	teacherCard(string dbLine);
	Status swipe(vIDType vehNum);
};

class restrictedCard : public card {
public:
	restrictedCard(string dbLine);
	Status swipe(vIDType vehNum);

};

class tempCard : public card {
	time_t expTime;

public:
	tempCard(string dbLine);
	Status swipe(vIDType vehNum);

	Status renewExpTime(time_t newExpTime);
	time_t getExpTime();
	bool isExpired();
};