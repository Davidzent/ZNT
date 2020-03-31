/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on Oct 27, 2018, 11:30 AM
 * Purpose:  Hello World Template
 */

//System Libraries Here
#include <iostream>
#include "EnCrypt.h"
#include "Data.h"
#include <cmath>
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
void getdata(char[],const int);
Data *struc(char[],const int);
void toint(Data*,int[]);
ENC *struc(int [],int);
void swap(ENC*,int,int);
void decrypt(ENC *);
void print(ENC*);
void destroy(ENC*);
void destroy(Data*);
//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    const int nDigit=4; //number of digits in data
    char *data=new char[nDigit];
    int *Digits=new int[nDigit];
    Data *info;
    ENC *toenc;
    //Get data to encrypt and give it an structure
    getdata(data,nDigit);
    cout<<endl;
    info=struc(data,nDigit);
    //convert characters to integers and give a structure
    toint(info,Digits);
    cout<<endl;
    toenc=struc(Digits,nDigit);
    //decrypt data
    decrypt(toenc);
    //print data
    cout<<"The decrypted data is"<<endl;
    print(toenc);
    //Exit
    destroy(info);
    destroy(toenc);
    return 0;
}
void print(ENC *info){
    for(int i=0;i<info->nDigit;i++){
        cout<<info->data[i];
    }
}
void decrypt(ENC *info){
    int result;
    for(int i=0;i<info->nDigit;i++){
        result=(info->data[i]-5);
        if(result<7&&result>0)info->data[i]=result;
        else info->data[i]=result+8;
    }
    swap(info,0,2);
    swap(info,1,3);
}
void swap(ENC *info,int from,int to){
    int temp=info->data[from];
    info->data[from]=info->data[to];
    info->data[to]=temp;
}
ENC *struc(int digits[],int size){
    ENC *info;
    info->data=digits;
    info->nDigit=size;
    return info;
}
void toint(Data *info,int digits[]){
    for(int i=0;i<info->nmData;i++){
        digits[i]=info->data[i]-48;
    }
}
Data *struc(char digits[],const int size){
    Data *info;
    info->data=digits;
    info->nmData=size;
    return info;
}
void getdata(char data[],const int nmData){
    cout<<"Input the data to decrypt"<<endl;
    for(int i=0;i<nmData;i++){
    cin>>data[i];
    if(data[i]<'0'||data[i]>'7'){
        cout<<"Invalid data"<<endl;
        exit(EXIT_FAILURE);
        }
    }
}
void destroy(ENC *info){
    delete []info->data;
}
void destroy(Data *info){
    delete []info->data;
}