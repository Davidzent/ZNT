/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on October 17th, 2018, 8:47 PM
 * Purpose:  Specification for the Hand
 */

#ifndef HAND_H
#define HAND_H

class Hand{
    private:
        int nHand;
        int *cards;
    public:
        Hand(int *array,int n){
            nHand=n;
            cards=array;
        }
        ~Hand(){delete []cards;}
        const int*getHand()const {return cards;}
        int getSize()const {return nHand;}
};

#endif /* HAND_H */