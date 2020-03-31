/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on Nov 08, 2018, 11:00 AM
 * Purpose:  
 */

//System Libraries Here
#include <iostream>

#include "NumDays.h"
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    int hour;
    //Input or initialize values Here
    cout<<"Input the Number of hours"<<endl;
    cin>>hour;
    //Process/Calculations Here
    NumDay day(hour);
    day.prnt();
    NumDay index(hour);
    cout<<"Input the another hour"<<endl;
    cin>>hour;
    NumDay day2(hour);
    cout<<"Addition"<<endl;
    day=index;
    day+day2;
    day.prnt();
    cout<<"Subtraction"<<endl;
    day=index;
    day-day2;
    day.prnt();
    cout<<"increment"<<'\n';
    day=index;
    day++;
    day.prnt();
    cout<<"decrement"<<'\n';
    day=index;
    day--;
    day.prnt();
    //Exit
    return 0;
}

