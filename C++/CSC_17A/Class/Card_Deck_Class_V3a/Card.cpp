/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on October 15th, 2018, 1:00 PM
 * Purpose:  Card Class
 */

#include "Card.h"

Card::Card(int n){
    number=n>0&&n<52?n:0;
}
char Card::getSuit() const{
    static char suit[]={'S','D','C','H'};
    return suit[number/13];
}

char Card::getFace() const{
    static char face[]={'A','2','3','4','5','6','7',
                        '8','9','T','J','Q','K'};
    return face[number%13];
}

short Card::getCVal() const{
    int n=number%13+1;
    n=n>10?10:n;
    return n;
}