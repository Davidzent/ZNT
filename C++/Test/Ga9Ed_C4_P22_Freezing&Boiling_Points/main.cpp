/* 
 * File:   
 * Author: 
 * Created on 
 * Purpose: 
 * Freezing and Boiling Points
The following table lists the freezing and boiling points of several substances. Write a
program that asks the user to enter a temperature and then shows all the substances
that will freeze at that temperature and all that will boil at that temperature. For example,
if the user enters −20 the program should report that water will freeze and oxygen
will boil at that temperature.
    Substance        Freezing Point (°F)     Boiling Point (°F)
    Ethyl alcohol                  -173                    172
    Mercury                         -38                    676
    Oxygen                         -362                   -306
    Water                            32                    212
 */

//System Libraries
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

//User Libraries

//Global Constants - No Global Variables
//Only Universal Constants, Math, Physics, Conversions, Higher Dimensions
const int EthyF=-173;
const int EthyB=172;
const int MercF=-38;
const int MercB=676;
const int OxygF=-362;
const int OxygB=-306;
const int WateF=32;
const int WateB=212;

//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv) {
    //Set Random Number seed

    //File reading
    ifstream in;
    ofstream out;
    in.open("in.txt");
    out.open("out.txt");
    
    //Declare Variable Data Types and Constants
    const int space1=9;
    const int space2=11;
    int input;
    
    //Initialize Variables
    out<<"Please enter the temperature to check: "<<endl;
    in>>input;
    
    //Process or map Inputs to Outputs
    
    //Display Outputs
    out<<"Substance        Freezing    Boiling"<<endl
        <<"Ethyl alcohol   "<<setw(space1)<<(input<=EthyF?"Yes":"No")<<setw(space2)<<(input>=EthyB?"Yes":"No")<<endl
        <<"Mercury         "<<setw(space1)<<(input<=MercF?"Yes":"No")<<setw(space2)<<(input>=MercB?"Yes":"No")<<endl
        <<"Oxygen          "<<setw(space1)<<(input<=OxygF?"Yes":"No")<<setw(space2)<<(input>=OxygB?"Yes":"No")<<endl
        <<"Water           "<<setw(space1)<<(input<=WateF?"Yes":"No")<<setw(space2)<<(input>=WateB?"Yes":"No")<<endl;  
    //Exit stage right!
    return 0;
}