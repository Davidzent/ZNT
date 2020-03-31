/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   savings account.h
 * Author: gabriel
 *
 * Created on December 12, 2018, 12:17 PM
 */

#ifndef SAVINGS_ACCOUNT_H
#define SAVINGS_ACCOUNT_H
#include <iostream>
using namespace std;
class SavingsAccount{
    public:
            SavingsAccount(float);               //Constructor
            void  Transaction(float);            //Procedure
            float Total(float=0,int=0);	         //Savings Procedure
            float TotalRecursive(float=0,int=0);
            void  toString();                    //Output Properties
    private:
            float Withdraw(float);               //Utility Procedure
            float Deposit(float);                //Utility Procedure
            float Balance;                       //Property
            int   FreqWithDraw;                  //Property
            int   FreqDeposit;                   //Property
};

#endif /* SAVINGS_ACCOUNT_H */

