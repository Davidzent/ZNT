/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on Nov 08, 2018, 11:00 AM
 * Purpose:  
 */

//System Libraries Here
#include <iostream>
#include "Days.h"
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    int day;
    string nam;
    DAY name;
    //Input or initialize values Here
    cout<<"Input month number"<<endl;
    cin>>day;
    cout<<"Input month name"<<endl;
    cin>>nam;
    //Process/Calculations Here
    name.setdat(day);
    name.setname(nam);
    cout<<"Normal Date"<<endl;
    name.prnt();
    cout<<"Increment"<<endl;
    name++;
    name.prnt();
    cout<<"Decrement the incremented date"<<endl;
    name--;
    name.prnt();

    //Exit
    return 0;
}

