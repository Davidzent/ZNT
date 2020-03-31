/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on November 6th, 2018, 1:20 PM
 * Purpose:  Specification for the Inherited CARD Class
 */


#ifndef INHCARD_H
#define INHCARD_H

#include "Card.h"
#include <cstring>
#include <sstream>
using namespace std;

class InhCard: public Card{
    public:
        InhCard(int num):Card(num){};
        string getFile() const{
            string file;
            file+=this->getFace();
            file+=this->getSuit();
            string value;
            stringstream ss;
            ss<<this->getCVal();
            ss>>value;
            file+=value;
            file+=".jpg";
            return file;
        }
};

#endif /* INHCARD_H */

