/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on October 15th, 2018, 1:10 PM
 * Purpose:  Card Class and develop a Deck
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries
#include "Deck.h"
#include "InhCard.h"

//Global Constants - Math/Physics Constants, Conversions,
//                   2-D Array Dimensions

//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Initialize Variables
    int nCards=52;
    int nShufl=7;
    int nHand=5;
    Deck deck(nCards);
    InhCard test(0);
    
    //Fill the Deck with Cards
    deck.prnCrds();
    
    //Shuffle the Deck
    deck.shuffle(nShufl);
    
    //Print the shuffled cards
    deck.prnCrds();
    cout<<endl<<test.getFile()<<endl;
    
    //Print the Hand
    
    //Exit stage right!
    return 0;
}