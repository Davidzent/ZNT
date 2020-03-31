/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on October 15th, 2018, 1:00 PM
 * Purpose:  Specification for the Card Class
 */

#ifndef CARD_H
#define CARD_H

class Card{
    private:
        int number;
    public:
        Card(int);
        char getSuit() const;
        char getFace() const;
        short getCVal() const;
};

#endif /* CARD */