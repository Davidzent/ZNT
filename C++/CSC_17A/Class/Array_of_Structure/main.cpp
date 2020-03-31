/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on September 17th, 2018, 1:40 PM
 * Purpose:  A 1D Structure array containing 1D Arrays
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries
#include "Struc1DArray.h"

//Global Constants - Math/Physics Constants, Conversions,
//                   2-D Array Dimensions

//Function Prototypes
int *fill1D(int);
void filStrc(DynAry1 *,int,int *,int);
void prnStrc(DynAry1 *,int,int);
void destroy(DynAry1 *,int);

//Execution Begins Here
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variables and Initialize
    int size=100;
    int nStruc=10;
    DynAry1 *array1D=new DynAry1[nStruc];
    for(int i=0;i<nStruc;i++){
        int *dynAry=fill1D(size);
        filStrc(array1D,i,dynAry,size);
    }
    
    //Initialize Variables
    prnStrc(array1D,nStruc,10);
    
    //Deallocate memory
    destroy(array1D,nStruc);
    
    //Exit stage right!
    return 0;
}

int *fill1D(int n){
    int *a=new int[n];
    for(int i=0;i<n;i++){
        a[i]=rand()%90+10;//Random 2 Digit numbers
    }
    return a;
}

void filStrc(DynAry1 *d1,int row,int *a,int n){
    d1[row].size=n;
    (*(d1+row)).array=a;
}

void prnStrc(DynAry1 *d1,int rows,int perLine){
    for(int row=0;row<rows;row++){
        cout<<endl;
        for(int i=0;i<d1[row].size;i++){
            cout<<d1[row].array[i]<<" ";
            if(i%perLine==(perLine-1))cout<<endl;
        }
        cout<<endl;
    }
    cout<<endl;
}

void destroy(DynAry1 *d1,int rows){
    for(int row=0;row<rows;row++){
        delete []d1[row].array;
    }
    delete []d1;
}