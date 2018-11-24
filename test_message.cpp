#include "msg.h"
#include <iostream>

using namespace std;

int mainTestMessage(){
//    msg::cardExists();
//    msg::cardAddSuccess();

	msg::freeRideSuccess();
	msg::paymentSuccess();
	msg::notEnoughBalance();
	msg::cardNotFound();

    msg::qError("qError Test");
    return 0;
}