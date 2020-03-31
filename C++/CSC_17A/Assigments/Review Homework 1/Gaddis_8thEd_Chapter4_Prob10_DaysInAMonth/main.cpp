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

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    int month,year,days;
    float year2;
    bool leapyrs;
    //Input or initialize values Here
    leapyrs=false;
    while(month>12||month<=0){
        cout<<"enter the month in order to find how many days it have ";
        cin>>month;
    }
    cout<<"enter the year ";
    cin>>year;
    year2=year;
    //Process/Calculations Here
    if(year/100==year2/100){
        if(year/400==year2/400)leapyrs=true;
    }
    else if(year/4==year2/4)leapyrs=true;
    if(month==1||month==3||month==5||month==7||month==8||month==10||month==12){
        days=31;
    }
    else if(month==2&&leapyrs==true){
        days=29;
    }
    else if(month==2&&leapyrs==false){
        days=28;
    }
    else days=30;
    //Output Located Here
    cout<<days<<" days"<<endl;

    //Exit
    return 0;
}

