#pragma once

#include "types.h"
#include <string>

using namespace std;

namespace message{
    //Core
	void ui_input(string msg);

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
    void cardNotFound();
	void cardCantRead();

    //Backend
    void newCard(idType id);
    void deletedCard(idType id);
	void cardExists(idType id);
	void cardAddSuccess(idType id);
	void dbFileOpenError();
	void dbFileReadError(string lastLine);
};
