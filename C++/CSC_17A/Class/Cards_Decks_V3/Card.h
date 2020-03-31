/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on October 15th, 2018, 8:47 PM
 * Purpose:  Specification for the CARD Class
 */

#ifndef CARD_H
#define CARD_H

class Card{
    private:
        int number;
    public:
        Card(int);
        char getSuit()const;
        char getFace() const;
        unsigned short getCVal() const;
};

#endif /* CARD */