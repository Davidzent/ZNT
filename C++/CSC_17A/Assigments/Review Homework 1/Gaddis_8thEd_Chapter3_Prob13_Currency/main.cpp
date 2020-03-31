/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on March 22, 2018, 11:00 AM
 * Purpose:  Hello World Template
 */

//System Libraries Here
#include <iostream>
#include <iomanip>
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions
    const float YENtDLL=111.10f;
    const float EURtDLL=0.86f;
//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    float DLLR,yen,eur;
    
    //Input or initialize values Here
    cout<<"Input the amount of dollars that you want to convert"<<endl;
    cin>>DLLR;
    
    //Process/Calculations Here
    yen=DLLR*YENtDLL;
    eur=DLLR*EURtDLL;
    
    //Output Located Here
    cout<<fixed<<showpoint<<setprecision(2);
    cout<<"The amount of "<<DLLR<<" is equal to "<<yen<<" Yen"<<endl;
    cout<<"The amount of "<<DLLR<<" is equal to "<<eur<<" Euros"<<endl;

    //Exit
    return 0;
}

