/* 
 * File:   main.cpp
 * Author: David Guijosa
 * Created on July 20, 2019, 12:36 PM
 * Instructions:  
     * Write a program to score the paper-rock-scissor game. 
     * Each of two users types in either P, R, or S. 
     * The program then announces the winner as well as the basis for determining the winner:
     * Paper covers rock, Rock breaks scissors, Scissors cut paper, or Nobody wins. 
     * Be sure to allow the users to use lowercase as well as uppercase letters.
 * -*- = possible changes
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
    char p1,p2;     //Player 1 and Player 2 inputs
    
    //Initialize or input i.e. set variable values
    cout<<"Rock Paper Scissors Game\n";
    cout<<"Input Player 1 and Player 2 Choices\n";
    cin>>p1>>p2;
    
    //Map inputs -> outputs
    p1>='a'?p1-=32:p1;  //to uppercase 
    p2>='a'?p2-=32:p2;  //to uppercase 
    
    //Display the outputs
    if(p1=='R'){
        if(p2=='R')cout<<"Nobody wins";                 //No test case for "Nobody wins", maybe include one
        else if(p2=='P')cout<<"Paper covers rock.";
        else if(p2=='S')cout<<"Rock breaks scissors.";
    }else if(p1=='P'){
        if(p2=='P')cout<<"Nobody wins";
        else if(p2=='R')cout<<"Paper covers rock.";
        else if(p2=='S')cout<<"Scissors cuts paper.";
    }else if(p1=='S'){
        if(p2=='S')cout<<"Nobody wins";                 
        else if(p2=='P')cout<<"Scissors cuts paper.";
        else if(p2=='R')cout<<"Rock breaks scissors.";
    }
    
    //Exit stage right or left!
    return 0;
}