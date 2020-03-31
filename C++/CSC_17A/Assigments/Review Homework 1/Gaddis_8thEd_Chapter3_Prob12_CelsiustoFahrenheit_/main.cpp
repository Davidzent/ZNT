/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on Sep 7, 2018, 11:00 AM
 * Purpose:  
 */

//System Libraries Here
#include <iostream>
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    float Cel,Fah;  //Celsius and fahrenheit
    
    //Input or initialize values Here
    cout<<"Input the temperature in Celsius to converted to Fahrenheit"<<endl;
    cin>>Cel;
    
    //Process/Calculations Here
    Fah=9*Cel/5+32;
    
    //Output Located Here
    cout<<"The temperature in Fahrenheit is = "<<Fah;

    //Exit
    return 0;
}

