#include "message.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main(){
    system("chcp 65001");

    message::cardExists();
    message::cardAddSuccess();

    message::freeRideSuccess();
    message::paymentSuccess();
    message::notEnoughBalance();
    message::cardNotFound();

    message::qError("qError Test");
    system("pause");
    return 0;
}