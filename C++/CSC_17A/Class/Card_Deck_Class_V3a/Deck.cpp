/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on October 17th, 2018, 8:47 PM
 * Purpose:  Implementation for the Deck of Cards
 */

#include "Deck.h"
#include <iostream>
#include <cstdlib>
using namespace std;


Deck::Deck(int n){
    nCards=n<2||n>nCards?52:n;//Limit of the Number of cards
    card=new Card*[nCards];   //Allocation of the cards in the Deck
    indx=new int[nCards];     //Allocation of the index
    //Create the Cards
    for(int crd=0;crd<nCards;crd++){
        card[crd]=new Card(crd);
        indx[crd]=crd;
    }
}

Deck::~Deck(){
    for(int crd=0;crd<nCards;crd++){
        delete card[crd];
    }
    delete []card;
    delete []indx;
}

void Deck::shuffle(int nShuf){
    for(int cShuf=1;cShuf<=nShuf;cShuf++){
        for(int crd=0;crd<nCards;crd++){
            int tCrdNum=rand()%nCards;
            int temp=indx[crd];
            indx[crd]=indx[tCrdNum];
            indx[tCrdNum]=temp;
        }
    }
}

int *Deck::deal(int nDeal){
    static int nDelt=0;
    if(nDelt>.80*nCards){
        shuffle(7);
        nDelt=0;
    }
    int *hand=new int[nDeal];
    for(int card=nDelt,i=0;card<nDelt+nDeal;card++,i++){
        hand[i]=indx[card];
    }
    nDelt+=nDeal;
    return hand;
}

void Deck::prnCrds(){
    cout<<endl<<endl;
    for(int cd=0;cd<nCards;cd++){
        int crd=indx[cd];
        cout<<card[crd]->getFace()<<card[crd]->getSuit()<<"->"
                <<card[crd]->getCVal()<<" ";
        if(card[crd]->getFace()=='K')cout<<endl;
    }
}

void Deck::prnCrds(int *,int){
    
}
