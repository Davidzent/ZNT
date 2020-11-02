/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on September 17th, 2018, 1:40 PM
 * Purpose:  1D Array Structure
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
DynAry1 *filStrc(int *,int);
void prnStrc(DynAry1 *,int);
void destroy(DynAry1 *);

//Execution Begins Here
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare Variables and Initialize
    int size=100;
    int *dynAry=fill1D(size);
    DynAry1 *array1D=filStrc(dynAry,size);
    
    //Initialize Variables
    prnStrc(array1D,10);
    
    //Deallocate memory
    destroy(array1D);
    
    //Exit stage right!
    return 0;
}

int *fill1D(int n){
    int *a=new int[n];    //creates a dynamic array of size n
    for(int i=0;i<n;i++){
        a[i]=rand()%90+10;  //Fills array with 2 digit numbers
    }
    return a;
}

DynAry1 *filStrc(int *a,int n){
    DynAry1 *d1=new DynAry1;    //points d1 to a new DynAry1
    d1->size=n;                 //sets the variable size of the structure to n of the function
    (*d1).array=a;              //sets the pointer array of the structure to the pointer array a of the function
                                //(*d1).array=a same as d1->array=a just more confusing
    return d1;                  //return the created DynAry1
}

void prnStrc(DynAry1 *d1,int perLine){
    cout<<endl;                                 
    for(int i=0;i<d1->size;i++){                
        cout<<d1->array[i]<<" ";                //d1->array[i] gets the value from position i of the array of the structure  
        if(i%perLine==(perLine-1))cout<<endl;   //every perLine values outputs a end of the line  
    }
    cout<<endl;                                 
}

void destroy(DynAry1 *d1){
    delete []d1->array;                         //deletes the pointer array that is in the structure
    delete d1;                                  //deletes the structure pointer
}