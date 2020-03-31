/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on November 6th, 2018, 1:00 PM
 * Purpose:  Inherited Card Class
 */

#include "Card.h"
#include <cstring>
#include <sstream>
using namespace std;

#ifndef INHCARD_H
#define INHCARD_H

class InhCard: public Card{
    public:
        InhCard(int num): Card(num){};
        string getFile(){
            string file,val;
            stringstream ss;
            ss<<getCVal();
            ss>>val;
            file+=getFace();
            file+=getSuit();
            file+=val;
            file+=".jpg";
            return file;
        }
};


#endif /* INHCARD_H */

