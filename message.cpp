#include "message.h"
#include <iostream>

using namespace std;

//Frontend Core
void message::frontendInfo(string msg){
    cout << "----- [INFO] " << msg << endl;
}
void message::frontendErr(string msg){
    cout << "----- [ERR]  " << msg << endl;
}


//Backend Core
void message::backendInfo(string infoMsg){
    cout << "[INFO] " << infoMsg << endl;
}
void message::backendErr(string errMsg){
    cout << "[ERR]  " << errMsg << endl;
}
void message::qError(string errMsg){
    backendErr(errMsg);
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

//Backend
void message::cardExists(){
    backendErr("Card already exists");
}
void message::cardAddSuccess(){
    backendInfo("Sucessfully added card");
}
void message::newCard(idType id){
    backendInfo("New card added: "+(unsigned int)id);
}
void message::deletedCard(idType id){
    backendInfo("Deleted card: "+(unsigned int)id);
}

