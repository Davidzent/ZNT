/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on October 16th, 2018, 1:40 PM
 * Purpose:  Card Class Test
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries
#include "Card.h"

//Global Constants - Math/Physics Constants, Conversions,
//                   2-D Array Dimensions

//Function Prototypes
void prntCrd(Card *);

//Execution Begins Here
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Printout each card
    for(int card=0;card<52;card++){
        Card *c=new Card(card);
        prntCrd(c);
        delete c;
    }
    
    //Exit stage right!
    return 0;
}

void prntCrd(Card *a){
    cout<<a->getFace()<<a->getSuit()<<"->"<<a->getCVal()<<" ";
    if(a->getFace()=='K')cout<<endl;
}