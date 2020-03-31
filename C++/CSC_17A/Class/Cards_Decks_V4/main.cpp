/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on September 17th, 2018, 1:40 PM
 * Purpose:  Deck Class Test
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
    
    //Create an array of 52 cards
    int nCards=52;      //Number of Cards in the Deck
    int nShuf=7;        //Number of times to shuffle the Deck
    int nHand=5;        //Number of Cards in the Hand
    Deck deck(nCards);  //Instantiate the Deck, create the Deck Object
    
    //Printout each card
    deck.prnCrds();
    
    //Shuffle the Deck
    deck.shuffle(nShuf);
    
    //Printout each card
    deck.prnCrds();
    
    //Deal the Hand and Print
    Hand handOne(deck.deal(nHand),nHand);
    deck.prnCrds(handOne);

    //Deal the next Hand and Print
    Hand handTwo(deck.deal(nHand),nHand);
    deck.prnCrds(handTwo);
    InhCard test(0);
    cout<<endl<<test.getFile()<<endl;
    
    //Exit stage right!
    return 0;
}