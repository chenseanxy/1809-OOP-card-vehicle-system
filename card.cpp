#include "card.h"
#include "msg.h"
#include <iostream>
#include "main.h"

using namespace std;

card::card(){
	cid=0;
	cType = 0;
	cBal = 0;
	cRideCount = 0;
}

card::card(cIDType ID, cTypeT cardT, cBalanceType bal, cRideCountType rideC, string name, string gender, string unit){
    cid=ID;
    cType=cardT;
    cBal=bal;
    cRideCount=rideC;
	cName = name;
	cGender = gender;
	cUnit = unit;
}

card::~card(){
}

bool card::operator==(card c){
	return getID()==c.getID();
}

cBalanceType card::getBalance() const{
    return cBal;
}
cTypeT card::getCardType() const{
    return cType;
}
string card::getCardTypeString() const{
	string cardTypes[3] = { "Student", "Teacher", "Restricted" };
	return cardTypes[getCardType()];
}
cRideCountType card::getRideCount() const{
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
cIDType card::getID() const{
    return cid;
}

bool card::getFreeRideAvail() const{
    if(getCardType()==2 && getRideCount()<20){
        return true;
    }
    return false;
}

Status card::setID(cIDType ID){
    cid=ID;
    return 0;
}
Status card::setCardType(cTypeT cardT){
    cType=cardT;
    return 0;
}
Status card::setBalance(cBalanceType bal){
    cBal=bal;
    return 0;
}
Status card::setRideCount(cRideCountType rideC){
    cRideCount=rideC;
    return 0;
}

Status card::showSwipeInfo() const{
	cout << "ID: " << getID() << endl
		<< "姓名：" << getName() << endl
		<< "卡类型: " << getCardTypeString() << endl
		<< "余额: " << getBalance() << endl
		<< "乘车次数: " << getRideCount() << endl;

	if (getCardType() == 2 && getRideCount() == 21) {
		msg::frontendInfo("本次开始计费");
	}
	
    return 0;
}
Status card::showInfo() const{
	debugPrintCard();
    return 0;
}

Status card::ride(){
    setRideCount(getRideCount()+1);
    return 0;
}

Status card::freeRide(){
    if(getCardType() != 2){
        return 1;
    }

    msg::freeRideSuccess();
    return 0;
}

Status card::rejectRide(){
    msg::qError("Ride rejected");
    return 0;
}

void card::debugPrintCard() const{
	msg::debug("----Printing card----");
	msg::debug("ID:   " + to_string(getID()));
	msg::debug("Name: " + getName());
	msg::debug("Type: " + to_string(getCardType())+"-"+getCardTypeString());
	msg::debug("Ride Count: " + to_string(getID()));
	msg::debug("Balance:    " + to_string(getBalance()));
	msg::debug("Gender:     " + getGender());
	msg::debug("Unit:       " + getUnit());
	msg::debug("----Card Printed----");
}

Status card::charge(cBalanceType amount){
    if(amount<0){
        msg::qError(string("Cannot charge negative amount"));
        return 1;
    }

    if(getBalance() < amount){
        msg::notEnoughBalance();
        return 1;
    }

    setBalance(getBalance()-amount);
    msg::paymentSuccess();
    return 0;
}

Status card::swipe(vIDType vehNum){
    if(getID()==0){return -1;}
	if (vdb.find(vehNum).isFull()) {
		rejectRide();
		msg::frontendErr("Vehicle is full");
		return 1;
	}

    switch(getCardType()){
        
        //Student
        case 0:{
            Status chargeResult=charge();
            if(chargeResult==0){
                ride();
                showSwipeInfo();
            }
            else{
                rejectRide();
            }
            return 0;
            break;
        }
        //Teacher
        case 1:
        ride();
        showSwipeInfo();
        return 0;
        break;

        //Restricted
        case 2:{
            if(getFreeRideAvail() == true){
                freeRide();
                ride();
                showSwipeInfo();
            }
            else{
                Status chargeResult=charge();
                if(chargeResult==0){
                    ride();
                    showSwipeInfo();
                }
                else{
                    rejectRide();
                }
            }
            return 0;
            break;
        }

    }
    msg::qError("Undefined error: card::swipe()");
    return -1;
}
