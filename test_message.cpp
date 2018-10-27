#include "message.h"
#include <iostream>

using namespace std;

int main(){
    message::cardExists();
    message::cardAddSuccess();

	message::freeRideSuccess();
	message::paymentSuccess();
	message::notEnoughBalance();
	message::cardNotFound();

    message::qError("qError Test");
    return 0;
}