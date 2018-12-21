/*************************
*	msg.h
*	Defines msg (message) namespace
*	Handles the display of messages and alerts
*************************/

#pragma once

#include "types.h"
#include <Windows.h>
#include <string>

using namespace std;

namespace msg{
    //Core
	void inputMsg(string msg);

    void frontendInfo(string msg);
    void frontendErr(string msg);

    void backendInfo(string infoMsg);
    void backendErr(string errMsg);
    void qError(string errMsg);

	void debug(string debugMsg);

	//Color
	void setColor(WORD wAttributes);
	void resetColor();

    //Frontend
    void freeRideSuccess();
    void paymentSuccess();
    void notEnoughBalance();

	void header(string header);
	void newLine();

    //Backend
    void newCard(cIDType cid);
    void deletedCard(cIDType cid);
	void cardExists(cIDType cid);
	void cardAddSuccess(cIDType cid);
	void dbFileReadError(string lastLine);
};
