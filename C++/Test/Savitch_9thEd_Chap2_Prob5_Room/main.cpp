/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on January 2, 2019, 12:36 PM
 * Purpose:  Creation of Template to be used for all
 *           future projects
 */

//System Libraries
#include <iostream>  //Input/Output Library
using namespace std;

//User Libraries

//Global Constants, no Global Variables are allowed
//Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc...

//Function Prototypes

//Execution Begins Here!
int main(int argc, char** argv) {
    //Set the random number seed
    
    //Declare Variables
    int current,size;
    
    //Initialize or input i.e. set variable values
    cout<<"Input the maximum room capacity and the number of people"<<endl;
    cin>>size>>current;         //input the maximum number of people and the number of people that are listed for the meeting
    
    //Map inputs -> outputs
    
    //Display the outputs
    if(current>size){
        cout<<"Meeting cannot be held."<<endl;
        cout<<"Reduce number of people by "<<current-size<<" to avoid fire violation.";
    }
    else if(current<size){
        cout<<"Meeting can be held."<<endl;
        cout<<"Increase number of people by 100 will be allowed without violation.";
    }else{
        //add a third visible Test case when the room is full
        
    }
    //Exit stage right or left!
    return 0;
}