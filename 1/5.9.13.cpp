#include <iostream>
#include <stdlib.h>

using namespace std;

typedef struct Date{
    int year;
    int month;
    int day;
}Date;

Date scanDate(){
    Date d;
    scanf("%d/%d/%d", &d.year, &d.month, &d.day);
    return d;
}

void printDate(Date d){
    cout << d.year << "/" << d.month << "/" << d.day << endl;
}

Date initDate(int year, int month, int day){
    Date d={year,month,day};
    return d;
}

int main(){
    printDate(scanDate());
    system("pause");
    return 0;
}
