#include "message.h"
#include <iostream>

using namespace std;

//Frontend Core
void message::frontendInfo(string msg){
    cout << "[INFO] " << msg << endl;
}
void message::frontendErr(string msg){
    cout << "[ERR]  " << msg << endl;
}


//Backend Core
void message::backendInfo(string infoMsg){
    cout << "       [INFO] " << infoMsg << endl;
}
void message::backendErr(string errMsg){
    cout << "       [ERR]  " << errMsg << endl;
}
void message::qError(string errMsg){
    backendErr(errMsg);
}

void message::debug(string debugMsg) {
	cout << "       [DEBUG]" << debugMsg << endl;
}

//Frontend
void message::freeRideSuccess(){
    frontendInfo("Enjoy your free ride!");
}
void message::paymentSuccess(){
    frontendInfo("Payment successful!");
}
void message::notEnoughBalance(){
    frontendInfo("Not enough balance!");
}
void message::cardNotFound(){
    frontendInfo("Invalid card!");
}

void message::cardCantRead()
{
	frontendErr("Cannot read card, try again?");
}

//Backend
void message::cardExists(idType id){
    backendErr("Card already exists " + to_string(id));
}
void message::cardAddSuccess(idType id){
    backendInfo("Sucessfully added card " + to_string(id));
}
void message::dbFileOpenError(){
	backendErr("Can't open dbFile");
}
void message::dbFileReadError(string lastLine){
	backendErr("dbFile read error, last line: " + lastLine);
}
void message::newCard(idType id){
    backendInfo("New card added: "+std::to_string(id));
}
void message::deletedCard(idType id){
    backendInfo("Deleted card: "+ std::to_string(id));
}


