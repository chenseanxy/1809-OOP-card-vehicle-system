#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct month{
    char* name;
    int days;
}month;

char names[12][10]={{"January"},{"February"},{"March"},{"April"},{"May"},{"June"},{"July"},{"August"},{"September"},{"October"},{"November"},{"December"}};

int days(int month){
    switch(month){
        case 2: 
        return 28; break;

        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
        return 31; break;

        case 4: case 6: case 9: case 11:
        return 30; break;
    }
    return -1;
}

void table1_output(int day, char* name){
    cout << name << " " << day << endl;
}
void table1(){
    int i, t1_days[12];
    for(i=0;i<12;i++){
        t1_days[i]=days(i+1);
    }
    for(i=0;i<12;i++){
        table1_output(t1_days[i],names[i]);
    }
}

void table2_output(month mon){
    cout << mon.name << " " << mon.days << endl;
}

void table2(){
    int i;
    month table2[12];
    for(i=1;i<13;i++){
        table2[i-1].name=names[i-1];
        table2[i-1].days=days(i);
    }
    for(i=0;i<12;i++){
        table2_output(table2[i]);
    }
}

int main(){
    table1();
    cout << endl;
    table2();
    system("pause");
    return 0;
}
