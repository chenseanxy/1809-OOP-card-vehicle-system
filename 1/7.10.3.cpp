#include <iostream>
#include <stdlib.h>

using namespace std;

int main(int argc, char* argv[]){
    int i;
    for(i=0;i<argc;i++){
        cout << "Hello, " << argv[i] << "!\n";
    }
    system("pause");
    return 0;
}