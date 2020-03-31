/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on FEbruary 13, 2019, 11:00 AM
 * Purpose: 
 */

//System Libraries Here
#include <iostream>
#include <ctime>

#include "Triangular Matrix.h"
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    int row=10;
    int input;
    TrgMtrx array(row,90,10);
    
    //Input or initialize values Here
    array.SetRVal();
    //Output Located Here
    array.prntAry();
    array.SetVal(1,0);
    array.prntAry();

    //Exit
    return 0;
}