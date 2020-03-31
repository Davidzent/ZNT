/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on March 22, 2018, 11:00 AM
 * Purpose:  Hello World Template
 */

//System Libraries Here
#include <iostream>

using namespace std;

//User Libraries Here
#include "Date.h"
//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
string name(int);
//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    int day,month,year;
    Date date;
    //Input or initialize values Here
    cout<<"Enter the date in stile DD MM YYYY"<<endl;
    cin>>date;
    //Process/Calculations Here
    date.nDate();
    //Output Located Here
    cout<<date;
    //Exit
    return 0;
}

