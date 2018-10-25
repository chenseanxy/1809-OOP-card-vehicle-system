#include "card.h"
#include "message.h"
#include <iostream>

using namespace std;

card::card(){
    cout << "New Card" << endl;
}
card::~card(){
    cout << "Deleting Card "<< id << endl;    
}

balanceType card::getBalance() const{
    return balance;
}
cardTypeT card::getCardType() const{
    return cardType;
}
rideCountType card::getRideCount() const{
    return rideCount;
}
idType card::getID() const{
    return id;
}

bool card::getFreeRideAvail() const{
    if(rideCount<20){
        return true;
    }
    return false;
}

Status card::showSwipeInfo() const{
    printf("%ud %.2lf %ud\n", id, balance, rideCount);
    cout << "Card Swipe Info should be shown here\n";
    return 0;
}
Status card::showInfo() const{
    printf("%ud %.2lf %ud\n", id, balance, rideCount);
    cout << "More Info should be shown here\n";
    return 0;
}

Status card::ride(){
    rideCount++;
    return 0;
}

Status card::freeRide(){
    if(cardType != 2){
        return 1;
    }

    cout << "successfulFreeRide" <<endl;
    return 0;
}

Status card::charge(balanceType amount){
    if(amount<0){
        message::qError(string("Cannot charge negative"));
        return 1;
    }

    if(balance < amount){
        message::notEnoughBalance();
        return 1;
    }

    balance-=amount;
    message::paymentSuccess();
    return 0;
}

Status card::swipe(){
    if(id==0){return -1;}

    switch(cardType){
        
        //Student
        case 0:
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

        //Teacher
        case 1:
        ride();
        showSwipeInfo();
        return 0;
        break;

        //Restricted
        case 2:
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

        message::qError("Undefined error: card::swipe()");
        return -1;
    }
}
