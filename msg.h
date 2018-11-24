#pragma once

#include "types.h"
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

    //Frontend
    void freeRideSuccess();
    void paymentSuccess();
    void notEnoughBalance();

    //Backend
    void newCard(cIDType cid);
    void deletedCard(cIDType cid);
	void cardExists(cIDType cid);
	void cardAddSuccess(cIDType cid);
	void dbFileReadError(string lastLine);
};
