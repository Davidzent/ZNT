/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on October 16th, 2018, 1:40 PM
 * Purpose:  Deck test
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
int *inHand(int *,int,int);

//Execution Begins Here
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Create an array of 52 cards
    int nCards=52;
    int nShuffle=7;
    Card **deck=new Card*[nCards];
    int *indx=new int[nCards];
    
    //Printout each card
    for(int card=0;card<nCards;card++){
        deck[card]=new Card(card);
        prntCrd(deck[card]);
        indx[card]=card;
    }
    
    //Shuffle the Deck
    for(int shuffle=1;shuffle<=nShuffle;shuffle++){
        for(int card=0;card<nCards;card++){
            int swapit=rand()%nCards;
            int temp=indx[card];
            indx[card]=indx[swapit];
            indx[swapit]=temp;
        }
    }
    
    //Printout each card
    cout<<endl<<endl;
    for(int card=0;card<nCards;card++){
        prntCrd(deck[indx[card]]);
    }
    
    //Printout the hand
    int nHand=5;
    int *hand1=inHand(indx,nHand,nCards);
    cout<<endl<<endl;
    for(int card=0;card<nHand;card++){
        prntCrd(deck[hand1[card]]);
    }
    
    //Printout the hand
    int *hand2=inHand(indx,nHand,nCards);
    cout<<endl<<endl;
    for(int card=0;card<nHand;card++){
        prntCrd(deck[hand2[card]]);
    }
    
    //Deallocate
    for(int card=0;card<nCards;card++){
        delete deck[card];
    }
    delete []deck;
    delete []hand1;
    delete []hand2;
    
    //Exit stage right!
    return 0;
}

int *inHand(int *indx,int n,int nCards){
    static int deal=0;
    int last=deal+n;
    if(deal+n>nCards-1)deal=0;
    int * hand=new int[n];
    for(int i=deal,j=0;deal<last;deal++,j++){
        hand[j]=indx[deal];
    }
    return hand;
}
void prntCrd(Card *a){
    cout<<a->getFace()<<a->getSuit()<<"->"<<a->getCVal()<<" ";
    if(a->getFace()=='K')cout<<endl;
}