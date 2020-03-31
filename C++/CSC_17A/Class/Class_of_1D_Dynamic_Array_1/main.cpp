/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on September 17th, 2018, 1:40 PM
 * Purpose:  1D Array Class
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries
#include "Class1DArray.h"

//Global Constants - Math/Physics Constants, Conversions,
//                   2-D Array Dimensions

//Function Prototypes
void prnCls(DynAry1 *,int);

//Execution Begins Here
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare Variables and Initialize
    int size=150;
    DynAry1 *dynAry = new DynAry1(size);
    
    //Initialize Variables
    prnCls(dynAry,10);
    
    //Deallocate the pointer
    delete dynAry;
    
    //Exit stage right!
    return 0;
}

void prnCls(DynAry1 *d1,int perLine){
    cout<<endl;
    for(int i=0;i<d1->getSize();i++){
        cout<<d1->getElem(i)<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}