#include "card.h"
#include "msg.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "main.h"

using namespace std;

card::card()
	:_cType(0) {
	cid = 0;
	cBal = 0;
	cRideCount = 0;
}

card::card(cTypeT cardType)
	:_cType(cardType) {

}

card::card(cIDType ID, cTypeT cardT, cBalanceType bal, cRideCountType rideC, string name, string gender, string unit)
	: _cType(cardT) {
	cid = ID;
	cBal = bal;
	cRideCount = rideC;
	cName = name;
	cGender = gender;
	cUnit = unit;
}

card::~card() {
}

bool card::operator==(card c) {
	return getID() == c.getID();
}

Status card::swipe(vIDType vehNum) {
	msg::backendErr("Base class: cannot swipe");
	return 1;
}

cBalanceType card::getBalance() const {
	return cBal;
}
cTypeT card::getCardType() const {
	return _cType;
}
string card::getCardTypeString() const {
	string cardTypes[5] = {"None", "Student", "Teacher", "Restricted", "Temporary" };
	return cardTypes[getCardType()];
}
cRideCountType card::getRideCount() const {
	return cRideCount;
}
string card::getName() const {
	return cName;
}
string card::getGender() const {
	return cGender;
}
string card::getUnit() const {
	return cUnit;
}
cIDType card::getID() const {
	return cid;
}

bool card::getFreeRideAvail() const {
	if (getCardType() == 2 && getRideCount() < 20) {
		return true;
	}
	return false;
}

Status card::setID(cIDType ID) {
	cid = ID;
	return 0;
}

Status card::setBalance(cBalanceType bal) {
	cBal = bal;
	return 0;
}
Status card::setRideCount(cRideCountType rideC) {
	cRideCount = rideC;
	return 0;
}

Status card::showSwipeInfo() const {
	cout << "	ID: " << getID() << endl
		<< "	Name：" << getName() << endl

		<< "	Type: " << getCardTypeString() << endl
		<< "	Bal: " << getBalance() << endl
		<< "	RideC: " << getRideCount() << endl;

	return 0;
}
Status card::showInfo() const {
	msg::setColor(10);
	cout << "--------------------CARD INFO--------------------" << endl
		<< "ID: " << getID() << endl
		<< "Name：" << getName() << endl
		<< "Gender: " << getGender() << endl
		<< "Unit:" << getUnit() << endl
		<< "Type: " << getCardTypeString() << endl
		<< "Bal: " << getBalance() << endl
		<< "Ride Count: " << getRideCount() << endl;
	msg::resetColor();

	return 0;
}

Status card::ride(vIDType vid) {
	setRideCount(getRideCount() + 1);
	return vdb.rideVeh(vid);
}

Status card::freeRide() {
	if (getCardType() != 2) {
		return 1;
	}

	msg::frontendInfo("Enjoy your free ride!");
	return 0;
}

Status card::rejectRide() {
	msg::frontendErr("Ride rejected");
	return 0;
}

string card::writeCard() const {
	stringstream ss;
	ss << getCardType() << " "
		<< getID() << " "
		<< getBalance() << " "
		<< getRideCount() << " "
		<< getName() << " "
		<< getGender() << " "
		<< getUnit();
	string output;
	getline(ss, output);
	return output;
}

void card::debugPrintCard() const {
	msg::debug("----Printing card----");
	msg::debug("ID:   " + to_string(getID()));
	msg::debug("Name: " + getName());
	msg::debug("Type: " + to_string(getCardType()) + "-" + getCardTypeString());
	msg::debug("Ride Count: " + to_string(getID()));
	msg::debug("Balance:    " + to_string(getBalance()));
	msg::debug("Gender:     " + getGender());
	msg::debug("Unit:       " + getUnit());
	msg::debug("----Card Printed----");
}

Status card::charge(cBalanceType amount) {
	if (amount < 0) {
		msg::backendErr(string("Cannot charge negative amount"));
		return 2;
	}

	if (getBalance() < amount) {
		msg::notEnoughBalance();
		return 1;
	}

	setBalance(getBalance() - amount);
	msg::frontendInfo("Payment successful!");
	return 0;
}

inline Status preSwipeCheck(card c, vIDType vid) {
	if (c.getID() == 0) {
		msg::frontendErr("Cant swipe empty card");
		return -1;
	}
	if (vdb.isVehFull(vid)) {
		msg::frontendErr("Vehicle full");
		return 1;
	}
	return 0;
}


studentCard::studentCard(string dbLine)
	: card(1) {
	stringstream ss;
	ss << dbLine;
	ss >> cid >> cBal >> cRideCount >> cName >> cGender >> cUnit;
}

Status studentCard::swipe(vIDType vid) {
	if (preSwipeCheck(*this, vid)) {
		rejectRide();
		return 1;
	}

	//	charge the card of default amount
	Status chargeResult = charge();
	if (chargeResult == 0) {
		//	charge is successful
		ride(vid);
		showSwipeInfo();
	}
	else {
		rejectRide();
		return 1;
	}
	return 0;
}


teacherCard::teacherCard(string dbLine)
	: card(2) {
	stringstream ss;
	ss << dbLine;
	ss >> cid >> cBal >> cRideCount >> cName >> cGender >> cUnit;
}

Status teacherCard::swipe(vIDType vid) {
	if (preSwipeCheck(*this, vid)) {
		rejectRide();
		return 1;
	}

	ride(vid);
	showSwipeInfo();
	return 0;
}

restrictedCard::restrictedCard(string dbLine)
	: card(3) {
	stringstream ss;
	ss << dbLine;
	ss >> cid >> cBal >> cRideCount >> cName >> cGender >> cUnit;
}

Status restrictedCard::swipe(vIDType vid) {
	if (preSwipeCheck(*this, vid)) {
		rejectRide();
		return 1;
	}
	
	if (getID() == 0) { return -1; }

	if (getFreeRideAvail() == true) {
		freeRide();
		ride(vid);
		showSwipeInfo();
	}
	else {
		Status chargeResult = charge();
		if (chargeResult == 0) {
			ride(vid);
			showSwipeInfo();
		}
		else {
			rejectRide();
		}
	}
	return 0;
}

Status restrictedCard::showSwipeInfo() const {
	card::showSwipeInfo();

	if (getRideCount() == 21) {
		msg::frontendInfo("Started charging");
	}
	return 0;
}

tempCard::tempCard(string dbLine)
	:card(4) {
	stringstream ss;
	ss << dbLine;
	ss >> cid >> cBal >> cRideCount >> cName >> cGender >> cUnit >> expTime;
}

Status tempCard::swipe(vIDType vehNum) {
	if (preSwipeCheck(*this, vehNum)) {
		rejectRide();
		return 1;
	}

	//	charge the card of default amount
	Status chargeResult = charge();
	if (isExpired()) {
		msg::frontendErr("本卡已失效！有效期至 " + getExpTimeStr());
		rejectRide();
		return 1;
	}
	else if (chargeResult == 0) {
		//	charge is successful
		ride(vehNum);
		showSwipeInfo();
	}
	else {
		rejectRide();
		return 1;
	}
	return 0;
}

Status tempCard::showSwipeInfo() const {
	card::showSwipeInfo();
	cout << "有效期: " << getExpTimeStr() << endl;
	return 0;
}

Status tempCard::showInfo() const {
	card::showInfo();
	msg::setColor(9);
	cout << "Expire Time: " << getExpTime() << endl;
	msg::resetColor();
	return 0;
}

string tempCard::writeCard() const {
	stringstream ss;
	ss << card::writeCard() << " "
		<< getExpTime();
	string output;
	getline(ss, output);
	return output;
}

Status tempCard::renewExpTime(time_t newExpTime) {
	if (newExpTime < expTime) {
		msg::backendErr("Cannot renew expTime backwards");
		return 1;
	}
	else {
		expTime = newExpTime;
	}
	
	return 0;
}

time_t tempCard::getExpTime() const {
	return expTime;
}

string tempCard::getExpTimeStr() const {
	time_t exp = getExpTime();
	stringstream ss;
	ss << std::put_time(localtime(&exp), "%Y-%m-%d");
	return ss.str();
}

bool tempCard::isExpired() const {
	return time(0) > getExpTime();
}
