/* 
 * File:   SavingsAccount.cpp
 * Author: Guijosa David
 *
 * Created on December 12, 2018, 12:17 PM
 */
#include <cmath>
#include "savings account.h"

SavingsAccount::SavingsAccount(float balance){
    this->Balance=0;
    if(balance>0)this->Balance=balance;
    this->FreqDeposit=0;
    this->FreqWithDraw=0;
}            
void  SavingsAccount::Transaction(float money){
    if(money>0)Balance+=money,this->FreqDeposit++;
    else if(Balance>money)Balance-=money,this->FreqWithDraw++;
    else cout<<"The amount exceeds your balance"<<endl;
}
float SavingsAccount::Total(float savint,int time){
    float x=1;
    for(int i=0;i<time;i++){
        x*=(1+savint);
    }
    return Balance*x;
}
float SavingsAccount::TotalRecursive(float savint,int time){
    return Balance*pow((1+savint),time);
}
void  SavingsAccount::toString(){
    cout<<"Deposit Frequence "<<this->FreqDeposit<<endl;
    cout<<"WithDraw Frequence "<<this->FreqWithDraw<<endl;
    cout<<"Balance "<<this->Balance<<endl;
    
}
