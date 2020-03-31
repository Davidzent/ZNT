/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TimeOff.h
 * Author: gabriel
 *
 * Created on November 12, 2018, 8:26 PM
 */

#ifndef TIMEOFF_H
#define TIMEOFF_H
#include <iostream>
using namespace std;
class TimeOff{
    private:
        int mxsick=5;
        int mxvact=10;
        int mxUpaid=5;
        int ID;
        string name;
        int upaidtk;
        int sicktk;
        int vactake;
    public:
        TimeOff();
        friend ostream &operator<<(ostream &,const TimeOff &);
        friend istream &operator>>(istream&,TimeOff &);
        
};


#endif /* TIMEOFF_H */

