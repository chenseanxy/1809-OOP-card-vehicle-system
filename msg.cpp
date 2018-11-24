#include "msg.h"
#include <iostream>

using namespace std;

void msg::inputMsg(string msg) {
	cout << msg << ": ";
}

//Frontend Core
void msg::frontendInfo(string msg){
    cout << "[INFO] " << msg << endl;
}
void msg::frontendErr(string msg){
    cout << "[ERR]  " << msg << endl;
}


//Backend Core
void msg::backendInfo(string infoMsg){
    cout << "       [INFO] " << infoMsg << endl;
}
void msg::backendErr(string errMsg){
    cout << "       [ERR]  " << errMsg << endl;
}
void msg::qError(string errMsg){
    backendErr(errMsg);
}

void msg::debug(string debugMsg) {
	cout << "       [DEBUG]" << debugMsg << endl;
}

//Frontend
void msg::freeRideSuccess(){
    frontendInfo("Enjoy your free ride!");
}
void msg::paymentSuccess(){
    frontendInfo("Payment successful!");
}
void msg::notEnoughBalance(){
    frontendInfo("Not enough cBal!");
}

//Backend
void msg::cardExists(cIDType cid){
    backendErr("Card already exists " + to_string(cid));
}
void msg::cardAddSuccess(cIDType cid){
    backendInfo("Sucessfully added card " + to_string(cid));
}

void msg::dbFileReadError(string lastLine){
	backendErr("dbFile read error, last line: " + lastLine);
}
void msg::newCard(cIDType cid){
    backendInfo("New card added: "+std::to_string(cid));
}
void msg::deletedCard(cIDType cid){
    backendInfo("Deleted card: "+ std::to_string(cid));
}


