/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on October 15th, 2018, 1:00 PM
 * Purpose:  Card Class
 */

#include "AbsCard.h"

#ifndef CARD_H
#define CARD_H

class Card: public AbsCard{
    private:
        int number;
    public:
        Card(int);
        char getSuit() const;
        char getFace() const;
        short getCVal() const;
};

#endif /* CARD */