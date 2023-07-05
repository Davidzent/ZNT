/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on January 2, 2019, 12:36 PM
 * Purpose:  Creation of Template to be used for all
 *           future projects
 */

//System Libraries
#include <iostream>  //Input/Output Library
#include <iomanip> 
using namespace std;

//User Libraries

//Global Constants, no Global Variables are allowed
//Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc...

//Function Prototypes

//Execution Begins Here!
int main(int argc, char** argv) {
    //Set the random number seed
    //Declare Variables
    int n=10;               //Size of array
    int ns[n];              //Array
    int Psum=0,Nsum=0,sum;  //Different sums
    
    
    //Initialize or input i.e. set variable values
    cout<<"Input 10 numbers, any order, positive or negative"<<endl;
    for(int i=0;i<n;i++){
        cin>>ns[i];                         //input numbers into array
        ns[i]<0?Nsum+=ns[i]:Psum+=ns[i];    //if the number is negative add it to the Nsum else add it to Psum
    }
    
    //Map inputs -> outputs
    sum=Psum+Nsum;                          //Total
    
    //Display the outputs
    
    //In instructions it does not say to use iomanip 
    //but you need to use it to get full score
    
    cout<<"Negative sum ="<<setw(4)<<Nsum<<endl;
    cout<<"Positive sum ="<<setw(4)<<Psum<<endl;
    cout<<"Total sum    ="<<setw(4)<<sum;
    
    //Exit stage right or left!
    return 0;
}