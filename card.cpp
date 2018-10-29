#include "card.h"
#include "message.h"
#include <iostream>

using namespace std;

card::card(){
	id=0;
	message::qError("New empty card");
}
card::card(idType ID, cardTypeT cardT, balanceType bal, rideCountType rideC){
    id=ID;
    cardType=cardT;
    balance=bal;
    rideCount=rideC;
    //message::newCard(id);
}
card::~card(){
    //message::deletedCard(getID());
}

bool card::operator==(card c)
{
	return getID()==c.getID();
}

balanceType card::getBalance() const{
    return balance;
}
cardTypeT card::getCardType() const{
    return cardType;
}
string card::getCardTypeString() const{
	string cardTypes[3] = { "Student", "Teacher", "Restricted" };
	return cardTypes[getCardType()];
}
rideCountType card::getRideCount() const{
    return rideCount;
}
idType card::getID() const{
    return id;
}

bool card::getFreeRideAvail() const{
    if(getCardType()==2 && getRideCount()<20){
        return true;
    }
    return false;
}

Status card::setID(idType ID){
    id=ID;
    return 0;
}
Status card::setCardType(cardTypeT cardT){
    cardType=cardT;
    return 0;
}
Status card::setBalance(balanceType bal){
    balance=bal;
    return 0;
}
Status card::setRideCount(rideCountType rideC){
    rideCount=rideC;
    return 0;
}

Status card::showSwipeInfo() const{
	cout << "ID: " << getID() << endl
		 << "Card Type:" << getCardTypeString() << endl
		 << "Balance:" << getBalance() << endl
		 << "Ride Counts This Month:" << getRideCount() << endl;
	if (getCardType() == 2 && getRideCount() == 21) {
		cout << "Started charging this time." << endl;
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

    message::freeRideSuccess();
    return 0;
}

Status card::rejectRide(){
    message::qError("Ride rejected");
    return 0;
}

void card::debugPrintCard() const{
    cout 
    << "[DEBUG] -----Printing Card:-----" << endl
    << "[DEBUG] ID: " << getID() << endl
    << "[DEBUG] Card Type: " << getCardType() << endl
    << "[DEBUG] Balance: " << getBalance() << endl
    << "[DEBUG] Ride Count: " << getRideCount() << endl;
}

Status card::charge(balanceType amount){
    if(amount<0){
        message::qError(string("Cannot charge negative amount"));
        return 1;
    }

    if(getBalance() < amount){
        message::notEnoughBalance();
        return 1;
    }

    setBalance(getBalance()-amount);
    message::paymentSuccess();
    return 0;
}

Status card::swipe(){
    if(getID()==0){return -1;}

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
    message::qError("Undefined error: card::swipe()");
    return -1;
}
