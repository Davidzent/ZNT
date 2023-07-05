/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on February 1, 2021, 12:09 PM
 * Purpose: Write a program that asks the user to enter a number of seconds .
            • There are 86400 seconds in a day. If the number of seconds entered by the user
            is greater than or equal to 86400, the program should display the number of
            days in that many seconds.
            • There are 3600 seconds in an hour. If the number of seconds entered by the
            user is less than 86400 but is greater than or equal to 3600, the program
            should display the number of hours in that many seconds .
            • There are 60 seconds in a minute. If the number of seconds entered by the user
            is less than 3600 but is greater than or equal to 60, the program should display
            the number of minutes in that many seconds .
 */

//System Libraries Here
#include <iostream> 
#include <iomanip>
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions
const int MintoSec=60;
const int HrstoSec=3600;
const int DaytoSec=86400;

//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    int toConv;         //Number to convert and number of seconds
    int days;           //Number of Days
    int hrs;            //Number of Hours
    int min;            //Number of minutes
    int totsec;         //To save the input number
    
    //Input or initialize values Here
    cout<<"Enter a number of seconds to convert"<<endl;
    cin>>toConv;
    totsec=toConv;
    
    //Calculate the answer
    days=toConv/DaytoSec;
    toConv-=days*DaytoSec;
    hrs=toConv/HrstoSec;
    toConv-=hrs*HrstoSec;
    min=toConv/MintoSec;
    toConv-=min*MintoSec;
    
    //Output Located Here
    cout<<"There "<<(days>1?"are ":"is ")<<days<<(days>1?" days ":" day ")<<
                        hrs<<(hrs>1?" hours ":" hour ")<<
                        min<<(min>1?" minutes and ":" minute and ")<<
                        toConv<<(toConv>1?" seconds in ":" second in ")<<
                        totsec<<(totsec>1?" seconds ":" second ")<<endl;
    
    //Exit
    return 0;
}

