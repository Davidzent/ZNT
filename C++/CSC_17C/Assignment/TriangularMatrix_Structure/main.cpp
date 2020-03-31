/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on February 13th, 2019, 1:30 M
 * Purpose:  Hello World Template
 */

//System Libraries Here
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries Here
#include "Triangle.h"

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
Trngl *fillStr(int);
void prntStr(Trngl *);
void destroy(Trngl *);

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare all Variables Here
    int row=10;
    
    //Input or initialize values Here
    Trngl *triangle=fillStr(row);
    
    //Output Located Here
    prntStr(triangle);
    
    //Return Memory
    destroy(triangle);

    //Exit
    return 0;
}

void destroy(Trngl *tri){
    for(int row=0;row<tri->size;row++){
        delete []tri->data[row];
    }
    delete []tri->data;
    delete tri;
}

void prntStr(Trngl *tri){
    cout<<endl;
    for(int row=0;row<tri->size;row++){
        for(int col=0;col<row;col++){
            cout<<tri->data[row][col]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

Trngl *fillStr(int n){
    //Allocate a structure to hold the Matrix
    Trngl *tri=new Trngl;
    //Create the 2-D allocated pointer
    tri->data=new int*[n];
    for(int row=0;row<n;row++){
        tri->data[row]=new int[row+1];
    }
    tri->size=n;
    //Fill the array with values
    for(int row=0;row<n;row++){
        for(int col=0;col<row;col++){
            tri->data[row][col]=rand()%90+10;
        }
    }
    //return the Array pointer
    return tri;
}