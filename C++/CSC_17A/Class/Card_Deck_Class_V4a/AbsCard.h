/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on November 6th, 2018, 1:00 PM
 * Purpose:  Abstract Card Class
 */

#ifndef ABSCARD_H
#define ABSCARD_H

class AbsCard{
    public:
        virtual char getSuit() const = 0;
};

#endif /* ABSCARD_H */