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
#include <fstream>
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
    ifstream in;
    ofstream out;
    int toConv;         //Number to convert and number of seconds
    float days;           //Number of Days
    float hrs;            //Number of Hours
    float min;            //Number of minutes
    
    //Input or initialize values Here
    in.open("in.txt");
    out.open("out.txt");
    out<<"Enter a number of seconds to convert"<<endl;
    in>>toConv;
    
    //Calculate the answer
    
    //Output Located Here
    out<<fixed<<showpoint<<setprecision(2);
    if(toConv>=DaytoSec){
        days=toConv/(float)DaytoSec;
        out<<"There "<<(days>1?"are ":"is ")<<days<<(days>1?" days":" day");
    }else if(toConv<DaytoSec&&toConv>=HrstoSec){
        hrs=toConv/(float)HrstoSec;
        out<<"There "<<(hrs>1?"are ":"is ")<<hrs<<(hrs>1?" hours":" hour");
                
    }else if(toConv<HrstoSec&&toConv>=MintoSec){
        min=toConv/(float)MintoSec;
        out<<"There "<<(min>1?"are ":"is ")<<min<<(min>1?" minutes and":" minute and");
                
    }else{
        out<<"There "<<(toConv>1?"are ":"is ")<<toConv<<(toConv>1?" seconds in":" second in");
        
    }
    out<<" in "<<toConv<<(toConv>1?" seconds ":" second ")<<endl;   

    //Exit
    in.close();
    out.close();
    return 0;
}

