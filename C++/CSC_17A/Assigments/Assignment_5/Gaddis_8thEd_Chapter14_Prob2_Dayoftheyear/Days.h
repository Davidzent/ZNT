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
        int day;
        const int size=12;
        int nmonth[12];
        string month[12]={"January ","February ","March ","April ","May ","June ","July ",
    "August ","September ","October ","November ","December "};
        int rday;
        int numnth;
    public:
        DAY();
        void setdat(int);
        void prnt();
};


#endif /* DAYS_H */

