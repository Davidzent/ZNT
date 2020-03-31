/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on Nov 08, 2018, 11:00 AM
 * Purpose:  
 */

//System Libraries Here
#include <iostream>

using namespace std;

//User Libraries Here
#include "Number.h"
//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    int num;
    //Input or initialize values Here
    cout<<"Enter a number between 0 and 9999"<<'\n';
    cin>>num;
    number numb(num);
    //Output Located Here
    numb.prnt();

    //Exit
    return 0;
}

