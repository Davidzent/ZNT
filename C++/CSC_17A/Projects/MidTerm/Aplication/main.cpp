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
#include "Account.h"
//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
Acount *filinfo();
void prtinfo(Acount *);
//Program Execution Begins Here
int main(int argc, char** argv) {
    //get account information
    Acount *acc=filinfo();
    //output account information
    prtinfo(acc);
    //Exit
    return 0;
}
Acount *filinfo(){
    Acount *acount;
    cout<<"enter your account name "<<endl;
    cin>>acount->name;
    /*cout<<"enter your address "<<endl;
    cin>>acount->adres;*/
    cout<<"enter your account number "<<endl;
    cin>>acount->nAccnt;
    if(acount->nAccnt<10000||acount->nAccnt>99999)exit(EXIT_FAILURE);
    cout<<"enter your balance this month"<<endl;
    cin>>acount->balance;
    cout<<"enter your total amount of all check written this month"<<endl;
    cin>>acount->nCheck;
    cout<<"enter the total value of deposits this month"<<endl;
    cin>>acount->nDepsit;
    acount->nwblnc=acount->balance+acount->nDepsit-acount->nCheck;;
    return acount;
}
void prtinfo(Acount *acount){
    cout<<"Account name        -> "<<acount->name<<endl;
    //cout<<"User Address        -> "<<acount->adres<<endl;
    cout<<"User Account number -> "<<acount->nAccnt<<endl;
    cout<<"User Balance        -> $"<<acount->balance<<endl;
    cout<<"Total Expenses      -> $"<<acount->nCheck<<endl;
    cout<<"Total Deposits      -> $" <<acount->nDepsit<<endl;
    cout<<"Your new balance is -> $"<<acount->nDepsit<<endl;
    if(acount->nwblnc<0){
        acount->nwblnc-=20;
        cout<<"You have overdrawn"<<endl;
        cout<<"There have been charged an additional $20 fee"<<endl;
        cout<<"This is your new balance"<<acount->nwblnc;
    }
}
