#include <iostream>
#include <stdlib.h>

using namespace std;

int main(){
    enum customBool {f,t};
    enum singleChoice {a,b,c,d};

    cout << "Size of:\n"
    << "  bool:"   << sizeof(bool)
    << "  char:"   << sizeof(char)
    << "  int:"    << sizeof(int)
    << "  double:" << sizeof(double)
    << "\n"

    << "  int*:"   << sizeof(int*)
    << "  char*:"  << sizeof(char*)
    << "\n"

    << "  customBool:" << sizeof(customBool)    
    << "  singleChoice:" << sizeof(singleChoice)
    << "\n";

    return 0;
}