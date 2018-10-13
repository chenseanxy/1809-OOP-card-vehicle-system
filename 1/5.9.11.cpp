#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

#define MAX_TABLE_LEN 1024
#define MAX_WORD_LEN 32

string strings[MAX_TABLE_LEN];

void scan(){
    int wordcount=0, i=0;
    bool taken=false;
    char word[MAX_WORD_LEN];
    while(wordcount<MAX_TABLE_LEN && ~scanf("%s",word)){
        taken=false;
        if(string(word)==string("Quit")){break;}

        for(i=0;i<=wordcount;i++){
            if(string(word)==strings[i]){
                taken=true; 
                break;
            }
        }

        if(taken==false){
            strings[wordcount].assign(word);
            wordcount++;
        }
    }
}

int main(){
    scan();
    cout << strings[0] << endl;
    cout << strings[1] << endl;
    cout << strings[2] << endl;
    system("pause");
    return 0;
}
