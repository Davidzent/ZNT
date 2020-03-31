/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Days.h
 * Author: rcc
 *
 * Created on November 8, 2018, 12:56 PM
 */

#ifndef DAYS_H
#define DAYS_H
#include <cstring>
using namespace std;
class DAY{
    private:
        int date;
        string name;
        const int size=12;
        int nmonth[12]={1,2,3,4,5,6,7,8,9,10,11,12};
        string month[12]={"January ","February ","March ","April ","May ","June ","July ",
    "August ","September ","October ","November ","December "};
    public:
        DAY();
        DAY(int);
        DAY(string);
        void setdat(int);
        void setname(string);
        string getname();
        int getdat();
        void prnt();
        void operator++(int);
        void operator--(int);
};


#endif /* DAYS_H */

