#include "card.h"
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
    if(balance < amount){
        cout << "notEnoughBalance" << endl;
        return 1;
    }

    balance-=amount;
    cout << "successfulPayment" << endl;
    return 0;
}
