/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on October 17th, 2018, 8:47 PM
 * Purpose:  Specification for the Deck of Cards
 */


#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include "Hand.h"

class Deck{
    private:
        int nCards;
        Card **card;
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

#endif /* DECK_H */