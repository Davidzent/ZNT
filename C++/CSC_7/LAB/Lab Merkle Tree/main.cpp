/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on FEbruary 13, 2019, 11:00 AM
 * Purpose: 
 */

//System Libraries Here
#include <iostream>
#include <ctime>
using namespace std;

//User Libraries Here
#include "Merkle_tree.h"
//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here


//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    const char name[20]="ToHash.txt";
    Merkle *data=new Merkle (name);
    //Input or initialize values Here
    //Process/Calculations Here
    data->display(data,0);
    //Output Located Here

    //Exit
    return 0;
}
//9519418408

