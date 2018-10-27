#ifndef MESSAGE_H
#define MESSAGE_H

#include "types.h"
#include <string>

using namespace std;

namespace message{
    //Core
    void frontendInfo(string msg);
    void frontendErr(string msg);

    void backendInfo(string infoMsg);
    void backendErr(string errMsg);
    void qError(string errMsg);

    //Frontend
    void freeRideSuccess();
    void paymentSuccess();
    void notEnoughBalance();
    void cardNotFound();

    //Backend
    void newCard(idType id);
    void deletedCard(idType id);
    void cardExists();
    void cardAddSuccess();
};


#endif // MESSAGE_H
