/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on Nov 08, 2018, 11:00 AM
 * Purpose:  
 */

//System Libraries Here
#include <iostream>
#include "Days.h"
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    int day;
    DAY name;
    //Input or initialize values Here
    cin>>day;
    //Process/Calculations Here
    name.setdat(day);
    //Output Located Here
    name.prnt();

    //Exit
    return 0;
}

