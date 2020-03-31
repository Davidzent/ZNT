/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on October 17th, 2018, 8:47 PM
 * Purpose:  Specification for the Deck of Cards
 */


#ifndef DECK_H
#define DECK_H

#include "Hand.h"

template <class T>
class Deck{
    private:
        int nCards;
        T **card;
        int *indx;
    public:
        Deck(int);
        ~Deck();
        void shuffle(int);
        int *deal(int);
        int getCard(bool,int);
        void prnCrds();
        void prnCrds(Hand &);
};

#include <iostream>
#include <cstdlib>
using namespace std;

template <class T>
Deck<T>::Deck(int nCards){
    this->nCards=((nCards<2||nCards>52)?52:nCards);
    card=new T*[this->nCards];
    indx=new int[this->nCards];
    
    //Printout each card
    for(int crd=0;crd<this->nCards;crd++){
        card[crd]=new T(crd);
        indx[crd]=crd;
    }
}

template <class T>
Deck<T>::~Deck(){
    for(int crd=0;crd<nCards;crd++){
        delete card[crd];
    }
    delete []indx;
    delete []card;
}

template <class T>
void Deck<T>::shuffle(int nShuffle){
    for(int shuffle=1;shuffle<=nShuffle;shuffle++){
        for(int card=0;card<nCards;card++){
            int swapit=rand()%nCards;
            int temp=indx[card];
            indx[card]=indx[swapit];
            indx[swapit]=temp;
        }
    }
    
}

template <class T>
int *Deck<T>::deal(int n){
    static int deal=0;
    int last=deal+n;
    if(deal+n>nCards-1)deal=0;
    int * hand=new int[n];
    for(int i=deal,j=0;deal<last;deal++,j++){
        hand[j]=indx[deal];
    }
    return hand;
}

template <class T>
int Deck<T>::getCard(bool shuf,int n){
    int crdNum=n<0||n>=nCards?0:n;
    if(shuf)return indx[n];
    else return n;
}

template <class T>
void Deck<T>::prnCrds(){
    cout<<endl<<endl;
    for(int crd=0;crd<nCards;crd++){
        int idx=indx[crd];
        cout<<card[idx]->getFace()<<card[idx]->getSuit()<<"->"<<card[idx]->getCVal()<<" ";
        if(card[idx]->getFace()=='K')cout<<endl;
    }
}

template <class T>
void Deck<T>::prnCrds(Hand &h){
    cout<<endl<<endl;
    const int *cidx=h.getHand();
    for(int crd=0;crd<h.getSize();crd++){
        int idx=cidx[crd];
        cout<<card[idx]->getFace()<<card[idx]->getSuit()<<"->"<<card[idx]->getCVal()<<" ";
        if(card[idx]->getFace()=='K')cout<<endl;
    }
}

#endif /* DECK_H */