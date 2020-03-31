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
#include "Car.h"
//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    int year;
    string make;
    //Input or initialize values Here
    cout<<"Enter the year"<<endl;
    cin>>year;
    cout<<"Enter the make"<<endl;
    cin>>make;
    car info(year,make);
    //Process/Calculations Here
    cout<<"Speed = "<<info.getspeed()<<endl;
    info.aclrt();
    cout<<"Speed = "<<info.getspeed()<<endl;
    info.brake();
    cout<<"Speed = "<<info.getspeed()<<endl;
    //Output Located Here
    

    //Exit
    return 0;
}

