/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on March 22, 2018, 11:00 AM
 * Purpose:  Hello World Template
 */

//System Libraries Here
#include <iostream>
#include <fstream>
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    unsigned char x=50;
    unsigned char y=0b11001100;
    unsigned short z=y*x;
    z>>=10;
    //Input or initialize values Here
    cout<<"Binary shifted fraction"<<endl;
    cout<<static_cast<int>(x)<<"*"<<static_cast<int>(y)<<"="<<z<<endl;
    //Process/Calculations Here

    //Output Located Here
    

    //Exit
    return 0;
}

/*
 * 1/3*16=16/3=5+1/3
 * 1/3=0.555555 in hex
 * 0.555555=0.01010101 in binary
 * 0.01x2^0
 * 10101010x2^-9
 * AAx16^-9 in hex
 * 
 * 1/5*16=16/5=3+1/5
 * 0.00110011 to inf
 * 11001100x2-10
 * 
 */