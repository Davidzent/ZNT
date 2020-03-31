/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on October 17th, 2018, 8:47 PM
 * Purpose:  Implementation of the Deck of Cards
 */

#include "Deck.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Deck::Deck(int nCards){
    this->nCards=((nCards<2||nCards>52)?52:nCards);
    card=new Card*[this->nCards];
    indx=new int[this->nCards];
    
    //Printout each card
    for(int crd=0;crd<this->nCards;crd++){
        card[crd]=new Card(crd);
        indx[crd]=crd;
    }
}

Deck::~Deck(){
    for(int crd=0;crd<nCards;crd++){
        delete card[crd];
    }
    delete []indx;
    delete []card;
}

void Deck::shuffle(int nShuffle){
    for(int shuffle=1;shuffle<=nShuffle;shuffle++){
        for(int card=0;card<nCards;card++){
            int swapit=rand()%nCards;
            int temp=indx[card];
            indx[card]=indx[swapit];
            indx[swapit]=temp;
        }
    }
    
}

int *Deck::deal(int n){
    static int deal=0;
    int last=deal+n;
    if(deal+n>nCards-1)deal=0;
    int * hand=new int[n];
    for(int i=deal,j=0;deal<last;deal++,j++){
        hand[j]=indx[deal];
    }
    return hand;
}

int Deck::getCard(bool shuf,int n){
    int crdNum=n<0||n>=nCards?0:n;
    if(shuf)return indx[n];
    else return n;
}

void Deck::prnCrds(){
    cout<<endl<<endl;
    for(int crd=0;crd<nCards;crd++){
        int idx=indx[crd];
        cout<<card[idx]->getFace()<<card[idx]->getSuit()<<"->"<<card[idx]->getCVal()<<" ";
        if(card[idx]->getFace()=='K')cout<<endl;
    }
}

void Deck::prnCrds(Hand &h){
    cout<<endl<<endl;
    const int *cidx=h.getHand();
    for(int crd=0;crd<h.getSize();crd++){
        int idx=cidx[crd];
        cout<<card[idx]->getFace()<<card[idx]->getSuit()<<"->"<<card[idx]->getCVal()<<" ";
        if(card[idx]->getFace()=='K')cout<<endl;
    }
}