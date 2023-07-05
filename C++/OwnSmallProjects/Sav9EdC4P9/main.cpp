/* 
 * File:   Sav9EdC4P9
 * Author: David Guijosa
 * Created on July 22, 2020
 * Instructions:
    * Find the max of either two or three parameters of type float
    * and returns the largest of them. Display answer to one decimal place. 
    * For function with two parameter, use first two inputs.
 */

//System Libraries
#include <iostream>  //Input/Output Library
#include <iomanip>   //IO manipulator
using namespace std;

//User Libraries

//Global Constants, no Global Variables are allowed
//Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc...

//Function Prototypes

//Execution Begins Here!
int main(int argc, char** argv) {
    //Set the random number seed
    
    //Declare Variables
    float n1,n2,n3;         //Number 1, 2 and 3
    
    //Initialize or input i.e. set variable values
    cout<<"Enter first number:\n";
    cin>>n1;
    cout<<"\nEnter Second number:\n";
    cin>>n2;
    cout<<"\nEnter third number:\n";
    cin>>n3;
    
    //Display the outputs
    cout<<fixed<<showpoint<<setprecision(1);
    cout<<"\nLargest number from two parameter function:\n";
    if(n1>n2)cout<<n1<<endl;                                    //Find Maximum between 2 parameters with if-else statement    
    else cout<<n2<<endl;
    
    cout<<"\nLargest number from three parameter function:\n";
    cout<<(n1>n2?(n1>n3?n1:n3):(n2>n3?n2:n3))<<endl;            //Find Maximum between 3 parameters same as
                                                                //if(n1>n2&&n1>n3)n1 
                                                                //else if(n2>n1&&n2>n3) n2 
                                                                //else n3
    
    //Exit stage right or left!
    return 0;
}