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
#include "Card.h"

//Global Constants - Math/Physics Constants, Conversions,
//                   2-D Array Dimensions

//Function Prototypes
void prnCrd(Card *);
void shuffle(int *,int,int);
int *deal(int *,int,int);

//Execution Begins Here
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Initialize Variables
    int nCards=52;
    int nShufl=7;
    int nHand=5;
    Card **deck=new Card*[nCards];//Declare the Deck
    int *indx=new int[nCards];
    
    //Fill the Deck with Cards
    cout<<"The Original Deck"<<endl;
    for(int card=0;card<nCards;card++){
        deck[card]=new Card(card);
        prnCrd(deck[card]);
        indx[card]=card;
    }
    
    //Shuffle the Deck
    shuffle(indx,nCards,nShufl);
    
    //Print the shuffled cards
    cout<<endl<<endl<<"The Shuffled Deck"<<endl;
    for(int card=0;card<nCards;card++){
        prnCrd(deck[indx[card]]);
    }
    
    //Print the Hand
    int *hand1=deal(indx,nCards,nHand);
    cout<<endl<<endl<<"The First Hand Delt"<<endl;
    for(int card=0;card<nHand;card++){
        prnCrd(deck[hand1[card]]);
    }
    
    //Print the Hand
    int *hand2=deal(indx,nCards,nHand);
    cout<<endl<<endl<<"The Second Hand Delt"<<endl;
    for(int card=0;card<nHand;card++){
        prnCrd(deck[hand2[card]]);
    }
    
    //Deallocate the pointer
    for(int card=0;card<52;card++){
        delete deck[card];
    }
    delete []deck;
    delete []indx;
    delete []hand1;
    delete []hand2;
    
    //Exit stage right!
    return 0;
}

int *deal(int *indx,int n,int nDeal){
    static int nDelt=0;
    if(nDelt>.80*n){
        shuffle(indx,n,7);
        nDelt=0;
    }
    int *hand=new int[nDeal];
    for(int card=nDelt,i=0;card<nDelt+nDeal;card++,i++){
        hand[i]=indx[card];
    }
    nDelt+=nDeal;
    return hand;
}

void shuffle(int *indx,int n,int nShuf){
    for(int cShuf=1;cShuf<=nShuf;cShuf++){
        for(int card=0;card<n;card++){
            int tCrdNum=rand()%n;
            int temp=indx[card];
            indx[card]=indx[tCrdNum];
            indx[tCrdNum]=temp;
        }
    }
}

void prnCrd(Card *c){
    cout<<c->getFace()<<c->getSuit()<<"->"<<c->getCVal()<<" ";
    if(c->getFace()=='K')cout<<endl;
}