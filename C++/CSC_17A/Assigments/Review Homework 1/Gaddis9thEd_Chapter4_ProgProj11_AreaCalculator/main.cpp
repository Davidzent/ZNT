/* 
 * File:   main.cpp
 * Author: Guijosa. David
 * Created on Sep 6, 2018, 10:20 AM
 * Purpose:  
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
    int day,year,date,month; 
    //Output Located Here
    cout<<"Input a day from 1-31 -->"<<endl;
    cin>>day;
    cout<<"Input a month in numeric form -->"<<endl;
    cin>>month;
    cout<<"Input the last two digits of a year -->"<<endl;
    cin>>year;

    //calculations 
    date=day*month;
    
    //Output Located Here
    if(day>31)cout<<"please enter a valid day"<<endl;
    if(month>12)cout<<"please enter a valid month"<<endl;
    if(year>99)cout<<"please enter a valid year"<<endl;
    if(month<=12,year<=99,day<=31)cout<<"The entered date is"<<endl,
       cout<<day<<"/"<<month<<"/"<<year<<endl;
    if(date==year)cout<<"The date is magic"<<endl;
    else cout<<"The date is not magic"<<endl;
    //Exit
    return 0;
}
