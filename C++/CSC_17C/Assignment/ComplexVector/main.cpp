/* 
 * File:   main.cpp
 * Author: Guijosa David
 * Created on March 20th, 2019, 12:36 PM
 * Purpose: 
 */

//System Libraries
#include <iostream>  //Input/Output Library
using namespace std;

//User Libraries
#include "Vector.h"

//Global Constants, no Global Variables are allowed
//Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc...

//Function Prototypes
void fillVec(SimpleVector<int> &);
void addVec(SimpleVector<int> &);
void delVec(SimpleVector<int> &);
void prntVec(SimpleVector<int> &,int);

//Execution Begins Here!
int main(int argc, char** argv) {
    //Declare Variables
    int size;
    
    //Read in the size
    cout<<"What size vector to test?"<<endl;
    cin>>size;
    SimpleVector<int> sv(size);
 
    //Initialize or input i.e. set variable values
    fillVec(sv);
    
    //Display the outputs
    prntVec(sv,10);
    
    //Add and subtract from the vector
    addVec(sv);
    
    //Display the outputs
    prntVec(sv,10);
    
    //Add and subtract from the vector
    delVec(sv);
    
    //Display the outputs
    prntVec(sv,10);

    //Exit stage right or left!
    return 0;
}

void addVec(SimpleVector<int> &sv){
    int add=sv.size()*0.1;
    for(int i=1;i<=add;i++){
        sv.push_front(i+add-1);
        sv.push_back(i-add);
    }
}

void delVec(SimpleVector<int> &sv){
    int del=sv.size()*0.2;
    for(int i=1;i<=del;i++){
        sv.pop_front();
        sv.pop_back();
    }
}

void fillVec(SimpleVector<int> &sv){
    for(int i=0;i<sv.size();i++){
        sv[i]=i%10;
    }
}
void prntVec(SimpleVector<int> &sv,int n){
    cout<<endl;
    for(int i=0;i<sv.size();i++){
        cout<<sv[i]<<" ";
        if(i%n==(n-1))cout<<endl;
    }
    cout<<endl;
}


