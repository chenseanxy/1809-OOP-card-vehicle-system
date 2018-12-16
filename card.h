/*************************
*	card.h
*	Defines card class and card-type related subclasses
*	Handles card and card-owner related operations
*************************/

#pragma once

#include "msg.h"
#include "types.h"


//	card:
//	Base class to represent generic card
class card {
protected:

	/*******************
	* Member Paramaters	
	********************/

	//	_cType: Indicates card type
	//	0-NullCard, 1-Student, 2-Teacher
	//	3-Restricted, 4-Temporary
	const cTypeT _cType;
	
	//	cid: ID indicating ownership
	//	Normally is studentID
	cIDType cid;

	//	cBal: Balance of card
	cBalanceType cBal;

	//	cRideCount: Ride count of card
	//	Reset every month
	cRideCountType cRideCount;

	//	cName: Card owner's name
	string cName;

	//	cGender: Card owner's gender
	//	M: Male, F: Female
	string cGender;

	//	cUnit: Card owner's unit
	//	Example: Software School
	string cUnit;


	/*******************
	* Member Functions (Protected)
	********************/

	//	charge: Reduce the card balance by amount
	//	param: (double) amount to charge, default is 2
	//	returns: status code: 0-Success
	//			 1-Not enough balance
	//			 2-Param invalid (negative)
	Status charge(cBalanceType amount = 2);

	//	ride: Ride action of the card
	//	action: increment card rideCount
	//			calls vehDB.rideVeh()
	//	param: vehicle ID
	//	returns: vehDB.rideVeh result
	Status ride(vIDType vid);

	//	freeRide: Called if freeRide is granted
	//	action: only shows "freeRide" message
	//	returns: status code: 0-Success
	//			 1-Card cannot freeRide
	Status freeRide();

	//	rejectRide: Called when ride is rejected
	//	action: only shows "rejected" message
	//	returns: status code: 0-Success
	Status rejectRide();

public:


	/*******************
	* Public Member Functions
	* Constructors and Deconstructors
	********************/

	//	card(): creates null card
	card();

	//	card(cardType): creates empty card of cardType
	card(cTypeT cType);

	//	card(bunch of paramaters): decreprated
	//	used to create fully filled cards
	card(cIDType ID, cTypeT cardT, cBalanceType bal, cRideCountType rideC, string name, string gender, string unit);
	
	//	card(dbLine): creates card from one line of dbfile
	//	param: one line of db string
	//	overwritten by subclasses
	card(string dbLine);
	
	//	~card(): deconstructor, nothing special
	~card();

	//	==: identifies if two cards are identical
	//	Only matches card ID
	bool operator==(card c);

	//	swipe(vehNum): exectutes card swipe action from veh
	//	param: vehNum as the executer of swipe action
	//	action: nothing in base class
	virtual Status swipe(vIDType vehNum);

	//	writeCard(): convert cardObj into
	//				 one line of dbString
	//	handles all paramaters defined in base class
	//	format: 
	//	ID cardType balance rideCount name gender unit
	virtual string writeCard();
	
	//	debugPrintCard(): (deprecated) (non-functional)
	//		prints out all info about the card
	void debugPrintCard() const;

	//	showSwipeInfo(): shows ui related info when
	//					 card is swiped
	Status showSwipeInfo() const;

	//	showInfo(): (deprecated) (non-functional)
	//		shows all info about the card
	//		wrapper for debugPrintCard()
	Status showInfo() const;


	/*******************
	* Public Member Functions
	* GET functions
	********************/

	//	getFreeRideAvail: checks if free ride is still
	//					  available for a card
	//	returns: true if free ride is available
	bool getFreeRideAvail() const;

	cBalanceType getBalance() const;

	cIDType getID() const;

	cTypeT getCardType() const;
	
	//	getCardTypeString(): returns the literal name
	//					     of card type
	//	return example: "Student" or "Teacher" ...
	string getCardTypeString() const;

	cRideCountType getRideCount() const;

	string getName() const;

	string getGender() const;

	string getUnit() const;


	/*******************
	* Public Member Functions
	* SET functions
	********************/

	Status setID(cIDType ID);

	Status setBalance(cBalanceType bal);

	Status setRideCount(cRideCountType rideC);
};

//	class studentCard: cardType=1
//	*no free ride
class studentCard : public card {
public:
	studentCard(string dbLine);
	Status swipe(vIDType vehNum);
};


//	class teacherCard: cardType=2
//	*unlimited free ride
class teacherCard : public card {
public:
	teacherCard(string dbLine);
	Status swipe(vIDType vehNum);
};


//	class restrictedCard: cardType=3
//	*limited free ride
class restrictedCard : public card {
public:
	restrictedCard(string dbLine);
	Status swipe(vIDType vehNum);
};


//	class tempCard: cardType=4
//	*expires at expTime
//	*no free ride
class tempCard : public card {

	//	expTime: Expiration time for temp card
	time_t expTime;

public:
	tempCard(string dbLine);
	Status swipe(vIDType vehNum);
	string writeCard();

	//	renewExpTime(): renew the expiration time
	//	param: time_t newExpirationTime
	Status renewExpTime(time_t newExpTime);

	time_t getExpTime();
	
	//	tempCard.isExpired(): returns if the card is expired
	bool isExpired();
};