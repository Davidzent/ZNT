/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on October 15th, 2018, 1:10 PM
 * Purpose:  Card Class
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
void prnCrd(Card *);

//Execution Begins Here
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Initialize Variables
    for(int card=0;card<52;card++){
        Card *c=new Card(card);
        prnCrd(c);
        delete c;
    }
    
    //Deallocate the pointer
    
    //Exit stage right!
    return 0;
}

void prnCrd(Card *c){
    cout<<c->getFace()<<c->getSuit()<<"->"<<c->getCVal()<<" ";
    if(c->getFace()=='K')cout<<endl;
}