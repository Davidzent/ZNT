/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on March 22, 2018, 11:00 AM
 * Purpose:  Hello World Template
 */

//System Libraries Here
#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;

//User Libraries Here
#include "GrossPay.h"
//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
void *filinfo(grPay *,int);
void calpay(grPay *,int);
void prnStrc(grPay *,int,string[]);
void getnum(grPay *,string[],int);
//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    int nEmp;
    grPay *array;
    //ask for number of employees
    cout<<"Enter number of employees"<<endl;
    cin>>nEmp;
    string nmNme[nEmp];
    array=new grPay[nEmp];
    //fill the array
    for(int i=0;i<nEmp;i++){
        filinfo(array,i);
        calpay(array,i);
        getnum(array,nmNme,i);
    }
    //Output information
    for(int i=0;i<nEmp;i++){
        prnStrc(array,i,nmNme);
    }
    delete []array;
    //Exit
    return 0;
}
void *filinfo(grPay *info,int i){
    cout<<"Enter the Employee name"<<endl;
    cin>>info[i].name;
    cout<<"Enter the Employee hours worked"<<endl;
    cin>>info[i].hrswrk;
    cout<<"Enter the Employee rate pay"<<endl;
    cin>>info[i].rtPay;
}
void calpay(grPay *info,int i){
    info[i].grspay=info[i].hrswrk*info[i].rtPay;
}
void prnStrc(grPay *group,int rows,string numNme[]){
    for(int row=0;row<=rows;row++){
        cout<<fixed<<showpoint<<setprecision(2);
        cout<<"Company"<<endl;
        cout<<"Address"<<endl;
        cout<<"Name: "<<group[row].name<<"      ";
        cout<<"Amount:"<<group[row].grspay<<endl;
        cout<<"Amount: "<<numNme[row]<<endl;
        cout<<"Signature Line _____________________________"<<endl;
    }
}
void getnum(grPay *strct,string name[],int i){
    int n;
    float num=strct[i].grspay;
    n=strct[i].grspay/100;
    num-=n*100;
    if(n>=1&&n<=9){
        switch (n){
            case 9:name[i]+="NIne Hundred ";break;
            case 8:name[i]+="Eight Hundred ";break;
            case 7:name[i]+="Seven Hundred ";break;
            case 6:name[i]+="Six Hundred ";break;
            case 5:name[i]+="Five Hundred ";break;
            case 4:name[i]+="Four Hundred ";break;
            case 3:name[i]+="Three Hundred ";break;
            case 2:name[i]+="Two Hundred ";break;
            case 1:name[i]+="One Hundred ";break;
        }
    }
    n=num/10;
    if(n==1){
        num-=n*10;
        n=num;
        switch (n){
            case 9:name[i]+="NIneteen ";break;
            case 8:name[i]+="Eighteen ";break;
            case 7:name[i]+="Seventeen ";break;
            case 6:name[i]+="Sixteen ";break;
            case 5:name[i]+="Fifteen ";break;
            case 4:name[i]+="Fourteen ";break;
            case 3:name[i]+="Thirteen ";break;
            case 2:name[i]+="Twelve ";break;
            case 1:name[i]+="Eleven ";break;
        }
    }
    else if(n>1&&n<=9){
        switch (n){
            case 9:name[i]+="NInety ";break;
            case 8:name[i]+="Eighty ";break;
            case 7:name[i]+="Seventy ";break;
            case 6:name[i]+="Sixty ";break;
            case 5:name[i]+="Fifty ";break;
            case 4:name[i]+="Forty ";break;
            case 3:name[i]+="Thirty ";break;
            case 2:name[i]+="Twenty ";break;
        }
        num-=n*10;
        n=num;
        if(n>0&&n<9){
             switch (n){
                case 9:name[i]+="NIne ";break;
                case 8:name[i]+="Eight ";break;
                case 7:name[i]+="Seven ";break;
                case 6:name[i]+="Six ";break;
                case 5:name[i]+="Five ";break;
                case 4:name[i]+="Four ";break;
                case 3:name[i]+="Three ";break;
                case 2:name[i]+="Two ";break;
                case 1:name[i]+="One ";break;
             }
        }
    }
    num-=n;
    n=num*10;
    if(n==1){
        name[i]+="and ";
        num-=n/10;
        n=num*100;
        switch (n){
            case 9:name[i]+="NIneteen ";break;
            case 8:name[i]+="Eighteen ";break;
            case 7:name[i]+="Seventeen ";break;
            case 6:name[i]+="Sixteen ";break;
            case 5:name[i]+="Fifteen ";break;
            case 4:name[i]+="Fourteen ";break;
            case 3:name[i]+="Thirteen ";break;
            case 2:name[i]+="Twelve ";break;
            case 1:name[i]+="Eleven ";break;
        }
        name[i]+=" Cents ";
    }
    else if(n>1&&n<=9){
        name[i]+=" and ";
        switch (n){
            case 9:name[i]+="NInety ";break;
            case 8:name[i]+="Eighty ";break;
            case 7:name[i]+="Seventy ";break;
            case 6:name[i]+="Sixty ";break;
            case 5:name[i]+="Fifty ";break;
            case 4:name[i]+="Forty ";break;
            case 3:name[i]+="Thirty ";break;
            case 2:name[i]+="Twenty ";break;
        }
        num-=n/10;
        n=num*100;
        if(n>0&&n<9){
             switch (n){
                case 9:name[i]+="NIne ";break;
                case 8:name[i]+="Eight ";break;
                case 7:name[i]+="Seven ";break;
                case 6:name[i]+="Six ";break;
                case 5:name[i]+="Five ";break;
                case 4:name[i]+="Four ";break;
                case 3:name[i]+="Three ";break;
                case 2:name[i]+="Two ";break;
                case 1:name[i]+="One ";break;
             }
        }
        name[i]+=" Cents ";
    }
}