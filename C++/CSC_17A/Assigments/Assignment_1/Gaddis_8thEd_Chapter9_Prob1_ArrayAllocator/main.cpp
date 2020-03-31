/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on March 22, 2018, 11:00 AM
 * Purpose:  Hello World Template
 */

//System Libraries Here
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
int *fill1D(int);
void destroy(int *);

//Program Execution Begins Here
int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    //Declare all Variables Here
    int size=100;
    int *dynAry=fill1D(size);
   
    //clean memory
    destroy(dynAry);
    //Exit
    return 0;
}

int *fill1D(int n){
    int *a=new int[n];
    for(int i=0;i<n;i++){
    a[i]=rand()%90+10;
    }
    return a;
}
void destroy(int *d1){
    delete []d1;
    delete d1;
}