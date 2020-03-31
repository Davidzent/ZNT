/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on April 3rd, 2019, 12:36 PM
 * Purpose:  Recursion
 */

//System Libraries
#include <iostream>  //Input/Output Library
#include <cmath>
#include <ctime>
using namespace std;

//User Libraries

//Global Constants, no Global Variables are allowed
//Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc...

//Function Prototypes
float fibRec(int,int&);           //Fibonacci Recursive
float fib(int,int&);              //Fibonacci - Loop

//Execution Begins Here!
int main(int argc, char** argv) {
    //Declare Variables
    int nf;
    int op=0,opn=0;
    //Initialize or input i.e. set variable values
    nf=10;
    
    //Perform the Recursive Call
    for(int j=0;j<=nf;j++){
        cout<<fibRec(j,op)<<" ";
    }
    cout<<endl;
    for(int j=0;j<=nf;j++){
        cout<<fib(j,opn)<<" ";
    }
    cout<<endl;
    cout<<"non recursive O() = "<<opn<<endl;
    cout<<"recursive O() = "<<op<<endl;
    //Exit stage right or left!
    return 0;
}
float fibRec(int n,int &op){
    //Base Case
    if(n==0){
        op++;
        return n;
    }
    if(n==1){
        op+=2;
        return n;
    }
    op+=4;
    //Recursive case
    return fibRec(n-1,op)+fibRec(n-2,op);
}

float fib(int n,int &op){
    //Base Case
    if(n==0){op++;return n;}
    if(n==1){op+=2;return n;}
    //Non Recursive
    int cnt=2,fnm1=1,fnm2=0,fn;
    op+=5;
    do{
        fn=fnm1+fnm2;
        fnm2=fnm1;
        fnm1=fn;
        op+=7;
    }while(++cnt<=n);
    return fn;
}