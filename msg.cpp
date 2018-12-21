#include "msg.h"
#include <iostream>

using namespace std;

void msg::inputMsg(string msg) {
	setColor(FOREGROUND_INTENSITY);
	cout << msg << ": ";
	resetColor();
}

//Frontend Core
void msg::frontendInfo(string msg){
	setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "[INFO] " << msg << endl;
	resetColor();
}
void msg::frontendErr(string msg){
	setColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
    cout << "[ERR]  " << msg << endl;
	resetColor();
}


//Backend Core
void msg::backendInfo(string infoMsg){
	setColor(FOREGROUND_RED | FOREGROUND_GREEN);
    cout << "       [INFO] " << infoMsg << endl;
	resetColor();
}
void msg::backendErr(string errMsg){
	setColor(FOREGROUND_RED);
    cout << "       [ERR]  " << errMsg << endl;
	resetColor();
}
void msg::qError(string errMsg){
    backendErr(errMsg);
}

void msg::debug(string debugMsg) {
	cout << "       [DEBUG]" << debugMsg << endl;
}

void msg::setColor(WORD wAttributes) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsole == INVALID_HANDLE_VALUE) return;
	SetConsoleTextAttribute(hConsole, wAttributes);
}

void msg::resetColor() {
	setColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}



//Frontend
void msg::freeRideSuccess(){
    frontendInfo("Enjoy your free ride!");
}
void msg::paymentSuccess(){
}
void msg::notEnoughBalance(){
    frontendInfo("Not enough cBal!");
}

void msg::header(string header) {
	setColor(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	cout << header << endl;
	resetColor();
}

void msg::newLine() {
	cout << endl;
}

//Backend
void msg::cardExists(cIDType cid){
    backendErr("Card already exists " + to_string(cid));
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


